/*
 * Copyright 2017 Everett Kropf.
 *
 * This file is part of ModifiedSchwarz.
 *
 * ModifiedSchwarz is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ModifiedSchwarz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ModifiedSchwarz.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "UnitTest.h"
#include "TestFunctions.hpp"

#include "SchwarzTypes.h"
#include "BoundaryValues.hpp"
#include "RealInterpolant.h"
#include "ComplexInterpolant.h"

using namespace ModifiedSchwarz;

//template<typename ArmaMatLike>
//ArmaMatLike polesInHoles(const ArmaMatLike& z, const UnitCircleDomain& D)
//{
//    ArmaMatLike w(size(z), arma::fill::zeros);
//    for (auto & d : D.centers()) w += 1./(z - d);
//
//    return w;
//}

SUITE(InterpolantSuite)
{

TEST(InterpLabel)
{
    TEST_FILE("Real Interpolant");
}

struct Fixture
{
    using Function = std::function<mat(cx_mat&)>;

    static constexpr unsigned N = 100;

    UnitCircleDomain domain;
    BoundaryPoints eval_points;
    ComplexBoundaryValues::Function g;
    RealBoundaryValues::Function h;

    Fixture()
        : domain(domainExample3()),
          eval_points(BoundaryPoints(domain, N))
    {
        g = [this](const cx_mat& z) { return polesInHoles(z, domain); };
        h = [this](const cx_mat& z) { return real(polesInHoles(z, domain)); };
    }
};

TEST_FIXTURE(Fixture, RealInterp)
{
    TEST_LINE("Real interpolation");

    cx_mat pts = BoundaryPoints(domain).matrix();
    // auto vv{h(pts.col(0).rows(0, 1))};
    cx_double p1{pts(0, 0)}, p2{pts(1, 0)};
    cx_double v1{1./(p1 - domain.dv(0)) + 1./(p1 - domain.dv(1))};
    cx_double v2{1./(p2 - domain.dv(0)) + 1./(p2 - domain.dv(1))};
    SDEBUG("  Centers: " << domain.centers() << "\n"
            << "  Value 1: " << v1 << "\n  Value 2: " << v2 << "\n");

    RealInterpolant gi(RealBoundaryValues(BoundaryPoints(domain), h));
    const auto& zb = eval_points.vector();
    CHECK(approx_equal(gi(zb), h(zb), "absdiff", 10.*eps2pi));

    try
    {
        gi.boundaryValues().values().save("bvalues.arma", arma::arma_ascii);
        gi.boundaryValues().points().matrix().save("bpoints.arma", arma::arma_ascii);
        gi.constants().save("constants.arma", arma::arma_ascii);
        gi.coefficients().save("coefficients.arma", arma::arma_ascii);
    }
    catch (...)
    {}

    TEST_DONE;
}

TEST_FIXTURE(Fixture, RealInterpD)
{
    TEST_LINE("Real interp derivatives");

    // TODO: Write tests for 1st derivative, and nth derivative.

    std::cout << "Test needs written.\n";
    CHECK(0);
}

TEST_FIXTURE(Fixture, ComplexInterp)
{
    TEST_LINE("Complex interpolation");

    ComplexInterpolant gi(ComplexBoundaryValues(BoundaryPoints(domain), g));
    const auto& zb = eval_points.vector();
    CHECK(approx_equal(gi(zb), g(zb), "absdiff", 10.*eps2pi));

    TEST_DONE;
}

TEST_FIXTURE(Fixture, ComplexInterpD)
{
    TEST_LINE("Complex interp derivatives");

    // TODO: Write tests for 1st derivative, and nth derivative.

    std::cout << "Test needs written.\n";
    CHECK(0);
}

} // SUITE
