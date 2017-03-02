#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralMethod.hpp"
#include "UnitCircleDomain.hpp"
#include "RealInterpolant.hpp"

#include "TestShared.hpp"

using namespace ModifiedSchwarz;
using namespace arma;

SUITE(SpectralMethodTest)
{

    class TestFixture
    {
            UnitCircleDomain _domain;
            cx_mat _boundaryPoints;
            cx_mat _functionValues;

        public:
            static constexpr unsigned npts = 200;

            TestFixture()
                : _domain(domainExample3()),
                  _boundaryPoints(_domain.boundaryPoints(npts)),
                  _functionValues(reshape(
                              testFunction(vectorise(_boundaryPoints)),
                              npts, _domain.m()+1))
            {}

            const UnitCircleDomain& domain() const { return _domain; }
            mat realPart() const { return real(_functionValues); }
            mat imaginaryPart() const { return imag(_functionValues); }

            cx_vec testFunction(const cx_vec& z)
            {
                return polesInHoles(z, _domain);
            }
    };

    TEST_FIXTURE(TestFixture, TestRHS)
    {
        const mat& imagPart = imaginaryPart();
        SpectralMethod method(Problem(domain(), imagPart));
        cx_vec rhs = method.computeRHS(100);

        cx_vec refRHS;
        CHECK(refRHS.load("../test/refRHS.dat"));

//        colvec abserr = abs(refRHS - rhs);
//        std::cout << " max absolute error: " << max(abserr) << std::endl;

        CHECK(approx_equal(rhs.head_rows(rhs.n_rows/2), refRHS, "absdiff", 1e-4));
    }

    TEST_FIXTURE(TestFixture, TestResidual)
    {
        const mat& imagPart = imaginaryPart();
        SpectralMethod method(Problem(domain(), imagPart));

        cx_vec rhs = method.computeRHS();
        const cx_mat& A = method.matrix();
        cx_vec x = solve(A, rhs);

        cx_vec res = rhs - A*x;
        CHECK(max(abs(res)/abs(rhs)) < 100*eps2pi);
    }

    TEST_FIXTURE(TestFixture, TestSolution)
    {
        SpectralMethod method(Problem(domain(), imaginaryPart()));
        Solution sol = method.solve();

        cx_mat bp(domain().boundaryPoints(10));
        // std::cout << abs(polesInHoles(cx_vec(vectorise(bp)), domain()) - sol(vectorise(bp)));

    }

}
