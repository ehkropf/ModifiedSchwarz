#ifndef SCHWARZPROBLEM_HPP
#define SCHWARZPROBLEM_HPP

#include "SpectralSolver.hpp"
#include "SchwarzSolution.hpp"
#include "SchwarzSolver.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Abstract representation of the Schwarz problem.
 *
 * Schwarz problem is stored as a matrix of boundary data where each column
 * represents a boundary.
 *
 * Provides a solve() method which creates and returns a SchwarzSolution.
 *
 */
class SchwarzProblem
{
    cmatd _problemData;

protected:
    SchwarzSolver* _solver;

public:
    SchwarzProblem(const cmatd& boundaryData)
        : _problemData(boundaryData), _solver(new SolverSpectral) {}
//    SchwarzProblem(const SchwarzProblem& other)
//        : _problemData(other.data()), _solver(new SolverSpectral) {}

    ~SchwarzProblem() { delete _solver; }

    SchwarzSolution solve() { return _solver->solve(*this); }

    const cmatd& data() const { return _problemData; }
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZPROBLEM_HPP
