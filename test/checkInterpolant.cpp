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

#include "SchwarzTypes.hpp"
#include "BoundaryValues.h"
#include "RealInterpolant.hpp"
#include "ComplexInterpolant.hpp"
#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;

SUITE(InterpolantSuite)
{

TEST(InterpLabel)
{
    TEST_FILE("Real Interpolant")
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
    TEST_LINE("Real interpolation")

    RealInterpolant gi(RealBoundaryValues(BoundaryPoints(domain), h));
    auto&& zb = eval_points.vector();
    CHECK(approx_equal(gi(zb), h(zb), "absdiff", 10.*eps2pi));

    TEST_DONE
}

TEST_FIXTURE(Fixture, ComplexInterp)
{
    TEST_LINE("Complex interpolation")

    ComplexInterpolant gi(ComplexBoundaryValues(BoundaryPoints(domain), g));
    auto&& zb = eval_points.vector();
    CHECK(approx_equal(gi(zb), g(zb), "absdiff", 10.*eps2pi));

    TEST_DONE
}

} // SUITE
