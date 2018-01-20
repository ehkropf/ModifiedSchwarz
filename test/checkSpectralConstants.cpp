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

#include "SpectralConstants.h"

using namespace ModifiedSchwarz;

TEST(ConstantsLabel)
{
    TEST_FILE("Spectral Constants")
}

TEST(TrapPoints)
{
    TEST_LINE("Trapezoidal rule points")

    unsigned pts = SpectralConstants::kTrapezoidalPoints();
    SpectralConstants::setTrapezoidalPoints(pts + 10);
    CHECK_EQUAL(pts + 10, SpectralConstants::kTrapezoidalPoints());
    CHECK_EQUAL(pts, SpectralConstants::kTrapezoidalPoints());

    TEST_OK
}

TEST(Truncation)
{
    TEST_LINE("Truncation")

    unsigned trunc = SpectralConstants::kSpectralTruncation();
    SpectralConstants::setTruncation(trunc + 10);
    CHECK_EQUAL(trunc + 10, SpectralConstants::kSpectralTruncation());
    CHECK_EQUAL(trunc, SpectralConstants::kSpectralTruncation());

    TEST_OK
}
