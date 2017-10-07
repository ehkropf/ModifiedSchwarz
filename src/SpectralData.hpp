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

#ifndef SPECTRALDATA_HPP
#define SPECTRALDATA_HPP

#include <memory>

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"
#include "SolverData.hpp"
#include "SpectralConstants.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 * Each domain has a unique spectral matrix (modulo the chosen
 * truncation level for the boundary function series). For each domain
 * then this class should be passed around as a shared pointer. See
 * associated typedef.
 *
 * See [elsewhere] for a description of the matrix.
 */
class SpectralData : public SolverData
{
    unsigned _truncation;
    UnitCircleDomain _domain;
    cx_mat _spectralMatrix;

protected:
    cx_mat constructMatrix();

public:
    SpectralData(const UnitCircleDomain&);
    SpectralData(const UnitCircleDomain&, unsigned);

    using Ptr = std::shared_ptr<SpectralData>;

    const UnitCircleDomain& domain() const { return _domain; }
    const cx_mat& matrix() const { return _spectralMatrix; }
    unsigned truncation() const
    {
        return (matrix().n_cols/2 - _domain.m())/(_domain.m() + 1);
    }

    friend bool operator==(const SpectralData& left, const SpectralData& right)
    {
        return left._domain == right._domain;
    };
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALDATA_HPP
