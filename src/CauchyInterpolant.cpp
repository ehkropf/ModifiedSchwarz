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

#include "CauchyInterpolant.h"
#include "ZFMM_Wrapper.h"

namespace ModifiedSchwarz
{

//////////////////////////////////////////////////////////////////////////////////
CauchyInterpolant::CauchyInterpolant(ComplexBoundaryValues v)
    : _boundary_values(v)
{
    // Use the boundary values to setup and store values needed for evaluation.
    // If we assume h_jk are the boundary values at the boundary points t_jk,
    // then we need the following:
    //   * sigma_j = j == 0 ? 1 : -1
    //   * s = sigma_j * q_j * exp(i*(2*pi*k)/N)
    //       = sigma_j * (t_jk - d_j)
    //   * h = h_jk * s
    // where k is in {0,..,N-1}.

    auto sigma = [](unsigned j)->double{ return j == 0 ? 1. : -1.; };
    const cx_mat& t_jk = _boundary_values.points().matrix();
    const cx_mat& h_jk = _boundary_values.values();
    unsigned N = t_jk.n_rows;
    const auto& D = _boundary_values.domain();

    _s.set_size(t_jk.n_elem);
    _h.set_size(t_jk.n_elem);
    for (unsigned j = 0; j < D.connectivity(); ++j)
    {
        auto s = arma::span(j*N, (j+1)*N - 1);
        _s.rows(s) = sigma(j) * (t_jk.col(j) - D.dv0(j));
        _h.rows(s) = h_jk.col(j) % _s.rows(s);
    }
}

//////////////////////////////////////////////////////////////////////////////////
void CauchyInterpolant::evalInto(const cx_vec& z, cx_vec& w) const
{
    // On evaluation, we need the matrix
    //
    //                      1
    //     I := (I_jk) = --------
    //                   t_jk - z
    //
    // where t_jk represents a row vector and z a column vector.

    if (_boundary_values.points().vector().n_elem * z.n_elem < min_pts_for_FMM)
    {
        // Quicker for a small number of points.
        const cx_rvec& t_jk = _boundary_values.points().vector().st();
        cx_mat I = arma::repmat(t_jk, z.n_elem, 1);
        I.each_col() -= z;
        I = 1./I;

        w = (I*_h)/(I*_s);
    }
    else
    {
        // FMM for larger number of points.
        cx_vec source = _boundary_values.points().vector();
        ZFMM2d top(source, cx_vec(-_h), z);
        ZFMM2d bot(source, cx_vec(-_s), z);

        w = top.pottarg/bot.pottarg;
    }
}

}; // namespace ModifiedSchwarz
