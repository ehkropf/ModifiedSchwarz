#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralData.hpp"
#include "SpectralSolution.hpp"
#include "UnitCircleDomain.hpp"

using namespace ModifiedSchwarz;

cx_vec polesInHoles(const cx_vec& z, const UnitCircleDomain& D)
{
    cx_vec w(z.n_elem, arma::fill::zeros);

    auto d = D.centers().begin();
    auto q = D.radii().begin();
    for (; d != D.centers().end() && q != D.radii().end(); ++d, ++q)
        w += *q/(z - *d)/i2pi;

    return w;
}

TEST(SolutionEval)
{
    /*
     * Compute coefficients for a solution via FFT.
     *
     * 1. For a truncation level of N (in the spectral formulation), we need
     *    M = 2*N + 1 points on each boundary.
     * 2. Get the real part of a function at M points on each boundary.
     * 3. The "solution" on each boundary is given by the FFT of the real part.
     */
    unsigned N = 16;
    unsigned M = 2*N + 1;
    auto D = domainExample3();
    auto zb = D.boundaryPoints(M);

    // Real part of a function.
    auto g = [&D](const cx_vec& z) -> vec { return real(polesInHoles(z, D)); };

    cx_mat a(M, D.m()+1);
    for (unsigned j = 0; j < D.m()+1; ++j)
        a.col(j) = fft(g(zb.col(j)))/M;

    SpectralSolution sol(std::move(a), SpectralDataSPtr(new SpectralData(D)));

    CHECK(approx_equal(real(sol.eval(zb.col(0))), g(zb.col(0)), "absdiff", eps2pi));
}
