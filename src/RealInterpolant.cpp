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

#include "RealInterpolant.h"
#include "Utility.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
RealInterpolant::RealInterpolant(RealBoundaryValues bvals)
    : _domain(bvals.domain())
    , _boundary_values(bvals)
{
    prepareInterpolant();
}

RealInterpolant::RealInterpolant(UnitCircleDomain domain, colvec constants, cx_mat coefficients)
    : _domain(domain)
    , _constants(constants)
{
    // Add extra zero row; see comment in prepareInterpolant() below.
    _coefficients = join_vert(coefficients,
                              cx_mat(1, coefficients.n_cols, arma::fill::zeros));
}

////////////////////////////////////////////////////////////////////////
void
RealInterpolant::prepareInterpolant()
{
    const mat& bvals = _boundary_values.values();
    unsigned M = bvals.n_rows;
    unsigned N = (unsigned)std::ceil((M - 1)/2.);
    cx_mat c(fft(bvals)/M);
    _constants = real(c.row(0).st());

    // Store coeffients with extra zero row for use in polyval. This
    // is because we add the constant to twice the real part of the
    // polynomial evaluation. (Artifact of DFT coefficients being
    // conjugate.)
    _coefficients = join_vert(flipud(c.rows(1, N)),
                              cx_mat(1, bvals.n_cols, arma::fill::zeros));
}

////////////////////////////////////////////////////////////////////////
colvec
RealInterpolant::evalOn(const cx_vec& z, unsigned j) const
{
    return _constants(j)
        +  real(2.*polyval(cx_vec(_coefficients.col(j)),
                           cx_vec((z - _domain.dv0(j))/_domain.qv0(j)) ));
}

////////////////////////////////////////////////////////////////////////
void RealInterpolant::funcDefinition(const cx_vec& z, colvec& w) const
{
    unsigned m = _domain.m();
    // colvec w(size(z));
    // w.fill(arma::datum::nan);

    for (unsigned j = 0; j < m+1; ++j)
    {
        uvec L = _domain.isOnC(j, z);
        if (L.n_elem)
            w.elem(L) = evalOn(z(L), j);
    }
}

////////////////////////////////////////////////////////////////////////
void RealInterpolant::generateBoundaryValues(BoundaryPoints pts)
{
    _boundary_values = RealBoundaryValues(pts, *this);
}

////////////////////////////////////////////////////////////////////////
RealInterpolant
RealInterpolant::derivative() const
{
    colvec new_const = _constants;
    cx_mat new_coeff = _coefficients;

    // TODO: Modify new_const and new_coeff appropritely.

    RealInterpolant deriv(_domain, new_const, new_coeff);
    if (!_boundary_values.points().isEmpty())
        deriv.generateBoundaryValues(_boundary_values.points());
    return deriv;
}

RealInterpolant
RealInterpolant::derivative(unsigned n) const
{
    return recursNthDeriv(*this, n);
}

////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, RealInterpolant& I)
{
    unsigned m = I._domain.connectivity();

    return os << "class:RealInterpolant\n{\n"
        << "\tconnectivity: " << m << "\n"
        << "\tsamplePointsPerBoundary: " << I._boundary_values.points().vector().n_elem/m << "\n"
        << "\tcoefficientsPerBoundary: " << I._coefficients.n_elem/m << "\n"
        << "}\n";
}

}; // namespace ModifiedSchwarz
