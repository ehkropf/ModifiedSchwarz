#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralSolution.hpp"
#include "UnitCircleDomain.hpp"

using namespace ModifiedSchwarz;

cvecd polesInHoles(const cvecd& z, const UnitCircleDomain& D)
{
    cvecd w(z.n_elem, arma::fill::zeros);

    cvecd::const_iterator d = D.centers().begin();
    vecd::const_iterator q = D.radii().begin();
    for (; d != D.centers().end() && q != D.radii().end(); ++d, ++q)
        w += *q/(z - *d)/i2pi;

    return w;
}

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

uint m = D.m();
