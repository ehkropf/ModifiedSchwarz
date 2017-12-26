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

using namespace ModifiedSchwarz;

TEST(UnitCircLabel)
{
    TEST_OUT("-----========== Unit Circle Domain check ==========-----")
}

class TestFixture
{
public:
    UnitCircleDomain domain;

    TestFixture() : domain(domainExample3()) {}
};

TEST_FIXTURE(TestFixture, Points)
{
    TEST_LINE("Points")

    unsigned n = 16;
    UnitCircleDomain D = domainExample3();
    cx_mat zb = D.boundaryPoints(n);

    CHECK_EQUAL(zb.n_cols, D.m()+1);
    CHECK_EQUAL(zb.n_rows, n);

    using namespace arma;
    double tol = std::numeric_limits<double>::epsilon()*2*std::acos(-1);
    CHECK(approx_equal(abs(zb.col(0)), colvec(n, fill::ones), "reldiff", tol));
    for (unsigned j = 0; j < D.m(); ++j)
        CHECK(approx_equal(abs(zb.col(j+1) - D.centers()(j)),
                           D.radii()(j)*colvec(n, fill::ones), "reldiff", tol));

    TEST_OK
}

TEST_FIXTURE(TestFixture, InsideDomain)
{
    TEST_LINE("Inside domain")

    const unsigned npts = 200;
    const unsigned expected = 28541;

    auto mask = domain.inDomain(domain.ngrid(npts));
    unsigned counted = sum(vectorise(mask));
    if (counted != expected)
    {
        TEST_OUT("expected " << expected << " points in domain, found " << counted << " points instead.")
        CHECK(false);
    }
    else
    {
        CHECK(true);
        TEST_OK
    }
}

TEST_FIXTURE(TestFixture, OnBoundary)
{
    TEST_LINE("On boundary")

    auto points = domain.boundaryPoints(257);
    for (unsigned j = 0; j <= domain.m(); ++j)
    {
        auto mask = domain.isOnBoundary(points.col(j));
        auto notOn = 257 - sum(vectorise(mask));
        if (notOn)
        {
            TEST_OUT("missed " << notOn << " points on boundary " << j);
            CHECK(false);
        }
        else
            CHECK(true);
    }

    TEST_OK
}
