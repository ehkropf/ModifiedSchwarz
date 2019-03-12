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

#include "ClosureInterpolant.h"

using namespace ModifiedSchwarz;

SUITE(ClosureInterpSuite)
{

TEST(ClosureInterpLabel)
{
    TEST_FILE("Closure interpolant");
}

struct Fixture
{
    static constexpr unsigned N = 100;

    UnitCircleDomain domain;
    BoundaryPoints boundary_pts;
    cx_vec interior_points;
    ComplexBoundaryValues::Function g;
    ClosureInterpolant f;

    Fixture()
        : domain(domainExample3()),
          boundary_pts(BoundaryPoints(domain, N)),
          interior_points{cx_double(0.66822, 0.11895), cx_double(0.667, 0.117)}
    {
        g = [this](const cx_vec& z) -> cx_vec { return polesInHoles(z, domain); };
        f = ClosureInterpolant(ComplexBoundaryValues(BoundaryPoints(domain), g));
    }
};

TEST_FIXTURE(Fixture, BoundaryInterp)
{
    TEST_LINE("Points on the boundary");

    cx_vec&& zb = boundary_pts.vector();
    CHECK(arma::approx_equal(f(zb), g(zb), "absidff", 1e-10));

    TEST_DONE;
}

TEST_FIXTURE(Fixture, InteriorInterp)
{
    TEST_LINE("Points in the interior");

    const cx_vec refv{g(interior_points)};
    const cx_vec iv{f(interior_points)};

#ifdef DEBUG
    const colvec absdiff{arma::abs(refv - iv)};
    const uvec big{arma::find(absdiff > 1e-10)};
    SDEBUG("Have " << big.n_elem << " values away from expected. Max abs diff seen: " << arma::max(absdiff));
    if (refv.has_inf() || refv.has_nan())
    {
        SDEBUG("Reference vector has infinite or nan values.");
    }
    if (iv.has_inf() || iv.has_nan())
    {
        SDEBUG("Interpolated vector has infinite or nan values.");
    }
#endif

    CHECK(arma::approx_equal(iv, refv, "absdiff", 1e-10));

    TEST_DONE;
}

TEST_FIXTURE(Fixture, CombinedInterp)
{
    TEST_LINE("Points on boundary and interior");

    uvec m = arma::regspace<uvec>(0, 20, 299);
    cx_vec zb = boundary_pts.vector();
    zb = zb(m);
    cx_vec zz = arma::join_cols(zb, interior_points);
    CHECK(arma::approx_equal(f(zz), g(zz), "absdiff", 1e-10));

    TEST_DONE;

    exit(0);
}

} // SUITE
