#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <memory>

#include "SchwarzTypes.hpp"
#include "RealInterpolant.hpp"

namespace ModifiedSchwarz
{

class SolverData;
using SolverDataSPtr = std::shared_ptr<SolverData>;

///////////////////////////////////////////////////////////////////////////
/*!
 *
 */
class Solution
{
    RealInterpolant _realPart;
    colvec _constants;
    RealInterpolant _imagPart;
    SolverDataSPtr _solverDataPtr;

public:
    Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart)
        : _realPart(realPart), _constants(constants), _imagPart(imagPart) {};

    Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart,
             SolverDataSPtr solverDataPtr)
        : _realPart(realPart), _constants(constants), _imagPart(imagPart),
          _solverDataPtr(solverDataPtr) {};

    const RealInterpolant& realPart() const { return _realPart; }
    const colvec& constants() const { return _constants; }
    const RealInterpolant& imagPart() const { return _imagPart; }
    SolverDataSPtr solverDataPtr() { return _solverDataPtr; }

    cx_vec eval(const cx_vec&);
};

}; // namespace ModifiedSchwarz

#endif // SOLUTION_HPP
