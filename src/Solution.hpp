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

    cx_vec eval(const cx_vec&) const;
    cx_vec operator()(const cx_vec& z) const { return eval(z); }
};

}; // namespace ModifiedSchwarz

#endif // SOLUTION_HPP
