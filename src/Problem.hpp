#ifndef SCHWARZPROBLEM_HPP
#define SCHWARZPROBLEM_HPP

#include <memory>

#include "UnitCircleDomain.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Schwarz problem is represented by a domain and boundary data (imaginary
 * part of the boundary values).
 * The boundary data is stored as a matrix where each column represents
 * a boundary.
 *
 * Provides a solve() method which creates and returns a Solution.
 * A previous solution may be given to solve() for solution acceleration;
 * this is highly dependent on the solver.
 * Of course this means we expect the Solver to conform to this interface.
 */
template<class Solver, class Solution>
class Problem
{
    UnitCircleDomain _domain;
    cx_mat _boundaryData;
    Solver _solver;

public:
    Problem(UnitCircleDomain domain, cx_mat boundaryData, Solver solver)
        : _domain(domain), _boundaryData(boundaryData), _solver(solver) {}

    const UnitCircleDomain& domain() const { return _domain; }
    const cx_mat& data() const { return _boundaryData; }
    const Solver solver() const { return _solver; }

    Solution solve() { return _solver.solve(*this); }
    Solution solve(const Solution& prevSolution) { return _solver.solve(*this, prevSolution); }
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZPROBLEM_HPP
