#ifndef SCHWARZSOLVER_HPP
#define SCHWARZSOLVER_HPP

#include <memory>
#include "SchwarzSolution.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

class SchwarzProblem; // Forward declaration.

/*!
 * Abstract representation of method to solve Schwarz problem.
 */
class SchwarzSolver
{
public:
    virtual ~SchwarzSolver() = default;

    virtual SchwarzSolver& newCopy() = 0;

    virtual SchwarzSolution solve(const SchwarzProblem& problem) = 0;
    virtual SchwarzSolution solve(const SchwarzProblem& problem, SchwarzSolution& previous) = 0;
};

typedef std::unique_ptr<SchwarzSolver> SchwarzSolverUPtr;

}; // namespace ModifiedSchwarz

#endif // SCHWARZSOLVER_HPP
