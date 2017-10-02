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

#include "Solution.hpp"
#include "UnitCircleDomain.hpp"
#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;

SUITE(SolutionTest)
{

class TestFixture
{
    public:
    UnitCircleDomain domain;
    RealInterpolant realPart;
    RealInterpolant imagPart;

    static constexpr unsigned npts = 200;

    TestFixture() : domain(domainExample3())
    {
        cx_mat zb = domain.boundaryPoints(npts);

        realPart = RealInterpolant(domain, real(polesInHoles(zb, domain)));
        imagPart = RealInterpolant(domain, imag(polesInHoles(zb, domain)));
    }
};

TEST_FIXTURE(TestFixture, EvalSolution)
{
    Solution sol(realPart, colvec(domain.m()+1, arma::fill::zeros), imagPart);

    cx_mat zb = domain.boundaryPoints(10);
    CHECK(approx_equal(polesInHoles(cx_vec(vectorise(zb)), domain), sol(vectorise(zb)), "reldiff", 10*eps2pi));
}

TEST(StoreData)
{
}

}
