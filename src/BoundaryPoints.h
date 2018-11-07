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

#ifndef BOUNDARY_POINTS_H
#define BOUNDARY_POINTS_H

#include "SchwarzTypes.h"
#include "UnitCircleDomain.h"

namespace ModifiedSchwarz
{

//! Defaults for BoundaryPoints class.
struct BoundaryPointsDefaults
{
    //! Number of points to create on circle boundary if not specified.
    constexpr static unsigned numPoints = 256;
};

//! Encapsulation of evenly spaced points on each boundary component.
class BoundaryPoints
{
    UnitCircleDomain _domain;
    //! One column per boundary.
    cx_mat _points;

public:
    //! Empty object -- no points defined.
    BoundaryPoints() {}
    //! Just use given points.
    BoundaryPoints(UnitCircleDomain domain, cx_mat points);
    //! Create numPoints evenly spaced points on each boundary.
    BoundaryPoints(UnitCircleDomain domain,
            unsigned numPoints = BoundaryPointsDefaults::numPoints);

    //! Domain of definition.
    UnitCircleDomain domain() const { return _domain; }

    //! View of points as matrix.
    const cx_mat& matrix() const  { return _points; }

    //! View of points as vector via arma::vectorise().
    cx_vec vector() const { return arma::vectorise(_points); }

    //! Has the point matrix been initialized?
    bool isEmpty() const { return _points.n_rows == 0; }
};

//! Pick points on circle j from vector of points on all circles.
/*! With 0 <= j < m, and a vector with an equal number of points on
 *  all circles in the domain, returns a copy of only the points on
 *  circle j.
 */
template<typename Vec>
Vec jPointsFromPointsVector(unsigned j, const UnitCircleDomain& D, const Vec& v)
{
    unsigned m = D.connectivity();
    unsigned n = v.n_elem / m;

    if (n*m != v.n_elem)
        throw(std::runtime_error("Vector does not represent an equal number of points on"
                    "all boundary circles."));

    return v.rows(j*n, (j+1)*n);
}

}; // namespace ModifiedSchwarz

#endif // BOUNDARY_POINTS_H
