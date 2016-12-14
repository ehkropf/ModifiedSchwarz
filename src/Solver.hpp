#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "SchwarzTypes.hpp"
#include "Problem.hpp"
#include "Solution.hpp"

namespace ModifiedSchwarz
{

///////////////////////////////////////////////////////////////////////////
/*!
 * Exists to dispatch Problem and (possibly) previous Solution data
 * to the proper solver method.
 *
 * Some solver methods may be accelerated by using previously computed
 * data, and this is passed around via a shared pointer stored in each
 * solution as appropriate.
 */
struct Solver
{
    enum Method { Spectral };
    Method method;

    Solver() : method(Method::Spectral) {}
    Solver(Method method) : method(method) {}

    Solution solve(const Problem&);
    Solution solve(const Problem&, const Solution&);
};

}; // namespace ModifiedSchwarz

#endif // SOLVER_HPP
