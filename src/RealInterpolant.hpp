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
    RealInterpolant(UnitCircleDomain domain, mat samples)
        : _domain(domain), _boundaryData(samples) { prepareInterpolant(); }

    colvec eval(const cx_vec& z) const;
};

}; // namespace ModifiedSchwarz

#endif // REALINTERPOLANT_HPP
