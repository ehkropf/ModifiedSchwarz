#ifndef SCHWARZSOLVER_HPP
#define SCHWARZSOLVER_HPP

#include <memory>
#include "Solution.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

class Problem; // Forward declaration.

/*!
 * Abstract representation of method to solve Schwarz problem.
 */
class Solver
{
public:
    virtual ~Solver() = default;

    virtual Solver& newCopy() = 0;

    virtual Solution solve(const Problem& problem) = 0;
    virtual Solution solve(const Problem& problem, Solution& previous) = 0;
};

typedef std::unique_ptr<Solver> SolverUPtr;

}; // namespace ModifiedSchwarz

#endif // SCHWARZSOLVER_HPP
