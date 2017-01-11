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

}; // namespace ModifiedSchwarz
