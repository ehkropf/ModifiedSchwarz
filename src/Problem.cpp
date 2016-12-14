#include "Problem.hpp"

namespace ModifiedSchwarz
{

Solution
Problem::solve()
{
    return Solver().solve(*this);
}

Solution
Problem::solve(Solver::Method m)
{
    return Solver(m).solve(*this);
}

Solution
Problem::solve(const Solution& prevSolution)
{
    return Solver().solve(*this, prevSolution);
}

Solution
Problem::solve(const Solution& prevSolution, Solver::Method m)
{
    return Solver(m).solve(*this, prevSolution);
}

}; // namespace ModifiedSchwarz
