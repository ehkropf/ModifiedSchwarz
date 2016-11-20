#ifndef SPECTRALMATRIX_HPP
#define SPECTRALMATRIX_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

/*!
 * Container class for the matrix used in the Schwarz problem spectral solver.
 */
class SpectralMatrix
{
    cmatd _theMatrix;

protected:
    void constructMatrix(const UnitCircleDomain& domain, const uint truncation);

public:
    SpectralMatrix(const UnitCircleDomain& domain, const uint truncation)
    { constructMatrix(domain, truncation); }

    const cmatd& getMatrix() const { return _theMatrix; }
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALMATRIX_HPP
