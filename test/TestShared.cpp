#include "TestShared.hpp"

namespace ModifiedSchwarz
{

cx_vec polesInHoles(const cx_vec& z, const UnitCircleDomain& D)
{
    cx_vec w(z.n_elem, arma::fill::zeros);

    auto d = D.centers().begin();
    auto q = D.radii().begin();
    for (; d != D.centers().end() && q != D.radii().end(); ++d, ++q)
        w += *q/(z - *d)/i2pi;

    return w;
}

}; // namespace ModifiedSchwarz
