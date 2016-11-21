#ifndef SCHWARZSOLUTION_HPP
#define SCHWARZSOLUTION_HPP

#include <memory>
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Abstract representation of solution to the Schwarz problem.
 */
class SchwarzSolution
{
public:
    virtual ~SchwarzSolution() = default;

    virtual cvecd eval(const cvecd& points) = 0;
};

typedef std::unique_ptr<SchwarzSolution> SchwarzSolutionUPtr;

}; // namespace ModifiedSchwarz

#endif // SCHWARZSOLUTION_HPP
