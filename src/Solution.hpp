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

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <memory>

#include "SchwarzTypes.hpp"
#include "RealInterpolant.hpp"
#include "SolverData.hpp"

namespace ModifiedSchwarz
{

///////////////////////////////////////////////////////////////////////////
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
    Solution() {}
    Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart);
    Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart, SolverData::Ptr pSolverData);

    const RealInterpolant& realPart()      const { return _realPart; }
    const colvec&          constants()     const { return _constants; }
    const RealInterpolant& imagPart()      const { return _imagPart; }
    const SolverData::Ptr  solverDataPtr() const { return _pSolverData; }

    cx_vec operator()(const cx_vec& z) const;
};

}; // namespace ModifiedSchwarz

#endif // SOLUTION_HPP
