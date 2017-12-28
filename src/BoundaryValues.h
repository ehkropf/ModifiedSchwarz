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
#include "ComplexInterpolant.hpp"
#include "Solution.hpp"

namespace ModifiedSchwarz
{

template <typename ArmaMat, typename ArmaVec>
class BoundaryValues
{
    BoundaryPoints _points;
    ArmaMat _values;

public:
    //! Generic callable object.
    using Function = std::function<ArmaVec (const cx_mat&)>;

    //! Default constructor.
    BoundaryValues() {}

    //! Construction by plain function.
    BoundaryValues(BoundaryPoints, Function);

    //! Get points.
    const BoundaryPoints& points() const { return _points; }

    //! Get data values.
    const ArmaMat& values() const { return _values; }
};

using RealBoundaryValues = BoundaryValues<mat, colvec>;
using ComplexBoundaryValues = BoundaryValues<cx_mat, cx_vec>;

struct BoundaryValueFactory
{
    //! Create using RealInterpolant.
    static RealBoundaryValues create(BoundaryPoints, const RealInterpolant&);

    //! Create using ComplexInterpolant.
    static ComplexBoundaryValues create(BoundaryPoints, const ComplexInterpolant&);

    //! Create using Solution.
    static ComplexBoundaryValues create(BoundaryPoints, const Solution&);
};

}; // namespace ModifiedSchwarz

#endif // BOUNDARY_VALUES_H
