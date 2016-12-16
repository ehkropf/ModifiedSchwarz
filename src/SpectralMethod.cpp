#include "SpectralMethod.hpp"

namespace ModifiedSchwarz
{

cx_vec
SpectralMethod::computeRHS(unsigned M)
{
    using namespace arma;

    // M is number of sample points for trapezoidal rule.
    const UnitCircleDomain& D = _data.domain();
    const unsigned m = D.m();
    const unsigned N = _data.truncation();

    const cx_mat zj = D.boundaryPoints(M*(m+1));
    const cx_mat rzj = reshape(_imagPart(vectorise(zj)), size(zj));


    // Note p = 0; means k = -1, ..., -N or -k-1 = 0, ..., N-1;
    // and thus N rows.
    // Also p > 1; means k = -1, ..., -N-1; and thus N+1 rows.
    // (The k here is *formula* k, which is different than counter k
    // used below, but the two are related.)
    cx_mat L(N+m*(N+1), M*(m+1));

    for (unsigned j = 0; j <= m; ++j)
    {
        const unsigned coff = j*M;
        const double qj = j > 0 ? -D.qv(j-1) : 1.;
        L(0, span(coff, coff+(M-1))) = qj*rzj.row(j);
    }

    for (unsigned k = 1; k < N; ++k)
        L.row(k) = L.row(k-1)%vectorise(zj).st();

    for (unsigned p = 1; p <= m; ++p)
    {
        const unsigned roff = N + (p-1)*(N+1);
        cx_vec etap = (zj - D.dv0(p))/D.qv0(p);
        L.row(roff) = L.row(0)/etap.st();
        for (unsigned k = 1; k < N+1; ++k)
        {
            L.row(roff+k) = L.row(roff+k-1)/etap.st();
        }
    }

    return L*repmat((2.*pi/M)*zj.row(0).st(), m+1, 1);
}

}; // namespace ModifiedSchwarz
