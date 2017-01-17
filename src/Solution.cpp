#include "Solution.hpp"

namespace ModifiedSchwarz
{

//////////////////////////////////////////////////////////////////////////////
Solution::Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart)
    : _realPart(realPart),
      _constants(constants),
      _imagPart(imagPart) {}

Solution::Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart, SolverData::Ptr pSolverData)
        : _realPart(realPart),
          _constants(constants),
          _imagPart(imagPart),
          _pSolverData(pSolverData) {}

//////////////////////////////////////////////////////////////////////////////
cx_vec Solution::eval(const cx_vec& z) const
{
    // Separate boundary and domain points.
    // Boundary points are given by realPart(z_j) + 1i*(constant_j + imagPart(z_j)).
    // Domain values are given by barycentric interpolant.

    return cx_vec();
}

}; // namespace ModifiedSchwarz
