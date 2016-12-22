#include "TestShared.hpp"

namespace ModifiedSchwarz
{

cx_vec polesInHoles(const cx_vec& z, const UnitCircleDomain& D)
{
    cx_vec w(z.n_elem, arma::fill::zeros);

    for (auto d = D.centers().begin(); d != D.centers().end(); ++d)
        w += 1./(z - *d);

    return w;
}

}; // namespace ModifiedSchwarz
