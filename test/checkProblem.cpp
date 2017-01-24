#include "UnitTest++/UnitTest++.h"

#include "Problem.hpp"
#include "UnitCircleDomain.hpp"
#include "TestShared.hpp"

using namespace ModifiedSchwarz;

TEST(CallSolve)
{
    unsigned N = 128;
    auto D = domainExample3();
    //auto zb = D.boundaryPoints(N);
    auto g = [&D](const cx_mat& z) -> mat { return imag(polesInHoles(z, D)); };

    Problem problem(RealInterpolant(D, g(D.boundaryPoints(N))));
    Solution sol = problem.solve();

    cx_vec zt = vectorise(D.boundaryPoints(7));
    cx_vec actual = polesInHoles(zt, D);

//    std::cout << "Imag part check:\n"
//        << imag(actual) - sol.imagPart()(zt) << std::endl;
//
//    std::cout << "Real part check:\n"
//        << join_horiz(real(actual), sol.realPart()(zt)) << std::endl;
//
//    cx_vec err = polesInHoles(zt, D) - sol(zt);
//    std::cout << "max(abs(err) = " << max(abs(err)) << std::endl;

//    CHECK(false);
}
