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

#include "Solver.h"
#include "SpectralMethod.h"

#include <cassert>

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////////
Solver::Solver()
    : method(Method::Spectral) {}

Solver::Solver(Method method)
    : method(method) {}

////////////////////////////////////////////////////////////////////////////////
Solution Solver::solve(const Problem& p)
{
    switch(method)
    {
        case Spectral:
            return SpectralMethod(p).solve();
            break;

        default:
            // NEVER should be here. Means enum was added without method implementation.
            assert(false);
    }
}

Solution Solver::solve(const Problem& p, const Solution& prev)
{
    switch(method)
    {
        case Spectral:
            return SpectralMethod(p, prev).solve();
            break;

        default:
            // NEVER should be here. Means enum was added without method implementation.
            assert(false);
    }
}

} // ModifiedSchwarz
