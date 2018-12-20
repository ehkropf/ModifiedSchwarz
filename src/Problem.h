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

#ifndef SCHWARZPROBLEM_H
#define SCHWARZPROBLEM_H

#include "SchwarzTypes.h"
#include "RealInterpolant.h"
#include "Solver.h"
#include "Solution.h"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////
//! Encapsulation of modified Schwarz problem statement.
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
    //! Define problem with real valued function on the boundary.
    Problem(RealInterpolant imaginaryPart);

    // FIXME: BoundaryValues contians domain; domain arg not needed.
    //! Define problem with evenly spaced real samples on the boundary.
    Problem(UnitCircleDomain domain, RealBoundaryValues imaginaryPart);

    //! View of imaginary part interpolant.
    const RealInterpolant& interpolant() const { return _imaginaryPart; }
    //! Domain of definition.
    const UnitCircleDomain& domain() const { return _imaginaryPart.domain(); }
    //! View of boundary data samples defining interpolant.
    const mat& dataPoints() const { return _imaginaryPart.boundaryData(); }

    //! Call the modified Schwarz solver.
    Solution solve();
    //! Call the modified Schwarz solver; specify solution method.
    Solution solve(Solver::Method);
    //! Call the modified Schwarz solver with previous solution acceleration.
    Solution solve(const Solution& prevSolution);
    // FIXME: Wouldn't the previous solution contain information about the
    // type of solver used?
    //! Call solver with previous solution and specified method.
    Solution solve(const Solution& prevSolution, Solver::Method);

    // Self output.
    friend std::ostream& operator<<(std::ostream&, Problem&);
};

} // namespace ModifiedSchwarz

#endif // SCHWARZPROBLEM_H
