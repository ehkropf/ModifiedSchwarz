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

#include "Problem.hpp"
#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;

TEST(ProblemLabel)
{
    TEST_FILE("Problem check")
}

SUITE(ProbemTests)
{
    class Fixture
    {
        public:
            UnitCircleDomain domain;

            Fixture() : domain(domainExample3()) {}
    };

    TEST_FIXTURE(Fixture, BasicSolve)
    {
        TEST_LINE("Basic solve")

        unsigned N = 128;
        const UnitCircleDomain& D = domain;
        auto g = [&D](const cx_mat& z) -> mat { return imag(polesInHoles(z, D)); };

        Problem problem(RealInterpolant(RealBoundaryValues(BoundaryPoints(domain, N), g)));
        Solution sol = problem.solve();

        cx_vec zt = vectorise(D.boundaryPoints(7));
        cx_vec actual = polesInHoles(zt, D);

        CHECK(arma::approx_equal(polesInHoles(zt, D), sol(zt), "reldiff", 1e-6));

        TEST_OK
    }

}
