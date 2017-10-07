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

#ifndef SCHWARZPROBLEM_HPP
#define SCHWARZPROBLEM_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"
#include "RealInterpolant.hpp"
#include "Solver.hpp"
#include "Solution.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////
/*!
 * Schwarz problem is represented by a domain and boundary data (imaginary
 * part of the boundary values).
 * The boundary data is stored as a RealInterpolant. The original data
 * points to construct the interpolant are available via the dataPoints()
 * member wrapper.
 */
class Problem
{
    RealInterpolant _imaginaryPart;

public:
    Problem(RealInterpolant imaginaryPart);
    Problem(UnitCircleDomain domain, mat imaginaryPart);

    const RealInterpolant& interpolant() const { return _imaginaryPart; }
    const UnitCircleDomain& domain() const { return _imaginaryPart.domain(); }
    const mat& dataPoints() const { return _imaginaryPart.boundaryData(); }

    Solution solve();
    Solution solve(Solver::Method);
    Solution solve(const Solution& prevSolution);
    Solution solve(const Solution& prevSolution, Solver::Method);
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZPROBLEM_HPP
