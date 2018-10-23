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

#include "UnitCircleDomain.h"

namespace ModifiedSchwarz
{

UnitCircleDomain::UnitCircleDomain(cx_vec centers, colvec radii)
    : _centers(centers),
      _radii(radii)
{}


////////////////////////////////////////////////////////////////////////
uvec
UnitCircleDomain::isOnC(unsigned j, const cx_vec& z) const
{
    return find(abs(qv0(j) - abs(z - dv0(j))) < eps2pi);
}

////////////////////////////////////////////////////////////////////////
umat
UnitCircleDomain::isOnCj(unsigned j, const cx_mat& z) const
{
    return abs(qv0(j) - abs(z - dv0(j))) < eps2pi;
}

////////////////////////////////////////////////////////////////////////
umat
UnitCircleDomain::isOnBoundary(const cx_mat& z) const
{
    // FIXME: Need threaded speedup?
    umat mask(size(z), arma::fill::zeros);
    for (unsigned i = 0; i < z.n_elem; ++i)
    {
        for (unsigned j = 0; j < connectivity(); ++j)
            if (fabs(fabs(z(i) - dv0(j)) - qv0(j)) < eps2pi)
            {
                mask(i) = 1;
                break;
            }
    }

    return mask;
}

////////////////////////////////////////////////////////////////////////
umat
UnitCircleDomain::inDomain(const cx_mat& Z) const
{
    // FIXME: This is really bad if parallelized. Who incremented the iterator!?
    umat mask(size(Z));
    auto iter = mask.begin();
    auto end = mask.end();
    Z.for_each([&](const cx_double& v)
            {
                bool isIn = abs(v) < 1. - eps2pi;
                for (unsigned j = 0; j < m(); ++j) isIn &= abs(v - dv(j)) > qv(j) - eps2pi;
                if (iter != end) *(iter++) = (unsigned)isIn;
            });
    return mask;
}

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
cx_mat
UnitCircleDomain::ngrid(unsigned npts) const
{
    return cx_mat(repmat(arma::linspace<rowvec>(-1., 1., npts), npts, 1),
                  repmat(arma::linspace<colvec>(1., -1., npts), 1, npts));
}

////////////////////////////////////////////////////////////////////////
UnitCircleDomain domainExample3()
{
    return UnitCircleDomain(cx_vec{ cx_double(-0.2517, 0.3129), cx_double(0.2307, -0.4667) },
            colvec{ 0.2377, 0.1557 });
}

}; // namespace ModifiedSchwarz
