#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
cx_vec polyval(const cx_vec& a, const cx_vec& x)
{
    cx_vec pn(x.n_elem, arma::fill::zeros);
    for (cx_mat::const_iterator i = a.begin(); i != a.end(); ++i)
        pn = pn%x + *i;

    return pn;
}

}; // namespace ModifiedSchwarz
