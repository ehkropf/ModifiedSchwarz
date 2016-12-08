#include "RealInterpolant.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
void
RealInterpolant::prepareInterpolant()
{
    unsigned N = _boundaryData.n_rows;
    cx_mat c(fft(_boundaryData)/N);
    _constants = real(c.row(0).st());
    _coefficients = flipud(c.rows(1, N));
}

////////////////////////////////////////////////////////////////////////
cx_vec
RealInterpolant::eval(const cx_vec& z) const
{
    cx_vec w(size(z));
    w.fill(arma::datum::nan);

    return w;
}

}; // namespace ModifiedSchwarz
