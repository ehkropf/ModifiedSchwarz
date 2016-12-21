#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralMethod.hpp"
#include "UnitCircleDomain.hpp"

#include "TestShared.hpp"

TEST(theRHS)
{
    using namespace ModifiedSchwarz;
    using namespace arma;

    auto D = domainExample3();
    auto g = [&D](const cx_vec& z) -> colvec { return real(polesInHoles(z, D)); };

    mat imagPart = reshape(g(vectorise(D.boundaryPoints(200))), 200, D.m()+1);
    SpectralMethod method(Problem(D, imagPart));
    cx_vec rhs = method.computeRHS(100);

    cx_vec refRHS;
    CHECK(refRHS.load("../test/refRHS.dat"));

    std::cout << join_horiz(rhs, refRHS);

    CHECK(approx_equal(rhs, refRHS, "absdiff", eps2pi));
}
