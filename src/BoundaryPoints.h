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

struct BoundaryPointsDefaults
{
    constexpr static unsigned numPoints = 256;
};

class BoundaryPoints
{
    UnitCircleDomain _domain;
    cx_mat _points;

public:
    BoundaryPoints() {}
    BoundaryPoints(UnitCircleDomain domain, cx_mat points);
    BoundaryPoints(UnitCircleDomain domain,
            unsigned numPoints = BoundaryPointsDefaults::numPoints);

    //! Domain of definition.
    UnitCircleDomain domain() const { return _domain; }

    //! Access points as matrix.
    const cx_mat& matrix() const  { return _points; }

    //! Access points as vector.
    cx_vec vector() const { return arma::vectorise(_points); }
};

}; // namespace ModifiedSchwarz

#endif // BOUNDARY_POINTS_H
