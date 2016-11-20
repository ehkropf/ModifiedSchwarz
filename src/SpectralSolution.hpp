#ifndef SPECTRALSOLUTION_HPP
#define SPECTRALSOLUTION_HPP

#include "SchwarzSolution.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Solution to Schwarz problem using the spectral method.
 */
class SpectralSolution : public SchwarzSolution
{
    cmatd _coefficients;

public:
    SpectralSolution(const cmatd& coefficients)
        : _coefficients(coefficients) {}

    virtual cvecd eval(const cvecd&) { return cvecd(); }
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLUTION_HPP
