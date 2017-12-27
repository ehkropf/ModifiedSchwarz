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

#include "ComplexInterpolant.hpp"

namespace ModifiedSchwarz
{
//////////////////////////////////////////////////////////////////////////////////
ComplexInterpolant::ComplexInterpolant(const RealInterpolant& rpart, const RealInterpolant& ipart)
    : _realPart(rpart),
      _imagPart(ipart)
{}

ComplexInterpolant::ComplexInterpolant(const Solution& S)
    : _realPart(S.realPart()),
      _imagPart(S.imagPart())
{}

//////////////////////////////////////////////////////////////////////////////////
void ComplexInterpolant::evalInto(const cx_vec& z, cx_vec& w) const
{
    w = cx_vec(_realPart(z), _imagPart(z));
}

}; // namespace ModifiedSchwarz
