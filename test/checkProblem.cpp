#include "UnitTest++.h"

#include "Problem.hpp"
#include "UnitCircleDomain.hpp"
#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;

TEST(BasicSolve)
{
    unsigned N = 128;
    auto D = domainExample3();
    auto g = [&D](const cx_mat& z) -> mat { return imag(polesInHoles(z, D)); };

    Problem problem(RealInterpolant(D, g(D.boundaryPoints(N))));
    Solution sol = problem.solve();

    cx_vec zt = vectorise(D.boundaryPoints(7));
    cx_vec actual = polesInHoles(zt, D);

    CHECK(arma::approx_equal(polesInHoles(zt, D), sol(zt), "reldiff", 1e-6));
}
