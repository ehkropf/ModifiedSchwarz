#ifndef SCHWARZPROBLEM_HPP
#define SCHWARZPROBLEM_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

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
class Problem
{
    UnitCircleDomain _domain;
    cx_mat _boundaryData;

public:
    Problem(UnitCircleDomain domain, cx_mat boundaryData)
        : _domain(domain), _boundaryData(boundaryData) {}

    const UnitCircleDomain& domain() const { return _domain; }
    const cx_mat& data() const { return _boundaryData; }
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZPROBLEM_HPP
