#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

class Problem;
class Solution;

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

    Solver();
    Solver(Method method);

    Solution solve(const Problem&);
    Solution solve(const Problem&, const Solution&);
};

}; // namespace ModifiedSchwarz

#endif // SOLVER_HPP
