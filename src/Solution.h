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

#ifndef SOLUTION_H
#define SOLUTION_H

#include <memory>

#include "SchwarzTypes.h"
#include "RealInterpolant.h"
#include "SolverData.h"

namespace ModifiedSchwarz
{

// FIXME: Move to use ClosureInterpolant instead of own operator().

///////////////////////////////////////////////////////////////////////////
//! Represents solution of modified Schwarz problem as solver output.
/*!
 * Solution is made of 3 parts:
 *   1. an imaginary part (RealInterpolant) given as part of the problem,
 *   2. a real part (RealInterpolant) which is found by the solver, and
 *   3. an imaginary constant for each boundary also found by the solver.
 * All data is on the boundary of the domain.
 *
 * In addition, a SolverData object may be stored to accelerate future
 * solver runs in the same domain.
 */
class Solution
{
    RealInterpolant _realPart;
    colvec _constants;
    RealInterpolant _imagPart;
    SolverData::Ptr _pSolverData;

public:
    //! Empty solution -- nothing defined.
    Solution() {}

    //! Basic solution construction.
    Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart);

    //! Allows storage of solver data to accelerate subsequent solver runs.
    Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart, SolverData::Ptr pSolverData);

    //! View of solution real part.
    const RealInterpolant& realPart()      const { return _realPart; }
    //! View of solution constants.
    const colvec&          constants()     const { return _constants; }
    //! View of given imaginary part.
    const RealInterpolant& imagPart()      const { return _imagPart; }
    //! Read only pointer to solver data.
    const SolverData::Ptr  solverDataPtr() const { return _pSolverData; }

    //! Provide function-like behaviour.
    cx_vec operator()(const cx_vec& z) const;
};

}; // namespace ModifiedSchwarz

#endif // SOLUTION_H
