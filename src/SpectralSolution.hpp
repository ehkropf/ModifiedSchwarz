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
    cx_mat _coefficients;
    SpectralDataSPtr _domainData;

public:
    SpectralSolution(cx_mat coefficients) : _coefficients(coefficients) {}
    SpectralSolution(cx_mat coefficients, SpectralDataSPtr data)
        : _coefficients(coefficients), _domainData(data) {}

    const cx_mat& coefficients() const { return _coefficients; }
    SpectralDataSPtr data() const { return _domainData; }

    cx_vec eval(const cx_vec&);
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLUTION_HPP
