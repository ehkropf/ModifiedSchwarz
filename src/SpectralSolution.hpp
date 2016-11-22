#ifndef SPECTRALSOLUTION_HPP
#define SPECTRALSOLUTION_HPP

#include "Solution.hpp"
#include "SpectralMatrix.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Solution to Schwarz problem using the spectral method.
 */
class SpectralSolution : public Solution
{
    cmatd _coefficients;
    SpectralMatrixSPtr _domainData;

public:
    SpectralSolution(const cmatd& coefficients) : _coefficients(coefficients) {}
    SpectralSolution(const cmatd& coefficients, SpectralMatrixSPtr data)
        : _coefficients(coefficients), _domainData(data) {}

    const cmatd& coefficients() const { return _coefficients; }
    SpectralMatrixSPtr data() { return _domainData; }

    virtual cvecd eval(const cvecd&) { return cvecd(_coefficients.n_elem).zeros(); }
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLUTION_HPP
