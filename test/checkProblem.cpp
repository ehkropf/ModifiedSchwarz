#include "UnitTest++/UnitTest++.h"

#include "Problem.hpp"
#include "UnitCircleDomain.hpp"
#include "TestShared.hpp"

using namespace ModifiedSchwarz;

TEST(solve1)
{
    unsigned N = 128;
    auto D = domainExample3();
    auto zb = D.boundaryPoints(N);
    auto g = [&D](const cx_mat& z) -> mat { return real(polesInHoles(z, D)); };

    Problem problem(RealInterpolant(D, g(zb)));
    Solution solution = problem.solve();

    CHECK(false);
}
