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

public:
    SpectralMethod(const Problem& prob) : _data(prob.domain()) {}
    SpectralMethod(const Problem&, const Solution& prev)
        : _data(dynamic_cast<const SpectralData&>(prev.solverData())) {}

    Solution solve();
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
