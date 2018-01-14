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

#ifndef UNITCIRCLEDOMAIN_HPP
#define UNITCIRCLEDOMAIN_HPP

#include "SchwarzTypes.hpp"

// FIXME: Move function definitions to cpp file.

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 * Represents unit circle domain by holding vectors of center and radii
 * of the inner circles.
 *
 * Note centers and radii stored (and used in construction) represent
 * ONLY the inner circles, as we know the outer circle is unit. There
 * are then two numbering schemes:
 * - by index {0, ..., m-1} is the index of the stored center/radius,
 * - or by boundary number {0, 1, ..., m} where boundary 0 is the
 *   unit circle and (boundary number - 1) is the index of the stored
 *   center or radius.
 * The distinction is made in the accessor functions below because it
 * makes certain algorithms easier to write.
 */
class UnitCircleDomain
{
    cx_vec _centers;
    colvec _radii;

public:
    UnitCircleDomain() {}
    UnitCircleDomain(cx_vec, colvec);

    const cx_vec &centers() const { return _centers; }
    const colvec &radii() const { return _radii; }

    //! Access center by index.
    const cx_double dv(unsigned j) const { return _centers(j); }
    //! Access radius by index.
    const double qv(unsigned j) const { return _radii(j); }

    //! Access center by boundary number.
    const cx_double dv0(unsigned j) const { return j > 0 ? _centers(j-1) : 0.; }
    //! Access radius by boundary number.
    const double qv0(unsigned j) const { return j > 0 ? _radii(j-1) : 1.; }

    unsigned connectivity() const { return unsigned(_centers.n_elem) + 1; }
    unsigned m() const { return unsigned(_centers.n_elem); }

    /*!
     * Given a boundary number, return a vector of indices where z is
     * on that boundary.
     */
    uvec isOnC(unsigned j, const cx_vec& z) const;

    /*!
     * Given a boundary number and a set of points, return an unsigned matrix
     * of the same size set to 1 if the point is on boundary j and 0 if not.
     */
    umat isOnCj(unsigned, const cx_mat&) const;

    /*!
     * Given a set of points, return a matrix of unsigned values set to 1
     * if a point is on the boundary and 0 if not.
     */
    umat isOnBoundary(const cx_mat&) const;

    /*!
     * Given a matrix of points, returns an unsigned matrix of the same size
     * with 1 if the point is in the domain and 0 if not.
     */
    umat inDomain(const cx_mat&) const;

    /*!
     * Returns matrix of n points on boundary where each column represents a
     * boundary, whith leftmost column j=0 progressing linearly to rightmost
     * j=m. Points are created by parameterizing boundary by angle using n
     * equally spaced angles, and 0 as the starting angle.
     */
    cx_mat boundaryPoints(unsigned n) const;

    /*!
     * Returns n-by-n square grid of points covering the unit disk. Points are
     * not guaranteed to be in the closure of the domain and should be checked.
     * Note upper-left element is -1.0+1.0i and lower-right element is 1.0-1.0i
     * (Cartesian orientation).
     */
    cx_mat ngrid(unsigned n) const;

    //! Domain equality.
    friend bool operator==(const UnitCircleDomain& a, const UnitCircleDomain& b)
    {
        return arma::all(a._centers == b._centers) && arma::all(a._radii && b._radii);
    }
};

////////////////////////////////////////////////////////////////////////
/*!
 * Example domain defined in matlab code (it's cannon at this point):
 *
 *   D = circleRegion(...
 *              circle(0, 1), ...
 *              circle(-0.2517+0.3129i, 0.2377), ...
 *              circle(0.2307-0.4667i, 0.1557));
 *
 */
UnitCircleDomain domainExample3();

}; // namespace ModifiedSchwarz

#endif // UNITCIRCLEDOMAIN_HPP
