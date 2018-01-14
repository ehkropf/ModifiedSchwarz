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

#ifndef REALINTERPOLANT_HPP
#define REALINTERPOLANT_HPP

#include "SchwarzTypes.hpp"
#include "BoundaryValues.h"
#include "FunctionLike.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 * Provide interpolation on domain boundaries given real data at  evenly
 * spaced points on each boundary.
 *
 * Boundary data is stored in a matrix with each column representing a
 * boundary. Boundary sample data must be real and evenly spaced.
 *
 * Let M be the number of sample points on a boundary. The M-point  DFT is
 * taken for that boundary data and the N = ceil((M - 1)/2)  first
 * coefficients are used for the interpolation polynomial
 *
 *                            --- N
 *                            \
 *     p(z) = real(c_0) + 2 *  .     c_i * ((z - d_j)/q_j)^i
 *                            /
 *                            --- i=1
 *
 * for points z on boundary C_j.
 *
 * Note when evaluating points, it is assumed they have been tested to be on
 * the boundary. Results for non-boundary points are undefined.
 */
class RealInterpolant : public FunctionLike<cx_vec, colvec>
{
    UnitCircleDomain _domain;
    RealBoundaryValues _boundary_values;
    //mat _boundaryData;
    colvec _constants;
    cx_mat _coefficients;

protected:
    void prepareInterpolant();

public:
    RealInterpolant() {}
    RealInterpolant(RealBoundaryValues);
    RealInterpolant(UnitCircleDomain, colvec constants, cx_mat coefficients);

    //! Stored domain object.
    const UnitCircleDomain& domain() const { return _domain; }
    //! Boundary data matrix.
    const mat& boundaryData() const { return _boundary_values.values(); }
    //! m+1 vector of real constants.
    const colvec& constants() const { return _constants; }
    //! Vector of polynomial coefficients.
    const cx_mat& coefficients() const { return _coefficients; }

    //! Eval given vector of points on specific boundary.
    colvec evalOn(const cx_vec&, unsigned) const;

    //! Override FunctionLike<>::evalInto for f() behaviour.
    void evalInto(const cx_vec&, colvec&) const;
};

}; // namespace ModifiedSchwarz

#endif // REALINTERPOLANT_HPP
