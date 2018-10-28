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

#ifndef COMPLEXINTERP_H
#define COMPLEXINTERP_H

#include "SchwarzTypes.h"
#include "FunctionLike.hpp"
#include "RealInterpolant.h"

namespace ModifiedSchwarz
{

//! Complex valued interpolation on domain boundary.
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
    //! Empty interpolant -- nothing defined.
    ComplexInterpolant() {};

    //! Define given real and imaginary parts.
    ComplexInterpolant(RealInterpolant, RealInterpolant);

    //! Define given boundary samples.
    /*! FIXME: Should take const reference? Only a copy of boundary points are
     *  used in constructor.
     */
    ComplexInterpolant(ComplexBoundaryValues);

    //! View of real part.
    const RealInterpolant& realPart() const { return _realPart; }
    //! View of imaginary part.
    const RealInterpolant& imagPart() const { return _imagPart; }

    //! Provide function like behaviour.
    void funcDefinition(const cx_vec&, cx_vec&) const;

    //! Domain of definition.
    UnitCircleDomain domain() const { return _realPart.domain(); }

    //! Request check that boundary values are cached.
    /*! It's possible to have constructed the complex interpolant with real or
     *  imaginary interpolants that don't have initialized boundary value structures.
     *  This method checks each and tries to create them. Returns true on success and
     *  false if the values can't be created.
     */
    bool checkPartBoundaryValues();

    //! DFT derivative of each part. Returns new interpolant based on current.
    ComplexInterpolant derivative() const;

    //! n-th DFT derivative.
    ComplexInterpolant derivative(unsigned n) const;
};

//! Adjust imaginary part by a constant on each boundary.
/*! Solutions to the modified Schwarz problem are determined up to an imaginary constant
 *  on each boundary.
 */
ComplexInterpolant withAdjustedImagConst(RealInterpolant rpart, RealInterpolant ipart, colvec constvec);

}; // namespace ModifiedSchwarz

#endif // COMPLEXINTERP_H
