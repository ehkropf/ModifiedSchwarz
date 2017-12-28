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

#include "BoundaryValues.h"

namespace ModifiedSchwarz
{

template <typename ArmaMat, typename ArmaVec>
BoundaryValues<ArmaMat,ArmaVec>::BoundaryValues(BoundaryPoints pts, BoundaryValues<ArmaMat,ArmaVec>::Function f)
    : _points(pts)
{
    _values = f(_points.vector());
    _values.reshape(_points.matrix().n_rows, _points.matrix().n_cols);
}

////////////////////////////////////////////////////////////////////////////////
RealBoundaryValues
BoundaryValueFactory::create(BoundaryPoints pts, const RealInterpolant& f)
{
    return RealBoundaryValues(pts, [&f](const cx_vec& z){ return f(z); });
}

ComplexBoundaryValues
BoundaryValueFactory::create(BoundaryPoints pts, const ComplexInterpolant& f)
{
    return ComplexBoundaryValues(pts, [&f](const cx_vec& z){ return f(z); });
}

}; // namespace ModifiedSchwarz
