#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralData.hpp"
#include "SpectralSolution.hpp"
#include "UnitCircleDomain.hpp"

using namespace ModifiedSchwarz;

cvecd polesInHoles(const cvecd& z, const UnitCircleDomain& D)
{
    cvecd w(z.n_elem, arma::fill::zeros);

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
    uint N = 16;
    uint M = 2*N + 1;
    UnitCircleDomain D = domainExample3();
    auto zb = D.boundaryPoints(M);

    // Real part of a function.
    auto g = [&D](const cvecd& z) -> vecd { return arma::real(polesInHoles(z, D)); };

    cmatd a(M, D.m()+1);
    for (unsigned j = 0; j < D.m()+1; ++j)
        a.col(j) = arma::fft(g(zb.col(j)))/M;
    std::cout << a << std::endl;

    SpectralSolution sol(std::move(a), SpectralDataSPtr(new SpectralData(D)));

    std::cout << "Evaluating points:" << std::endl;
    std::cout << arma::join_horiz(arma::real(sol.eval(zb.col(0))), g(zb.col(0)));
    CHECK(arma::approx_equal(arma::real(sol.eval(zb.col(0))), g(zb.col(0)), "reldiff", eps2pi));
}
