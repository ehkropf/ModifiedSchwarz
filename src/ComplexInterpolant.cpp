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

#include "ComplexInterpolant.h"
#include "Utility.hpp"

namespace ModifiedSchwarz
{
//////////////////////////////////////////////////////////////////////////////////
ComplexInterpolant::ComplexInterpolant(RealInterpolant rpart, RealInterpolant ipart)
    : _realPart(rpart),
      _imagPart(ipart)
{}

ComplexInterpolant::ComplexInterpolant(ComplexBoundaryValues values)
    : _realPart(RealInterpolant(RealBoundaryValues(values.points(), real(values.values())))),
      _imagPart(RealInterpolant(RealBoundaryValues(values.points(), imag(values.values()))))
{}

//////////////////////////////////////////////////////////////////////////////////
void ComplexInterpolant::funcDefinition(const cx_vec& z, cx_vec& w) const
{
    w = cx_vec(_realPart(z), _imagPart(z));
}

bool
ComplexInterpolant::checkPartBoundaryValues()
{
    if (_realPart.boundaryValues().isEmpty())
    {
        try
        {
            _realPart.generateBoundaryValues(_imagPart.boundaryValues().points());
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    if (_imagPart.boundaryValues().isEmpty())
    {
        try
        {
            _imagPart.generateBoundaryValues(_realPart.boundaryValues().points());
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////
ComplexInterpolant
ComplexInterpolant::derivative() const
{
    RealInterpolant rpart = _realPart.derivative();
    RealInterpolant ipart = _imagPart.derivative();
    return ComplexInterpolant(rpart, ipart);
}

ComplexInterpolant
ComplexInterpolant::derivative(unsigned n) const
{
    return recursNthDeriv(*this, n);
}

//////////////////////////////////////////////////////////////////////////////////
ComplexInterpolant withAdjustedImagConst(RealInterpolant rpart, RealInterpolant ipart, colvec constvec)
{
    ipart.adjustConstants(constvec);
    return ComplexInterpolant(rpart, ipart);
}

} // namespace ModifiedSchwarz
