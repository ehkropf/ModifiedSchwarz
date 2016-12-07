#ifndef SPECTRALDATA_HPP
#define SPECTRALDATA_HPP

#include <memory>

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

#define DEFAULT_SPECTRAL_TRUNCATION 64

class SpectralData
{
    UnitCircleDomain _domain;
    cx_mat _spectralMatrix;

protected:
    cx_mat constructMatrix(uint);

public:
    SpectralData(const UnitCircleDomain& domain, uint truncation = DEFAULT_SPECTRAL_TRUNCATION)
        : _domain(domain), _spectralMatrix(constructMatrix(truncation)) {}

    const UnitCircleDomain& domain() const { return _domain; }
    const cx_mat& matrix() const { return _spectralMatrix; }
    uint truncation() const { return (_spectralMatrix.n_cols/2 - _domain.m())/(_domain.m() + 1); }

    friend bool operator==(const SpectralData& left, const SpectralData& right)
    {
        return left._domain == right._domain;
    };
};

typedef std::shared_ptr<const SpectralData> SpectralDataSPtr;

}; // namespace ModifiedSchwarz

#endif // SPECTRALDATA_HPP
