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
    cx_vec _constants;
    cx_mat _coefficients;
    SpectralDataSPtr _domainData;

protected:
    cx_vec extractConstants(const cx_mat&);
    cx_mat extractCoefficients(const cx_mat&);

public:
    SpectralSolution(const cx_mat& solutionMatrix)
        : _constants(extractConstants(solutionMatrix)),
          _coefficients(extractCoefficients(solutionMatrix)) {}

    SpectralSolution(const cx_mat& solutionMatrix, SpectralDataSPtr data)
        : _constants(extractConstants(solutionMatrix)),
          _coefficients(extractCoefficients(solutionMatrix)),
          _domainData(data) {}

    const cx_vec& constants() const { return _constants; }
    const cx_mat& coefficients() const { return _coefficients; }
    SpectralDataSPtr data() const { return _domainData; }

    cx_vec eval(const cx_vec&);
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLUTION_HPP
