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

#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
cx_mat
UnitCircleDomain::boundaryPoints(unsigned npts) const
{
    using namespace arma;

    cx_mat zb(npts, m()+1, fill::zeros);
    cx_vec circ = exp(i2pi*regspace<cx_vec>(0, npts-1)/npts);

    zb(span::all, span(0)) = circ;
    for (unsigned j = 0; j < m(); ++j)
    {
        zb(span::all, span(j+1)) =  _centers(j) + _radii(j)*circ;
    }

    return zb;
}

////////////////////////////////////////////////////////////////////////
UnitCircleDomain domainExample3()
{
    cx_vec centers{ cx_double(-0.2517, 0.3129), cx_double(0.2307, -0.4667) };
    colvec radii{ 0.2377, 0.1557 };

    return UnitCircleDomain(centers, radii);
}

}; // namespace ModifiedSchwarz
