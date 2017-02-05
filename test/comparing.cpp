#include <iostream>
#include "SpectralMethod.hpp"
#include "UnitCircleDomain.hpp"
#include "RealInterpolant.hpp"
#include "TestShared.hpp"

int main()
{
    using namespace ModifiedSchwarz;

    unsigned N = 64; //! Number of points on each boundary/rows in each column for data.
    auto D = domainExample3();
    unsigned m = D.m();
    cx_mat bPoints = D.boundaryPoints(N);
    cx_mat fPoints = polesInHoles(bPoints, D);

    //! Get coefficients for real interpolant of real part via fft.
    unsigned M = (unsigned)std::ceil((N - 1)/2.);
    std::cout << "N = " << N << "; M = " << M << std::endl;

    cx_mat cFFT(fft(real(fPoints))/N);
    cFFT = cFFT.rows(0, M); // Needs flipud to be used with polyval.

    //! Get solution of spectral method; attempt to extract coefficients.
    SpectralMethod method(Problem(D, imag(fPoints)));
    cx_vec rhs = method.computeRHS();
    const cx_mat& A = method.matrix();
    cx_vec x = solve(A, rhs);

    cx_mat cSM(M+1, m+1);
    cSM(0, 0) = 0.;
    cSM.col(0).rows(1, M) = x.rows(0, M-1);
    for (unsigned j = 1; j <= m; ++j)
    {
        unsigned offset = (j-1)*(N+1) + N;
        cSM.col(j) = x.rows(offset, offset+M);
    }

    mat relErr = abs(cFFT - cSM);
    for (unsigned j = 0; j < cSM.n_cols; ++j) relErr.col(j) /= max(abs(cFFT.col(j)));
    std::cout << relErr;

    return 0;
}
