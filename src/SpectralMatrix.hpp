#ifndef SPECTRALMATRIX_HPP
#define SPECTRALMATRIX_HPP

#include <memory>
#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

/*!
 * Container class for shared spectral matrix.
 */
class SpectralMatrix
{
    UnitCircleDomain _domain; // Acts as identifier.
    cmatd _domainMatrix;

protected:
    void constructMatrix(const uint truncation);

public:
    SpectralMatrix(const UnitCircleDomain& domain, const uint truncation)
        : _domain(domain) { constructMatrix(truncation); }

    const cmatd& matrix() const { return _domainMatrix; }
    const UnitCircleDomain& domain() const { return _domain; }
    uint truncation() const { return (_domainMatrix.n_cols/2 - _domain.m())/(_domain.m() + 1); }
};

typedef std::shared_ptr<SpectralMatrix> SpectralMatrixSPtr;

}; // namespace ModifiedSchwarz

#endif // SPECTRALMATRIX_HPP
