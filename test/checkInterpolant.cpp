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

    SDEBUG(domain);
    RealInterpolant gi(RealBoundaryValues(BoundaryPoints(domain), h));
    const auto& zb = eval_points.vector();
    //SDEBUG(arma::abs(gi(zb) - h(zb)));
    SDEBUG("\n" <<
            arma::join_rows(
                jPointsFromPointsVector(0, domain, gi(zb)),
                jPointsFromPointsVector(0, domain, h(zb)) ));
    CHECK(approx_equal(gi(zb), h(zb), "absdiff", 10.*eps2pi));

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
