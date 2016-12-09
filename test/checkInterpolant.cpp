#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.cpp"
#include "RealInterpolant.hpp"

using namespace ModifiedSchwarz;

cx_mat polesInHolesRI(const cx_mat& z, const UnitCircleDomain& D)
{
    cx_mat w(size(z), arma::fill::zeros);

    auto d = D.centers().begin(), de = D.centers().end();
    auto q = D.radii().begin(), qe = D.radii().end();
    for (; d != de && q != qe; ++d, ++q)
        w += *q/(z - *d)/i2pi;

    return w;
}

TEST(BasicInterp)
{
    unsigned N = 128;
    auto D = domainExample3();
    auto zb = D.boundaryPoints(N);

    // Real part of sample function.
    auto g = [&D](const cx_mat& z) -> mat { return real(polesInHolesRI(z, D)); };

    RealInterpolant gi(D, g(zb));
    CHECK(approx_equal(gi.eval(vectorise(zb)), real(vectorise(g(zb))), "absdiff", eps2pi));
}
