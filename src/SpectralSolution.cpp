#include "SpectralSolution.hpp"

namespace ModifiedSchwarz
{

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
    const vec& qv = D.radii();
    const cx_mat& a = _coefficients;
    unsigned N = (a.n_rows - 1)/2;

    cx_vec w(z.n_elem);
    for (unsigned j = 0; j < D.m()+1; ++j)
    {
        const cx_double dj = j > 0 ? dv(j-1) : 0.;
        const double qj = j > 0 ? qv(j-1) : 1.;

        cx_vec zj = z - dj;
        uvec L = find(abs(qj - abs(zj)) < eps2pi);
        if (L.n_elem)
            w.elem(L) = a(0, j) +
                2.*polyval(join_vert(flipud(a.col(j).subvec(1, N)), cx_vec(1, fill::zeros)), zj(L)/qj);
    }

    return w;
}

}; // namespace ModifiedSchwarz
