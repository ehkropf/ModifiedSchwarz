#include "SpectralMethod.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////////
SpectralMethod::SpectralMethod(const Problem& prob)
    : _data(std::make_shared<SpectralData>(prob.domain())),
      _imagPart(prob.interpolant()) {}

SpectralMethod::SpectralMethod(const Problem& prob, const Solution& prev)
        : _data(std::dynamic_pointer_cast<SpectralData>(prev.solverDataPtr())),
          _imagPart(prob.interpolant()) {}

////////////////////////////////////////////////////////////////////////////////
Solution SpectralMethod::solve()
{
    cx_vec x = arma::solve(_data->matrix(), computeRHS(kDefaultTrapezoidalPoints));
    const unsigned m = _data->domain().m();
    const unsigned N = (_data->matrix().n_cols/2 - m)/(m + 1);
    cx_vec c(m+1);
    cx_mat a(N, m+1);

    for (unsigned j = 0; j <= m; ++j)
    {
        unsigned offset = j > 0 ? (j-1)*(N+1) + N : 0;
        c(j) = j > 0 ? x(offset) : 0.;
        a.col(j) = arma::flipud(x.rows(offset+1, offset+N));
    }

    RealInterpolant realPart(_data->domain(), real(c), a);
    return Solution(realPart, imag(c), _imagPart); //, _data);
}

////////////////////////////////////////////////////////////////////////////////
cx_vec
SpectralMethod::computeRHS(unsigned M)
{
    using namespace arma;

    // M is number of sample points for trapezoidal rule.
    const UnitCircleDomain& D = _data->domain();
    const unsigned m = D.m();
    const unsigned N = _data->truncation();

    using rx_vec = Row<cx_double>;

    const rx_vec zj = vectorise(D.boundaryPoints(M)).st();
    const rowvec rzj = _imagPart(zj.st()).st();

    // Note p = 0; means k = -1, ..., -N or -k-1 = 0, ..., N-1;
    // and thus N rows.
    // Also p > 1; means k = -1, ..., -N-1; and thus N+1 rows.
    // (The k here is *formula* k, which is different than counter k
    // used below, but the two are related.)
    cx_mat L(N+m*(N+1), M*(m+1));

    // Shared row values.
    rx_vec dz = (2.*pi/M)*zj(span(0, M-1));
    for (unsigned j = 0; j <= m; ++j)
    {
        const unsigned coff = j*M;
        const auto idx = span(coff, coff+(M-1));
        const cx_double qj = j > 0 ? -D.qv(j-1) : 1.;
        L(0, idx) = qj*rzj(idx)%dz;
    }

    // For p = 0.
    for (unsigned k = 1; k < N; ++k)
        L.row(k) = L.row(k-1)%zj;

    for (unsigned p = 1; p <= m; ++p)
    {
        const unsigned roff = N + (p-1)*(N+1);
        rx_vec etap = D.qv0(p)/(zj - D.dv0(p));
        L.row(roff) = L.row(0)%etap;
        for (unsigned k = 1; k < N+1; ++k)
        {
            L.row(roff+k) = L.row(roff+k-1)%etap;
        }
    }

    return sum(L, 1);
}

}; // namespace ModifiedSchwarz
