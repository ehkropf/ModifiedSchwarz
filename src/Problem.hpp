#ifndef SCHWARZPROBLEM_HPP
#define SCHWARZPROBLEM_HPP

#include "UnitCircleDomain.hpp"
#include "Solution.hpp"
#include "Solver.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

class SpectralSolver : public Solver
{
};

/*!
 * Abstract representation of the Schwarz problem.
 *
 * Schwarz problem is stored as a matrix of boundary data where each column
 * represents a boundary.
 *
 * Provides a solve() method which creates and returns a Solution.
 *
 * Default solver is the SpectralSolver.
 */
class Problem
{
    UnitCircleDomain _domain;
    cmatd _boundaryData;
    SolverUPtr _solver;

public:
    Problem(const UnitCircleDomain& domain, const cmatd& boundaryData, Solver* solver = new SpectralSolver)
        : _domain(domain), _boundaryData(boundaryData), _solver(solver) {}

    const UnitCircleDomain& domain() const { return _domain; }
    const cmatd& data() const { return _boundaryData; }

    Solution solve() { return _solver->solve(*this); }
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZPROBLEM_HPP
