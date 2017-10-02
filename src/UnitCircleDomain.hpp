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
    UnitCircleDomain(const cx_vec &centers, const colvec &radii)
        : _centers(centers), _radii(radii) {}

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
    uvec isOnC(unsigned j, const cx_vec& z) const
    { return find(abs(qv0(j) - abs(z - dv0(j))) < eps2pi); }

    cx_mat boundaryPoints(unsigned) const;

    friend bool operator==(const UnitCircleDomain& a, const UnitCircleDomain& b)
    {
        return arma::all(a._centers == b._centers) & arma::all(a._radii && b._radii);
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
