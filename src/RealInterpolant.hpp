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
#include "UnitCircleDomain.hpp"
#include "FunctionLike.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 * Provide interpolation on domain boundaries given real data at
 * evenly spaced points on each boundary.
 *
 * Boundary data is stored in a matrix with each column representing
 * a boundary. Boundary sample data must be real and evenly spaced.
 *
 * Let M be the number of sample points on a boundary. The M-point
 * DFT is taken for that boundary data and the N = ceil((M - 1)/2)
 * first coefficients are used for the interpolation polynomial
 *
 *                            --- N
 *                            \
 *     p(z) = real(c_0) + 2 *  .     c_i * ((z - d_j)/q_j)^i
 *                            /
 *                            --- i=1
 *
 * for points z on boundary C_j.
 */
class RealInterpolant : public FunctionLike<cx_vec, colvec>
{
    UnitCircleDomain _domain;
    mat _boundaryData;
    colvec _constants;
    cx_mat _coefficients;

protected:
    void prepareInterpolant();

public:
    RealInterpolant() {}
    RealInterpolant(UnitCircleDomain domain, mat samples);
    RealInterpolant(UnitCircleDomain, colvec constants, cx_mat coefficients);

    const UnitCircleDomain& domain() const { return _domain; }
    const mat& boundaryData() const { return _boundaryData; }
    const colvec& constants() const { return _constants; }
    const cx_mat& coefficients() const { return _coefficients; }

    colvec evalOn(const cx_vec&, unsigned) const;
    void evalInto(const cx_vec&, colvec&) const;
};

}; // namespace ModifiedSchwarz

#endif // REALINTERPOLANT_HPP
