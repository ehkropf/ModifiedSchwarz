#include "UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralMethod.hpp"
#include "SpectralData.hpp"
#include "UnitCircleDomain.hpp"
#include "RealInterpolant.hpp"

#include "TestFunctions.hpp"

using namespace ModifiedSchwarz;
using namespace arma;

SUITE(SpectralMethodTest)
{

    class TestFixture
    {
        public:
            UnitCircleDomain domain;
            cx_mat boundaryPoints;
            cx_mat functionValues;

            static constexpr unsigned npts = 200;

            TestFixture()
                : domain(domainExample3()),
                  boundaryPoints(domain.boundaryPoints(npts)),
                  functionValues(reshape(
                              testFunction(vectorise(boundaryPoints)),
                              npts, domain.m()+1))
            {}

            mat realPart() const { return real(functionValues); }
            mat imaginaryPart() const { return imag(functionValues); }

            cx_vec testFunction(const cx_vec& z)
            {
                return polesInHoles(z, domain);
            }
    };

    TEST_FIXTURE(TestFixture, TestRHS)
    {
        const mat& imagPart = imaginaryPart();
        SpectralConstants::setTruncation(64);
        SpectralMethod method(Problem(domain, imagPart));
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
        SpectralMethod method(Problem(domain, imagPart));

        cx_vec rhs = method.computeRHS();
        const cx_mat& A = method.matrix();
        cx_vec x = solve(A, rhs);

        cx_vec res = rhs - A*x;
        CHECK(max(abs(res)/abs(rhs)) < 100*eps2pi);
    }

    TEST_FIXTURE(TestFixture, TestSolution)
    {
        SpectralMethod method(Problem(domain, imaginaryPart()));
        Solution sol = method.solve();

        SpectralData& data = *std::dynamic_pointer_cast<SpectralData>(sol.solverDataPtr());
        CHECK(data.domain() == domain);

        cx_vec bv(vectorise(domain.boundaryPoints(10)));
        CHECK(approx_equal(polesInHoles(cx_vec(vectorise(bv)), domain), sol(vectorise(bv)), "absdiff", 1e-6));
    }

}
