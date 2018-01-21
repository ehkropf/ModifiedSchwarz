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

TEST(BoundaryValueLabel)
{
    TEST_FILE("BoundaryValue check")
}

class TestFixture
{
public:
    using CompFunction = ComplexBoundaryValues::Function;
    using RealFunction = RealBoundaryValues::Function;

    UnitCircleDomain domain;
    CompFunction g;
    ComplexBoundaryValues cbvals;
    RealFunction h;
    RealBoundaryValues rbvals;

    TestFixture() : domain(domainExample3())
    {
        const UnitCircleDomain& D = domain;
        g = [&D](const cx_vec& z){return polesInHoles(z, D); };
        cbvals = ComplexBoundaryValues(BoundaryPoints(domain), g);
        h = [&D](const cx_vec& z){return real(polesInHoles(z, D)); };
        rbvals = RealBoundaryValues(BoundaryPoints(domain), h);
    }
};

TEST_FIXTURE(TestFixture, BValSizeCheck)
{
    TEST_LINE("Size check")

    CHECK_EQUAL(cbvals.points().matrix().n_cols, domain.connectivity());
    CHECK_EQUAL(cbvals.values().n_cols, domain.connectivity());
    CHECK_EQUAL(cbvals.values().n_rows, cbvals.points().matrix().n_rows);

    CHECK_EQUAL(rbvals.points().matrix().n_cols, domain.connectivity());
    CHECK_EQUAL(rbvals.values().n_cols, domain.connectivity());
    CHECK_EQUAL(rbvals.values().n_rows, rbvals.points().matrix().n_rows);

    TEST_OK
}

TEST_FIXTURE(TestFixture, BValValueCheck)
{
    TEST_LINE("Value check")

    CHECK(approx_equal(vectorise(cbvals.values()), g(cbvals.points().vector()), "absdiff", 1e-10));
    CHECK(approx_equal(vectorise(rbvals.values()), h(rbvals.points().vector()), "absdiff", 1e-10));

    TEST_OK
}
