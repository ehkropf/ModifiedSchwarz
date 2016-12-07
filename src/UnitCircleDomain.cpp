#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
cx_mat
UnitCircleDomain::boundaryPoints(unsigned npts)
{
    using namespace arma;

    cx_mat zb(npts, m()+1, fill::zeros);
    cx_vec circ = exp(i2pi*regspace<cx_vec>(0, npts-1)/npts);

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
    cx_vec centers{ cx_double(-0.2517, 0.3129), cx_double(0.2307, -0.4667) };
    colvec radii{ 0.2377, 0.1557 };

    return UnitCircleDomain(centers, radii);
}

}; // namespace ModifiedSchwarz
