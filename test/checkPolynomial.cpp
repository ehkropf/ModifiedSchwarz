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

#include <iostream>
#include "UnitTest.h"

#include "SchwarzTypes.h"
#include "Utility.hpp"

using namespace ModifiedSchwarz;
using namespace std::literals::complex_literals;

cx_vec a = { 1., -1.-2.i, -7.+4.i, 3.+6.i };
cx_vec x = { 3., -2.+1.i, -1. };
cx_vec y = { 0., 0., 8. };

TEST(PolyLabel)
{
    TEST_FILE("Polynomial");
}

TEST(Values)
{
    TEST_LINE("Polynomial values");

    cx_vec pv = polyval(a, x);
    CHECK(arma::approx_equal(pv, y, "reldiff", 1e-14));

    TEST_DONE;
}
