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
#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;

TEST(InterpLabel)
{
    TEST_FILE("Real Interpolant")
}

TEST(BasicInterp)
{
    unsigned N = 100;
    auto D = domainExample3();
    auto zb = BoundaryPoints(D, N);

    TEST_LINE("Basic interpolation")

    // Real part of sample function.
    auto g = [&D](const cx_mat& z) -> mat { return real(polesInHoles(z, D)); };

    RealInterpolant gi(D, RealBoundaryValues(BoundaryPoints(D), g));
    CHECK(approx_equal(gi(zb.vector()), g(zb.vector()), "absdiff", 10.*eps2pi));

    TEST_OK
}
