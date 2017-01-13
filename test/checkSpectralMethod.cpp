#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralMethod.hpp"
#include "UnitCircleDomain.hpp"

#include "TestShared.hpp"

using namespace ModifiedSchwarz;
using namespace arma;

static auto D = domainExample3();
//static auto g = [D](const cx_vec& z) -> colvec { return imag(polesInHoles(z, D)); };
colvec g(const cx_vec& z)
{
    return imag(polesInHoles(z, D));
}

TEST(theRHS)
{
    mat imagPart = reshape(g(vectorise(D.boundaryPoints(200))), 200, D.m()+1);
    SpectralMethod method(Problem(D, imagPart));
    cx_vec rhs = method.computeRHS(100);

    cx_vec refRHS;
    CHECK(refRHS.load("../test/refRHS.dat"));

//    colvec abserr = abs(refRHS - rhs);
//    std::cout << " max absolute error: " << max(abserr) << std::endl;

    CHECK(approx_equal(rhs.head_rows(rhs.n_rows/2), refRHS, "absdiff", 1e-4));
}

TEST(residual)
{
    mat imagPart = reshape(g(vectorise(D.boundaryPoints(200))), 200, D.m()+1);
    SpectralMethod method(Problem(D, imagPart));

    cx_vec rhs = method.computeRHS();
    const cx_mat& A = method.matrix();
    cx_vec x = solve(A, rhs);

    cx_vec res = rhs - A*x;
    CHECK(max(abs(res)/abs(rhs)) < 100*eps2pi);
}
