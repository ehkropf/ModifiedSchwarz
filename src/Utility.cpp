#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
cvecd polyval(const cvecd& a, const cvecd& x)
{
    cvecd pn(x.n_elem, arma::fill::zeros);
    for (cmatd::const_iterator i = a.begin(); i != a.end(); ++i)
        pn = pn%x + *i;

    return pn;
}

}; // namespace ModifiedSchwarz
