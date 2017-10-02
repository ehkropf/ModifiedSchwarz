#ifndef SOLVERDATA_HPP
#define SOLVERDATA_HPP

#include <memory>

namespace ModifiedSchwarz
{

// FIXME: There should be a member to store the solver methed used. 
//        In this way, a solver instance can check for compatible previous
//        solution data.

///////////////////////////////////////////////////////////////////////////
/*!
 * Abstract class to store data specific to a solver method.
 */
class SolverData
{
public:
    virtual ~SolverData() = default;

    using Ptr = std::shared_ptr<SolverData>;
    using ConstPtr = std::shared_ptr<const SolverData>;
};

}; // namespace ModifiedSchwarz

#endif // SOLVERDATA_HPP
