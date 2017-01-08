#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.cpp"
#include "RealInterpolant.hpp"
#include "TestShared.hpp"

using namespace ModifiedSchwarz;

TEST(BasicInterp)
{
    unsigned N = 128;
    auto D = domainExample3();
    auto zb = D.boundaryPoints(N);

    // Real part of sample function.
    auto g = [&D](const cx_mat& z) -> mat { return real(polesInHoles(z, D)); };

    RealInterpolant gi(D, g(zb));
    CHECK(approx_equal(gi.eval(vectorise(zb)), real(vectorise(g(zb))), "absdiff", 10.*eps2pi));
}
