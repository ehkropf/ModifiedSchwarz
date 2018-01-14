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

#include <functional>
#include "BoundaryPoints.h"

namespace ModifiedSchwarz
{

template <typename ArmaMat, typename ArmaVec>
class BoundaryValues
{
    BoundaryPoints _points;
    ArmaMat _values;

public:
    //! Generic callable object.
    using Function = std::function<ArmaVec(const cx_vec&)>;

    //! Default constructor.
    BoundaryValues() {}

    //! Construction by function.
    BoundaryValues(BoundaryPoints, Function);

    //! Just use given data.
    BoundaryValues(BoundaryPoints, ArmaMat);

    //! Domain of definition.
    UnitCircleDomain domain() const { return _points.domain(); }

    //! Reference to points on which values are defined.
    const BoundaryPoints& points() const { return _points; }

    //! Reference to values matrix.
    const ArmaMat& values() const { return _values; }
};

using RealBoundaryValues = BoundaryValues<mat,colvec>;
using ComplexBoundaryValues = BoundaryValues<cx_mat,cx_vec>;

template <typename ArmaMat,typename ArmaVec>
BoundaryValues<ArmaMat,ArmaVec>::BoundaryValues(BoundaryPoints pts, BoundaryValues<ArmaMat,ArmaVec>::Function f)
    : _points(pts), _values(f(_points.vector()))
{
    _values.reshape(_points.matrix().n_rows, _points.matrix().n_cols);
}

template <typename ArmaMat,typename ArmaVec>
BoundaryValues<ArmaMat,ArmaVec>::BoundaryValues(BoundaryPoints pts, ArmaMat vals)
    : _points(pts), _values(vals)
{}

}; // namespace ModifiedSchwarz

#endif // BOUNDARY_VALUES_H
