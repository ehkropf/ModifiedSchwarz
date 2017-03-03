#include "UnitTest++.h"

#include "Solution.hpp"
#include "UnitCircleDomain.hpp"
#include "TestShared.hpp"

using namespace ModifiedSchwarz;

SUITE(SolutionTest)
{

class TestFixture
{
    public:
    UnitCircleDomain domain;
    RealInterpolant realPart;
    RealInterpolant imagPart;

    static constexpr unsigned npts = 200;

    TestFixture() : domain(domainExample3())
    {
        cx_mat zb = domain.boundaryPoints(npts);

        realPart = RealInterpolant(domain, real(polesInHoles(zb, domain)));
        imagPart = RealInterpolant(domain, imag(polesInHoles(zb, domain)));
    }
};

TEST_FIXTURE(TestFixture, EvalSolution)
{
    Solution sol(realPart, colvec(domain.m()+1, arma::fill::zeros), imagPart);

    cx_mat zb = domain.boundaryPoints(10);
    CHECK(approx_equal(polesInHoles(cx_vec(vectorise(zb)), domain), sol(vectorise(zb)), "reldiff", 10*eps2pi));
}

TEST(StoreData)
{
}

}
