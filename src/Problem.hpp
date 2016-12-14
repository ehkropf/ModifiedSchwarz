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
    RealInterpolant _boundaryData;

public:
    Problem(UnitCircleDomain domain, mat boundaryData)
        : _boundaryData(RealInterpolant(domain, boundaryData)) {}

    const RealInterpolant& interpolant() const { return _boundaryData; }
    const UnitCircleDomain& domain() const { return _boundaryData.domain(); }
    const mat& dataPoints() const { return _boundaryData.boundaryData(); }

    Solution solve();
    Solution solve(Solver::Method);
    Solution solve(const Solution& prevSolution);
    Solution solve(const Solution& prevSolution, Solver::Method);
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZPROBLEM_HPP
