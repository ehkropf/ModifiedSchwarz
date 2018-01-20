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

#include "SpectralConstants.h"

namespace ModifiedSchwarz
{

bool SpectralConstants::_trapSet = false;
bool SpectralConstants::_truncSet = false;

unsigned SpectralConstants::_tmpTrapezoidalPoints = 0;
unsigned SpectralConstants::_tmpSpectralTruncation = 0;

unsigned
SpectralConstants::kTrapezoidalPoints()
{
    if (_trapSet)
    {
        _trapSet = false;
        return _tmpTrapezoidalPoints;
    }
    return kDefaultTrapezoidalPoints;
}

unsigned
SpectralConstants::kSpectralTruncation()
{
    if (_truncSet)
    {
        _truncSet = false;
        return _tmpSpectralTruncation;
    }
    return kDefaultSpectralTruncation;
}

void
SpectralConstants::setTrapezoidalPoints(const unsigned trapezoidalPoints)
{
    _tmpTrapezoidalPoints = trapezoidalPoints;
    _trapSet = true;
}

void
SpectralConstants::setTruncation(const unsigned truncationLevel)
{
    _tmpSpectralTruncation = truncationLevel;
    _truncSet = true;
}

}; // ModifiedSchwarz
