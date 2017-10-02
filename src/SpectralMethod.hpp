/*
 * Copyright 2017 Everett Kropf.
 *
 * This file is part of ModifiedSchwarz.
 *
 * ModifiedSchwarz is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ModifiedSchwarz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ModifiedSchwarz.  If not, see <http://www.gnu.org/licenses/>.
 */

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
