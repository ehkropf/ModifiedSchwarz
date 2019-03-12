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

#include "BoundaryValues.hpp"

using namespace ModifiedSchwarz;

SUITE(BoundaryValueSuite)
{

TEST(BoundaryValueLabel)
{
    TEST_FILE("BoundaryValue check");
}

class TestFixture
{
public:
    UnitCircleDomain domain;
    ComplexBoundaryValues::Function g;
    ComplexBoundaryValues cbvals;
    RealBoundaryValues::Function h;
    RealBoundaryValues rbvals;

    TestFixture() : domain(domainExample3())
    {
        g = [this](const cx_vec& z) -> cx_vec {return polesInHoles(z, domain); };
        cbvals = ComplexBoundaryValues(BoundaryPoints(domain), g);
        h = [this](const cx_vec& z) -> colvec {return real(polesInHoles(z, domain)); };
        rbvals = RealBoundaryValues(BoundaryPoints(domain), h);
    }

    cx_vec tmpfun(const cx_vec& z)
    {
        cx_vec w(size(z), arma::fill::zeros);
        for (auto & d : domain.centers()) w += 1./(z - d);
        return w;
    }
};

TEST_FIXTURE(TestFixture, BValSizeCheck)
{
    TEST_LINE("Size check");

    CHECK_EQUAL(cbvals.points().matrix().n_cols, domain.connectivity());
    CHECK_EQUAL(cbvals.values().n_cols, domain.connectivity());
    CHECK_EQUAL(cbvals.values().n_rows, cbvals.points().matrix().n_rows);

    CHECK_EQUAL(rbvals.points().matrix().n_cols, domain.connectivity());
    CHECK_EQUAL(rbvals.values().n_cols, domain.connectivity());
    CHECK_EQUAL(rbvals.values().n_rows, rbvals.points().matrix().n_rows);

    TEST_DONE;
}

TEST_FIXTURE(TestFixture, BValValueCheck)
{
    TEST_LINE("Value check");

    CHECK(approx_equal(vectorise(cbvals.values()), g(cbvals.points().vector()), "absdiff", 1e-10));
    CHECK(approx_equal(vectorise(rbvals.values()), h(rbvals.points().vector()), "absdiff", 1e-10));

    const colvec firsttwo{ 1.70211113721082, 1.68234033981218 };
    REQUIRE CHECK(approx_equal(h(rbvals.points().vector()).rows(0, 1), firsttwo, "absdiff", 1e-10));
    CHECK(approx_equal(rbvals.values()(arma::span(0, 1), 0), firsttwo, "absdiff", 1e-10));

    TEST_DONE;
}

} // SUITE
