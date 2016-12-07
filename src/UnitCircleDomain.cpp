#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
cmatd
UnitCircleDomain::boundaryPoints(unsigned npts)
{
    using namespace arma;

    cmatd zb(npts, m()+1, fill::zeros);
    cvecd circ = exp(i2pi*regspace<cvecd>(0, npts-1)/npts);

    zb(span::all, span(0)) = circ;
    for (unsigned j = 0; j < m(); ++j)
    {
        zb(span::all, span(j+1)) =  _centers(j) + _radii(j)*circ;
    }

    return zb;
}

////////////////////////////////////////////////////////////////////////
UnitCircleDomain domainExample3()
{
    cvecd centers{ ComplexDouble(-0.2517, 0.3129), ComplexDouble(0.2307, -0.4667) };
    vecd radii{ 0.2377, 0.1557 };

    return UnitCircleDomain(centers, radii);
}

}; // namespace ModifiedSchwarz
