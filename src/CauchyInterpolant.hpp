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

#ifndef CAUCHY_HPP
#define CAUCHY_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

class CauchyInterpolant
{
    UnitCircleDomain _domain;
    cx_mat _bdry_points;

public:
    /*!
     * Use matrix of boundary values to construct Cauchy interpolant for
     * points inside the domain. Uses the discrete boundary values given
     * to determine number of points to use in Barycentric interpolation.
     */
    CauchyInterpolant(const cx_mat& boundary_values, const UnitCircleDomain& domain);

    /*!
     * Given a set of points, evaluate the points in the domain using the
     * barycentric interpolation method for Cauchy's formula, and set any
     * points not in the domain (including boundary points) to NaN.
     */
    cx_mat operator()(const cx_mat&) const;
};

}; // namespace ModifiedSchwarz

#endif // CAUCHY_HPP
