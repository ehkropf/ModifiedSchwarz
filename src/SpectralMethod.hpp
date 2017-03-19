#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "SchwarzTypes.hpp"
#include "SpectralConstants.hpp"
#include "SpectralData.hpp"
#include "Problem.hpp"
#include "Solution.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 * Solves the modified Schwarz problem via the spectral method.
 * Call solve(...) with a previous solution to reuse the SpectralData
 * created for the last solver run. Saves reconstructing the spectral
 * matrix which is unique per domain+truncation.
 */
class SpectralMethod
{
    unsigned _trapezoidalPoints;
    SpectralData::Ptr _data;
    RealInterpolant _imagPart;

public:
    SpectralMethod(const Problem&);
    SpectralMethod(const Problem&, const Solution&);

    Solution solve();

    const cx_mat& matrix() const { return _data->matrix(); }
    const SpectralData& data() const { return *_data; }

    //! Compute system RHS using trapezoidal rule. Uses number of points
    // SpectralConstants::kTrapezoidalPoints(), read on SpectralMethod
    // construction, in the rule.
    cx_vec computeRHS();

    //! Compute system RHS using `numSamplePoints` in trapezoidal rule.
    cx_vec computeRHS(unsigned numSamplePoints);
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
