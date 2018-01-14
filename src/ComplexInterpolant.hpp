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

#ifndef COMPLEXINTERP_HPP
#define COMPLEXINTERP_HPP

#include "SchwarzTypes.hpp"
#include "FunctionLike.hpp"
#include "RealInterpolant.hpp"
#include "Solution.hpp"

namespace ModifiedSchwarz
{

/*!
 * Interpolant for evaluating points on the boundary. Given f is a
 * ComplexInterpolant and z is a complex column vector of points on the
 * boundary, then
 *
 *     cx_vec w = f(z)
 *
 * is a complex vector of interpolated values.
 */
class ComplexInterpolant : public FunctionLike<cx_vec>
{
    RealInterpolant _realPart;
    RealInterpolant _imagPart;

public:
    ComplexInterpolant(const RealInterpolant&, const RealInterpolant&);
    ComplexInterpolant(ComplexBoundaryValues);
    ComplexInterpolant(const Solution&);

    //! Access to constant reference to stored real part.
    const RealInterpolant& realPart() const { return _realPart; }
    //! Access to constant reference to stored imaginary part.
    const RealInterpolant& imagPart() const { return _imagPart; }

    //! Override FunctionLike<>::evalInto for f() behaviour.
    void evalInto(const cx_vec&, cx_vec&) const;
};

}; // namespace ModifiedSchwarz

#endif // COMPLEXINTERP_HPP
