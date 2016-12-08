#ifndef UNITCIRCLEDOMAIN_HPP
#define UNITCIRCLEDOMAIN_HPP

#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Represents unit circle domain by holding vectors of center and radii of the
 * inner circles.
 */
class UnitCircleDomain
{
    cx_vec _centers;
    colvec _radii;

public:
    UnitCircleDomain(const cx_vec &centers, const colvec &radii)
        : _centers(centers), _radii(radii) {}

    const cx_vec &centers() const { return _centers; }
    const colvec &radii() const { return _radii; }

    unsigned connectivity() const { return unsigned(_centers.n_elem) + 1; }
    unsigned m() const { return unsigned(_centers.n_elem); }

    cx_mat boundaryPoints(unsigned) const;

    friend bool operator==(const UnitCircleDomain& a, const UnitCircleDomain& b)
    {
        return arma::all(a._centers == b._centers) & arma::all(a._radii && b._radii);
    }
};

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
