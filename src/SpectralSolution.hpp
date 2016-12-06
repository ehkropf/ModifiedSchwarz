#ifndef SPECTRALSOLUTION_HPP
#define SPECTRALSOLUTION_HPP

#include "SchwarzTypes.hpp"
#include "SpectralData.hpp"

namespace ModifiedSchwarz
{

/*!
 * Solution to Schwarz problem using the spectral method.
 */
class SpectralSolution
{
    cmatd _coefficients;
    SpectralDataSPtr _domainData;

public:
    SpectralSolution(cmatd coefficients) : _coefficients(coefficients) {}
    SpectralSolution(cmatd coefficients, SpectralDataSPtr data)
        : _coefficients(coefficients), _domainData(data) {}

    const cmatd& coefficients() const { return _coefficients; }
    SpectralDataSPtr data() const { return _domainData; }

    cvecd eval(const cvecd&) { return cvecd(_coefficients.n_elem).zeros(); }
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLUTION_HPP
