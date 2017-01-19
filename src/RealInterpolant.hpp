#ifndef REALINTERPOLANT_HPP
#define REALINTERPOLANT_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 * Provide interpolation on domain boundaries given real data at
 * evenly spaced points on each boundary.
 *
 * Boundary data is stored in a matrix with each column representing
 * a boundary. Boundary sample data must be real and evenly spaced.
 *
 * Let M be the number of sample points on a boundary. The M-point
 * DFT is taken for that boundary data and the N = ceil((M - 1)/2)
 * first coefficients are used for the interpolation polynomial
 *
 *                            --- N
 *                            \
 *     p(z) = real(c_0) + 2 *  .     c_i * ((z - d_j)/q_j)^i
 *                            /
 *                            --- i=1
 *
 * for points z on boundary C_j.
 */
class RealInterpolant
{
    UnitCircleDomain _domain;
    mat _boundaryData;
    colvec _constants;
    cx_mat _coefficients;

protected:
    void prepareInterpolant();

public:
    RealInterpolant() {}
    RealInterpolant(UnitCircleDomain domain, mat samples);
    RealInterpolant(UnitCircleDomain, colvec constants, cx_mat coefficients);

    const UnitCircleDomain& domain() const { return _domain; }
    const mat& boundaryData() const { return _boundaryData; }
    const colvec& constants() const { return _constants; }
    const cx_mat& coefficients() const { return _coefficients; }

    colvec operator()(const cx_vec& z) const;
};

}; // namespace ModifiedSchwarz

#endif // REALINTERPOLANT_HPP
