#ifndef SOLVERDATA_HPP
#define SOLVERDATA_HPP

#include <memory>

namespace ModifiedSchwarz
{

///////////////////////////////////////////////////////////////////////////
/*!
 * Abstract class to store data specific to a solver method.
 */
class SolverData
{
public:
    virtual ~SolverData() = default;

    using Ptr = std::unique_ptr<SolverData>;
};

}; // namespace ModifiedSchwarz

#endif // SOLVERDATA_HPP
