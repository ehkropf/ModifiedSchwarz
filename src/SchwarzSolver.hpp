#ifndef SCHWARZSOLVER_HPP
#define SCHWARZSOLVER_HPP

#include "SchwarzSolution.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

class SchwarzProblem;

/*!
 * Abstract representation of method to solve Schwarz problem.
 */
class SchwarzSolver
{
public:
    virtual ~SchwarzSolver() {}

    virtual SchwarzSolution solve(const SchwarzProblem& problem) = 0;
    virtual SchwarzSolution solve(const SchwarzProblem& problem, SchwarzSolution& previous) = 0;
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZSOLVER_HPP
