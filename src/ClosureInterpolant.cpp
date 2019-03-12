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

#include "ClosureInterpolant.h"
#include "Utility.hpp"
#include <stdexcept>

namespace ModifiedSchwarz
{

ClosureInterpolant::ClosureInterpolant(ComplexInterpolant bfun, CauchyInterpolant ifun)
    : _boundary(bfun),
      _interior(ifun)
{}

ClosureInterpolant::ClosureInterpolant(ComplexInterpolant cfun)
    : _boundary(cfun)
{
    if (!cfun.checkPartBoundaryValues())
    {
        throw std::runtime_error("Complex interpolant does not have valid boundary value state.");
    }
    ComplexBoundaryValues&& values = ComplexBoundaryValues(
            cfun.realPart().boundaryValues().points(),
            cx_mat(cfun.realPart().boundaryValues().values(), cfun.imagPart().boundaryValues().values())
            );
    _interior = CauchyInterpolant(values);
}

ClosureInterpolant::ClosureInterpolant(ComplexBoundaryValues values)
    : _boundary(ComplexInterpolant(values)),
      _interior(CauchyInterpolant(values))
{}

////////////////////////////////////////////////////////////////////////////////
void
ClosureInterpolant::funcDefinition(const cx_vec& z, cx_vec& w) const
{
    auto D = _boundary.domain();
    uvec onb = D.isOnBoundary(z);

    SDEBUG("Have " << z.n_elem << " points to evaulate");

    // Evaluate boundary points.
    uvec mask{arma::find(onb == 1)};
    SDEBUG("Number of boundary points found: " << mask.n_elem);
    if (mask.n_elem > 0)
    {
        w(mask) = _boundary(z(mask));
    }

    // Evaluate interior points.
    mask = uvec{arma::find(onb == 0)};
    SDEBUG("Number of interior points found: " << mask.n_elem);
    if (mask.n_elem > 0)
    {
        w(mask) = _interior(z(mask));
    }
}

////////////////////////////////////////////////////////////////////////////////
ClosureInterpolant
ClosureInterpolant::derivative() const
{
    return ClosureInterpolant(_boundary.derivative());
}

ClosureInterpolant
ClosureInterpolant::derivative(unsigned n) const
{
    return recursNthDeriv(*this, n);
}

} // namespace ModifiedSchwarz
