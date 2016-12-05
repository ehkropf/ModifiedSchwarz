#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralSolution.hpp"
#include "UnitCircleDomain.hpp"

using namespace ModifiedSchwarz;

UnitCircleDomain D = domainExample3();

cvecd polesInHoles(const cvecd& z)
{
    cvecd w(z.n_elem, arma::fill::zeros);
    cvecd dv = D.centers();
    vecd qv = D.radii();

    cvecd::const_iterator d = dv.begin();
    vecd::const_iterator q = qv.begin();
    for (; d != dv.end() && q != qv.end(); ++d, ++q)
        w += *q/(z - *d)/i2pi;

    return w;
}
