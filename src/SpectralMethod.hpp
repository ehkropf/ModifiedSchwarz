#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "SchwarzTypes.hpp"
#include "SpectralConstants.hpp"
#include "SpectralData.hpp"
#include "Problem.hpp"
#include "Solution.hpp"

namespace ModifiedSchwarz
{

// FIXME: There is no way to communicate truncation level to the
// spectral matrix and solver. Only default ever taken.

////////////////////////////////////////////////////////////////////////
/*!
 * Solves the modified Schwarz problem via the spectral method.
 * Call solve(...) with a previous solution to reuse the SpectralData
 * created for the last solver run. Saves reconstructing the spectral
 * matrix which is unique per domain+truncation.
 */
class SpectralMethod
{
    SpectralData::Ptr _data;
    RealInterpolant _imagPart;

public:
    SpectralMethod(const Problem&);
    SpectralMethod(const Problem&, const Solution&);

    Solution solve();

    const cx_mat& matrix() const { return _data->matrix(); }
    const SpectralData& data() const { return *_data; }

    //! Compute system RHS using trapezoidal rule.
    cx_vec computeRHS(unsigned numSamplePoints = SpectralConstants::kTrapezoidalPoints());
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
