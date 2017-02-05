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

        std::cout << "m = " << m << "\nN = " << N << std::endl;

        const cx_mat& icoef = reffun.coefficients();
        std::cout << "Interp coeff size: " << icoef.n_rows << "x" << icoef.n_cols << std::endl;
        std::cout << "Interp constants:\n" << reffun.constants();

        cx_vec cv(m+1);
        cx_mat a(N, m+1);
        for (unsigned j = 0; j <= m; ++j)
        {
            unsigned offset = j > 0 ? (j-1)*(N+1) + N : 0;
            cv(j) = j > 0 ? x(offset) : 0.;
            a.col(j) = arma::flipud(x.rows(offset+1, offset+N));
        }
        std::cout << "Calc constants:\n" << real(cv);
        std::cout << "Calc coeff size: " << a.n_rows << "x" << a.n_cols << std::endl;

        std::cout << "Coeff on C0 (first " << icoef.n_rows << ")";
        std::cout << arma::join_horiz(icoef.col(0), flipud(x.rows(0, icoef.n_rows-1)));
//        std::cout << arma::join_horiz(icoef.col(0), a.col(0).rows(0, icoef.n_rows-1));
        // std::cout << "\n" << x;

        std::cout << std::endl;
    }

}
