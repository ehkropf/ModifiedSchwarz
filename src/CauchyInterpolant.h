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

#ifndef CAUCHY_H
#define CAUCHY_H

#include "BoundaryValues.h"
#include "FunctionLike.hpp"
#include "Solution.h"

namespace ModifiedSchwarz
{

/*!
 * Uses a Barycentric interpolation to approximate Cauchy's integral for
 * giving values in the domain. Is a FunctionLike object which takes a vector
 * of points in the domain and returns the appropriate value for each point.
 * It is expected that the points have been validated to be in the domain;
 * behaviour for points not in the domain is not defined.
 */
class CauchyInterpolant : public FunctionLike<cx_vec>
{
    ComplexBoundaryValues _boundary_values;
    cx_vec _s; //! Column vector of points for evaluation.
    cx_vec _h; //! Column vector of points for evaluation.

public:
    CauchyInterpolant() {};

    /*!
     * Use given boundary sample values to construct Cauchy Interpolant for
     * points inside the domain. Uses the discrete boundary values given
     * to determine number of points to use in Barycentric interpolation.
     */
    CauchyInterpolant(ComplexBoundaryValues);

    /*!
     * Create Cauchy interpolant from given Solution.
     */
    CauchyInterpolant(const Solution&);

    /*!
     * Given a set of points, evaluate the points in the domain using the
     * barycentric interpolation method for Cauchy's formula, and set any
     * points not in the domain (including boundary points) to NaN.
     */
    virtual void evalInto(const cx_vec&, cx_vec&) const;

    //! Domain of definition.
    UnitCircleDomain domain() const { return _boundary_values.domain(); }
};

}; // namespace ModifiedSchwarz

#endif // CAUCHY_H
