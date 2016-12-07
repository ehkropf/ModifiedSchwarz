#include "SpectralSolution.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 *
 */
cvecd
SpectralSolution::eval(const cvecd& z)
{
    using namespace arma;

    const UnitCircleDomain& D = _domainData->domain();
    const cvecd& dv = D.centers();
    const vecd& qv = D.radii();
    const cmatd& a = _coefficients;
    unsigned N = (a.n_rows - 1)/2;

    cvecd w(z.n_elem);
    for (unsigned j = 0; j < D.m()+1; ++j)
    {
        const ComplexDouble dj = j > 0 ? dv(j-1) : 0.;
        const double qj = j > 0 ? qv(j-1) : 1.;

        cvecd zj = z - dj;
        uvec L = find(abs(qj - abs(zj)) < eps2pi);
        if (L.n_elem)
            w.elem(L) = a(0, j) +
                2.*polyval(join_vert(flipud(a.col(j).subvec(1, N)), cvecd(1, fill::zeros)), zj(L)/qj);
    }

    return w;
}

}; // namespace ModifiedSchwarz
