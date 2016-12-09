#ifndef SPECTRALDATA_HPP
#define SPECTRALDATA_HPP

#include <memory>

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

constexpr unsigned default_spectral_truncation = 64;

////////////////////////////////////////////////////////////////////////
/*!
 * Each domain has a unique spectral matrix (modulo the chosen
 * truncation level for the boundary function series). For each domain
 * then this class should be passed around as a shared pointer. See
 * associated typedef.
 *
 * See [elsewhere] for a description of the matrix.
 */
class SpectralData
{
    UnitCircleDomain _domain;
    cx_mat _spectralMatrix;

protected:
    cx_mat constructMatrix(uint);

public:
    SpectralData(const UnitCircleDomain& domain, uint truncation = default_spectral_truncation)
        : _domain(domain), _spectralMatrix(constructMatrix(truncation)) {}

    const UnitCircleDomain& domain() const { return _domain; }
    const cx_mat& matrix() const { return _spectralMatrix; }
    uint truncation() const
    {
        return (_spectralMatrix.n_cols/2 - _domain.m())/(_domain.m() + 1);
    }

    friend bool operator==(const SpectralData& left, const SpectralData& right)
    {
        return left._domain == right._domain;
    };
};

////////////////////////////////////////////////////////////////////////
/*!
 * Shared pointer to a const SpectralData instance. Can be re-used by solver
 * objects to speed up subsequent solutions.
 */
typedef std::shared_ptr<const SpectralData> SpectralDataSPtr;

}; // namespace ModifiedSchwarz

#endif // SPECTRALDATA_HPP
