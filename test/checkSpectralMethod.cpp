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

    TEST_FIXTURE(TestFixture, TestPieces)
    {
        SpectralMethod method(Problem(domain(), imaginaryPart()));

        mat realPart64 = real(polesInHoles(domain().boundaryPoints(64), domain()));
        RealInterpolant reffun(domain(), realPart64);

        cx_vec rhs = method.computeRHS();
        const cx_mat& A = method.matrix();
        cx_vec x = solve(A, rhs);

        std::cout << std::endl;
        std::cout << "n_elem in x: " << x.n_elem << std::endl;

        unsigned m = domain().m();
        unsigned N = (A.n_cols/2 - m)/(m + 1);
        unsigned M = (unsigned)std::ceil((N - 1)/2.);

        std::cout << "m = " << m << "\nN = " << N << std::endl;

        const cx_mat& icoef = reffun.coefficients();
        std::cout << "Interp coeff size: " << icoef.n_rows << "x" << icoef.n_cols << std::endl;
        std::cout << "Interp constants:\n" << reffun.constants();

        cx_vec cv(m+1);
        cx_mat a(M, m+1);
        cv(0) = 0.;
        a.col(0) = flipud(x.rows(0, M-1));
        for (unsigned j = 1; j <= m; ++j)
        {
            unsigned offset = (j-1)*(N+1) + N;
            cv(j) = x(offset);
            a.col(j) = flipud(x.rows(offset+1, offset+M));
        }
        std::cout << "Calc constants:\n" << real(cv);
        std::cout << "Calc coeff size: " << a.n_rows << "x" << a.n_cols << std::endl;

        for (unsigned j = 0; j <= m; ++j)
        {
            std::cout << "Coeff on C" << j << ", iterpolated vs. calculated.\n";
            std::cout << join_horiz(icoef.col(j).rows(0, M-1), a.col(j)) << std::endl;
        }

        std::cout << std::endl;
    }

}
