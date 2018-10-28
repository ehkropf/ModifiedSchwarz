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

#ifndef REALINTERPOLANT_H
#define REALINTERPOLANT_H

#include "SchwarzTypes.h"
#include "BoundaryValues.hpp"
#include "FunctionLike.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
//! Real valued interpolant on domain boundary.
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
 * \f[
 *      p_j(z) = \mathrm{real}\{c_{j,0}\} + 2\sum_{i=1}^N c_{j,i} \left(\frac{z - d_j}{q_j}\right)^i
 * \f]
 * for points z on boundary C_j.
 *
 * Note when evaluating points, it is assumed they have been tested to be on
 * the boundary. Results for non-boundary points are undefined.
 */
class RealInterpolant : public FunctionLike<cx_vec, colvec>
{
    // FIXME: Domain is now stored in boundary values.
    UnitCircleDomain _domain;
    RealBoundaryValues _boundary_values;
    //! Constants c_j.
    colvec _constants;
    //! Polynomial coefficients.
    /*! Coefficients are stored column-wise, one column per boundary. In terms
     *  of the polynomial, row 0 multiples z^n, row 1 for z^(n-1), down to
     *  last row multipies z^1.
     */
    cx_mat _coefficients;

protected:
    //! Runs FFT on boundary values to generate coefficients.
    void prepareInterpolant();

public:
    //! Empty (nonfunctional) interpolant.
    RealInterpolant() {}

    //! Use samples to construct interpolant.
    RealInterpolant(RealBoundaryValues);

    //! Polynomial data given directly.
    /*! Note this constructor leaves the boundary values uninitialized!
     *  Use `generateBoundaryValues()` after construction to rectify.
     */
    RealInterpolant(UnitCircleDomain, colvec constants, cx_mat coefficients);

    //! Domain of definition.
    const UnitCircleDomain& domain() const { return _domain; }

    //! View of stored BoundaryValues.
    const RealBoundaryValues& boundaryValues() const { return _boundary_values; }

    //! Boundary data matrix.
    const mat& boundaryData() const { return _boundary_values.values(); }

    //! View of m+1 vector of real constants.
    const colvec& constants() const { return _constants; }

    //! View of polynomial coefficients.
    const cx_mat& coefficients() const { return _coefficients; }

    //! Eval given vector of points on specific boundary.
    colvec evalOn(const cx_vec&, unsigned) const;

    //! Define function behaviour for FunctionLike.
    void funcDefinition(const cx_vec&, colvec&) const;

    //! Adjust polynomial constants by given vector c (add to stored constant vector).
    void adjustConstants(const colvec& c) { _constants += c; }

    //! Use interpolant to generate values at given points.
    void generateBoundaryValues(BoundaryPoints);

    //! DFT derivative. Returns new interpolant based on current.
    /*! Recall it's possible to have an instance of the interpolant with no boundary
     *  points/values defined. In this case, the derivative will also be missing
     *  defined boundary points/values.
     */
    RealInterpolant derivative() const;

    //! n-th DFT derivative.
    RealInterpolant derivative(unsigned n) const;

    //! Self description.
    friend std::ostream& operator<<(std::ostream&, RealInterpolant&);
};

}; // namespace ModifiedSchwarz

#endif // REALINTERPOLANT_H
