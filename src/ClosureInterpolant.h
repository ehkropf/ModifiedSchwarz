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

#ifndef CLOSURE_INTERPOLANT_H
#define CLOSURE_INTERPOLANT_H

#include "SchwarzTypes.hpp"
#include "FunctionLike.hpp"
#include "CauchyInterpolant.hpp"
#include "ComplexInterpolant.hpp"
#include "Solution.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////////
/*!
 * An instantiation of this class acts like a function on the closure of the
 * defined domain. It consists of a ComplexInterpolant for the boundary and a
 * CauchyInterpolant for the interior. If _f_ is an instance of
 * ClosureInterpolant and _z_ is a complex vector of points, then
 *
 *     cx_vec w = f(z)
 *
 * sorts points in z into boundary, interior, and not in closure categories,
 * and fills w with the approprate values. Any point not in the closure is
 * given the map value of NaN.
 */
class ClosureInterpolant : public FunctionLike<cx_vec> {
    ComplexInterpolant _boundary;
    CauchyInterpolant _interior;

public:
    ClosureInterpolant(ComplexInterpolant, CauchyInterpolant);
    ClosureInterpolant(ComplexBoundaryValues);
    ClosureInterpolant(const Solution&);

    void evalInto(const cx_vec&, cx_vec&) const;
};

}; // ModifiedSchwarz

#endif // CLOSURE_INTERPOLANT_H
