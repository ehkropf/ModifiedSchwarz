#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
cx_vec polyval(const cx_vec& a, const cx_vec& x)
{
    cx_vec pn(x.n_elem, arma::fill::zeros);
    for (const cx_double& ai : a) pn = pn%x + ai;

    return pn;
}

}; // namespace ModifiedSchwarz
