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

#include "CauchyInterpolant.hpp"

namespace ModifiedSchwarz
{

//////////////////////////////////////////////////////////////////////////////////
CauchyInterpolant::CauchyInterpolant(const cx_mat& boundary_values, const UnitCircleDomain& domain)
    : _domain(domain),
      _bdry_points(boundary_values)
{}

//////////////////////////////////////////////////////////////////////////////////
cx_mat
CauchyInterpolant::operator()(const cx_mat& z) const
{
    cx_mat w(size(z));
    w.fill(arma::datum::nan);
    uvec mask = find(_domain.inDomain(z));

    // FIXME: Dummy evaluation.
    w(mask) = z(mask);

    return w;
}

}; // namespace ModifiedSchwarz
