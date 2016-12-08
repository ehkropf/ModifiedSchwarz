#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.cpp"
#include "RealInterpolant.hpp"

using namespace ModifiedSchwarz;

cx_mat polesInHoles(const cx_mat& z, const UnitCircleDomain& D)
{
    cx_mat w(size(z), arma::fill::zeros);

    auto d = D.centers().begin();
    auto q = D.radii().begin();
    for (; d != D.centers().end() && q != D.radii().end(); ++d, ++q)
        w += *q/(z - *d)/i2pi;

    return w;
}

TEST(BasicInterp)
{
    unsigned N = 32;
    auto D = domainExample3();
    auto zb = D.boundaryPoints(N);

    // Real part of sample function.
    auto g = [&D](const cx_mat& z) -> mat { return real(polesInHoles(z, D)); };

    RealInterpolant gi(D, g(zb));
    CHECK(approx_equal(gi.eval(zb), g(zb), "absdiff", eps2pi));
}
