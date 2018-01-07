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
#include "UnitCircleDomain.hpp"
#include "CauchyInterpolant.hpp"
#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;

SUITE(CauchyInterpolantTests)
{

TEST(CauchyInterpLabel)
{
    TEST_FILE("Cauchy interpolation")
}

struct Fixture
{
    // using Function = std::function<tbd(tbd)>;
    UnitCircleDomain domain;
    cx_vec test_point_inside;

    Fixture()
        : domain(domainExample3()),
          test_point_inside{cx_double(0.66822, 0.11895), cx_double(0.667, 0.117)}
    {}
};

TEST_FIXTURE(Fixture, ValueCheck)
{
    TEST_LINE("Simple interpolation")

    auto g = [](const cx_vec& z){ return exp(z); };
    CauchyInterpolant f(ComplexBoundaryValues(BoundaryPoints(domain), g));

    TEST_OUT("Base values:\n" << g(test_point_inside))
    TEST_OUT("Interp values:\n" << f(test_point_inside))

    CHECK(arma::approx_equal(g(test_point_inside), f(test_point_inside), "absdiff", 1e-10));

    TEST_DONE
}

} // SUITE
