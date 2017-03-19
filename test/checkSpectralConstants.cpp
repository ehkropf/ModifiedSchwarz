#include <iostream>

#include "UnitTest++.h"
#include "SpectralConstants.hpp"

using namespace ModifiedSchwarz;

TEST(TrapPoints)
{
    unsigned pts = SpectralConstants::kTrapezoidalPoints();
    SpectralConstants::setTrapezoidalPoints(pts + 10);
    CHECK_EQUAL(pts + 10, SpectralConstants::kTrapezoidalPoints());
    CHECK_EQUAL(pts, SpectralConstants::kTrapezoidalPoints());
}

TEST(Truncation)
{
    unsigned trunc = SpectralConstants::kSpectralTruncation();
    SpectralConstants::setTruncation(trunc + 10);
    CHECK_EQUAL(trunc + 10, SpectralConstants::kSpectralTruncation());
    CHECK_EQUAL(trunc, SpectralConstants::kSpectralTruncation());
}
