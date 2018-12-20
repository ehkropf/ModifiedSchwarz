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

#ifndef SPECTRALDATA_H
#define SPECTRALDATA_H

#include <memory>

#include "SchwarzTypes.h"
#include "UnitCircleDomain.h"
#include "SolverData.h"
#include "SpectralConstants.h"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
//! Spectral method for the modified Schwarz problem.
/*!
 * Each domain has a unique spectral matrix (modulo the chosen
 * truncation level for the boundary function series). For each domain
 * then this class should be passed around as a shared pointer. See
 * associated typedef.
 *
 * For a description of the method and matrix, see
 *
 * * D. Crowdy, E. Kropf, C. Green and M. Nasser, "The Schottky–Klein prime
 *   function: a theoretical and computational tool for applications", _IMA
 *   Journal of Applied Mathematics_, 81, 2016, pp. 589--628.
 */
class SpectralData : public SolverData
{
    // FIXME: Either this goes, or the calculation in the method goes.
    // It makes no sense to have both.
    unsigned _truncation;
    UnitCircleDomain _domain;
    cx_mat _spectralMatrix;

protected:
    //! Builds the spectral domain matrix.
    /*!
     *  This matrix is the same for _all_ problems defined on a given
     *  domain.
     */
    cx_mat constructMatrix();

public:
    //! Build method data given domain.
    SpectralData(const UnitCircleDomain&);
    //! Specify truncation level for spectral representation.
    SpectralData(const UnitCircleDomain&, unsigned);

    //! Override SolverData::Ptr typedef.
    using Ptr = std::shared_ptr<SpectralData>;

    //! Domain of definition.
    const UnitCircleDomain& domain() const { return _domain; }
    //! View of domain spectral matrix.
    const cx_mat& matrix() const { return _spectralMatrix; }
    //! Spectral method representation truncation level.
    unsigned truncation() const
    {
        return (matrix().n_cols/2 - _domain.m())/(_domain.m() + 1);
    }

    // FIXME: This should also check truncation level!
    //! Two SpectralData objects are the same if their domains are the same.
    friend bool operator==(const SpectralData& left, const SpectralData& right)
    {
        return left._domain == right._domain;
    };
};

} // namespace ModifiedSchwarz

#endif // SPECTRALDATA_H
