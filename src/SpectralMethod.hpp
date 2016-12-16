#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "SchwarzTypes.hpp"
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
    SpectralData _data;
    RealInterpolant _imagPart;

public:
    SpectralMethod(const Problem& prob)
        : _data(prob.domain()), _imagPart(prob.interpolant()) {}

    SpectralMethod(const Problem& prob, const Solution& prev)
        : _data(dynamic_cast<const SpectralData&>(prev.solverData())),
          _imagPart(prob.interpolant()) {}

    Solution solve();

    //! Experiments have shown this to be a reasonable default value.
    const static unsigned kDefaultTrapezoidalPoints = 100;

    //! Compute system RHS using trapezoidal rule.
    cx_vec computeRHS(unsigned numSamplePoints = kDefaultTrapezoidalPoints);
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
