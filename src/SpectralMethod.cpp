/*
 * Copyright 2017 Everett Kropf.
 *
 * This file is part of ModifiedSchwarz.
 *
 * ModifiedSchwarz is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ModifiedSchwarz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ModifiedSchwarz.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SpectralMethod.h"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////////
SpectralMethod::SpectralMethod(const Problem& prob)
    : _trapezoidalPoints(SpectralConstants::kTrapezoidalPoints()),
      _data(std::make_shared<SpectralData>(prob.domain())),
      _imagPart(prob.interpolant()) {}

SpectralMethod::SpectralMethod(const Problem& prob, const Solution& prev)
    : _trapezoidalPoints(SpectralConstants::kTrapezoidalPoints()),
      _data(std::dynamic_pointer_cast<SpectralData>(prev.solverDataPtr())),
      _imagPart(prob.interpolant()) {}

////////////////////////////////////////////////////////////////////////////////
Solution SpectralMethod::solve()
{
    SDEBUG("call matrix solve");
    cx_vec x = arma::solve(_data->matrix(), computeRHS());

    const unsigned m = _data->domain().m();
    const unsigned N = (_data->matrix().n_cols/2 - m)/(m + 1);
    const unsigned M = (unsigned)std::ceil((N - 1)/2.);
    cx_vec c(m+1);
    cx_mat a(M, m+1);

    c(0) = 0.;
    a.col(0) = arma::flipud(x.rows(0, M-1));
    for (unsigned j = 1; j <= m; ++j)
    {
        const unsigned offset = (j-1)*(N+1) + N;
        c(j) = x(offset);
        a.col(j) = arma::flipud(x.rows(offset+1, offset+M));
    }

    SDEBUG("create real part");
    RealInterpolant realPart(_data->domain(), real(c), a);

    SDEBUG("return solution");
    return Solution(realPart, imag(c), _imagPart, _data);
}

////////////////////////////////////////////////////////////////////////////////
cx_vec
SpectralMethod::computeRHS()
{
    return computeRHS(_trapezoidalPoints);
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

    cx_vec b = sum(L, 1);
    return join_vert(b, conj(b));
}

}; // namespace ModifiedSchwarz
