#include "RealInterpolant.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
void
RealInterpolant::prepareInterpolant()
{
    unsigned M = _boundaryData.n_rows;
    unsigned N = (unsigned)std::ceil((M - 1)/2.);
    cx_mat c(fft(_boundaryData)/M);
    _constants = real(c.row(0).st());
    _coefficients = join_vert(flipud(c.rows(1, N)),
                              cx_mat(1, _boundaryData.n_cols, arma::fill::zeros));
}

////////////////////////////////////////////////////////////////////////
colvec
RealInterpolant::eval(const cx_vec& z) const
{
    using namespace arma;

    unsigned m = _domain.m();
    colvec w(size(z));
    w.fill(datum::nan);
    for (unsigned j = 0; j < m+1; ++j)
    {
        uvec L = _domain.isOnC(j, z);
        if (L.n_elem)
            w.elem(L) = _constants(j)
                    + real(2.*polyval(_coefficients.col(j),
                                      (z(L) - _domain.dv0(j))/_domain.qv0(j)));
    }


    return w;
}

}; // namespace ModifiedSchwarz
