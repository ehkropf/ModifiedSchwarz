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
    cmatd _spectralMatrix;

protected:
    cmatd constructMatrix(uint);

public:
    SpectralData(const UnitCircleDomain& domain, uint truncation = DEFAULT_SPECTRAL_TRUNCATION)
        : _domain(domain), _spectralMatrix(constructMatrix(truncation)) {}

    const UnitCircleDomain& domain() const { return _domain; }
    const cmatd& matrix() const { return _spectralMatrix; }

    friend bool operator==(const SpectralData& left, const SpectralData& right)
    {
        return left._domain == right._domain;
    };
};

typedef std::shared_ptr<SpectralData> SpectralDataSPtr;

}; // namespace ModifiedSchwarz

#endif // SPECTRALDATA_HPP
