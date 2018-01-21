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

#ifndef SPECRALCONST_H
#define SPECRALCONST_H

// FIXME: This is NOT a thread safe way to do this.
// FIXME: No way to query non-default values.
// FIXME: "k" names are horrible and not-intuitive of function.

namespace ModifiedSchwarz
{

//! Spectral method constants.
/*!
 * Static class providing constructor constants for spectral method.
 */
class SpectralConstants
{
    static bool _trapSet;
    static bool _truncSet;
    static unsigned _tmpTrapezoidalPoints;
    static unsigned _tmpSpectralTruncation;

    //! No public instances.
    SpectralConstants() {}

public:
    //! Number of collocation points for trapezoidal rule. Experiments have
    //! shown this to be a reasonable default value.
    constexpr static unsigned kDefaultTrapezoidalPoints = 100;

    //! Known good (via expermiment) default truncation level.
    constexpr static unsigned kDefaultSpectralTruncation = 96;

    //! Default number of points to use in trapezoidal quadrature rule.
    /*!
     * Returns default number of trapezoidal points to use unless set was
     * called. If set was previously called, that value is cleared and next
     * call to this function will return defaults unless set is called again.
     */
    static unsigned kTrapezoidalPoints();

    //! Default length of truncation in spectral representation.
    /*!
     * Returns default truncation level for spectral method unless set was
     * called. If set was previously called, that value is cleared and next
     * call to this function will return defaults unless set is called again.
     */
    static unsigned kSpectralTruncation();

    /*!
     *  Sets value for next call of kTrapezoidalPoints(). Note SpectralMethod
     *  reads this constant on construction, and thus will undo any set call.
     */
    static void setTrapezoidalPoints(const unsigned trapezoidalPoints);

    /*!
     *  Sets value for next call of kTrapezoidalPoints(). Note SpectralMethod
     *  reads this constant on construction, and thus will undo any set call.
     */
    static void setTruncation(const unsigned truncationLevel);
};

}; // ModifiedSchwarz

#endif // SPECRALCONST_H
