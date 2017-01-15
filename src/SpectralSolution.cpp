#include "SpectralSolution.hpp"
#include "Utility.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
cx_vec
SpectralSolution::extractConstants(const cx_mat& solMat)
{
    return cx_vec(solMat.row(0).st());
}

////////////////////////////////////////////////////////////////////////
cx_mat
SpectralSolution::extractCoefficients(const cx_mat& solMat)
{
    using namespace arma;
    unsigned N = (solMat.n_rows - 1)/2;

    return join_vert(flipud(solMat.rows(1, N)),
                     cx_mat(1, solMat.n_cols, fill::zeros));
}

////////////////////////////////////////////////////////////////////////
/*!
 *
 */
cx_vec
SpectralSolution::eval(const cx_vec& z)
{
    using namespace arma;

    const UnitCircleDomain& D = _domainData->domain();
    const cx_vec& dv = D.centers();
    const colvec& qv = D.radii();
    const cx_vec& kv = _constants;
    const cx_mat& a = _coefficients;

    cx_vec w(z.n_elem);
    for (unsigned j = 0; j < D.m()+1; ++j)
    {
        const cx_double dj = j > 0 ? dv(j-1) : 0.;
        const double qj = j > 0 ? qv(j-1) : 1.;

        uvec L = D.isOnC(j, z);
        if (L.n_elem)
            w.elem(L) = kv(j) + 2.*polyval(a.col(j), (z(L) - dj)/qj);
    }

    return w;
}

}; // namespace ModifiedSchwarz
