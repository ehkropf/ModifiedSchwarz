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

#ifndef BOUNDARY_VALUES_H
#define BOUNDARY_VALUES_H

#include "BoundaryPoints.h"

namespace ModifiedSchwarz
{

class BoundaryValues
{
    BoundaryPoints _points;
    cx_mat _values;

public:
    //! Default constructor.

    //! Construct using points and interpolant.

    //! Get points.
    const BoundaryPoints& points() const { return _points; }

    //! Get data values.
    const cx_mat& values() const { return _values; }
};

}; // namespace ModifiedSchwarz

#endif // BOUNDARY_VALUES_H
