#ifndef SCHWARZSOLUTION_HPP
#define SCHWARZSOLUTION_HPP

#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Abstract representation of solution to the Schwarz problem.
 */
class SchwarzSolution
{
    cmatd _domainMatrix;

public:
    virtual cvecd eval(const cvecd& points) = 0;
};

}; // namespace ModifiedSchwarz

#endif // SCHWARZSOLUTION_HPP
