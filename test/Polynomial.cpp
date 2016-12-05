#include <iostream>
#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"

using namespace ModifiedSchwarz;
using namespace std::literals::complex_literals;

cvecd a = { 1., -1.-2.i, -7.+4.i, 3.+6.i };
cvecd x = { 3., -2.+1.i, -1. };
cvecd y = { 0., 0., 8. };

TEST(Values)
{
    cvecd pv = polyval(a, x);
    CHECK(arma::approx_equal(pv, y, "reldiff", 1e-14));
}
