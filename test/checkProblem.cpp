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

#include "UnitTest++.h"

#include "Problem.hpp"
#include "UnitCircleDomain.hpp"
#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;

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
        unsigned N = 128;
        auto& D = domain;
        auto g = [&D](const cx_mat& z) -> mat { return imag(polesInHoles(z, D)); };

        Problem problem(RealInterpolant(D, g(D.boundaryPoints(N))));
        Solution sol = problem.solve();

        cx_vec zt = vectorise(D.boundaryPoints(7));
        cx_vec actual = polesInHoles(zt, D);

        CHECK(arma::approx_equal(polesInHoles(zt, D), sol(zt), "reldiff", 1e-6));
    }

}
