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

#include "Problem.h"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////////
Problem::Problem(RealInterpolant imaginaryPart)
    : _imaginaryPart(imaginaryPart) {}

Problem::Problem(RealBoundaryValues imaginaryPart)
    : _imaginaryPart(RealInterpolant(imaginaryPart)) {}

////////////////////////////////////////////////////////////////////////////////
Solution
Problem::solve()
{
    return Solver().solve(*this);
}

Solution
Problem::solve(Solver::Method m)
{
    return Solver(m).solve(*this);
}

Solution
Problem::solve(const Solution& prevSolution)
{
    return Solver().solve(*this, prevSolution);
}

Solution
Problem::solve(const Solution& prevSolution, Solver::Method m)
{
    return Solver(m).solve(*this, prevSolution);
}

std::ostream& operator<<(std::ostream& os, Problem& P)
{
    return os << "Problem is defined by\n" << P._imaginaryPart;
}

} // namespace ModifiedSchwarz
