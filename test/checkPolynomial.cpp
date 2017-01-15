#include <iostream>
#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "Utility.hpp"

using namespace ModifiedSchwarz;
using namespace std::literals::complex_literals;

cx_vec a = { 1., -1.-2.i, -7.+4.i, 3.+6.i };
cx_vec x = { 3., -2.+1.i, -1. };
cx_vec y = { 0., 0., 8. };

TEST(Values)
{
    cx_vec pv = polyval(a, x);
    CHECK(arma::approx_equal(pv, y, "reldiff", 1e-14));
}
