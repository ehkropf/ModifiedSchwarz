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

#include "Solution.h"

namespace ModifiedSchwarz
{

//////////////////////////////////////////////////////////////////////////////
Solution::Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart)
    : _realPart(realPart),
      _constants(constants),
      _imagPart(imagPart) {}

Solution::Solution(RealInterpolant realPart, colvec constants, RealInterpolant imagPart, SolverData::Ptr pSolverData)
        : _realPart(realPart),
          _constants(constants),
          _imagPart(imagPart),
          _pSolverData(pSolverData) {}

//////////////////////////////////////////////////////////////////////////////
cx_vec Solution::operator()(const cx_vec& z) const
{
    using namespace std::complex_literals;

    // Boundary points are given by realPart(z_j) + 1i*(constant_j + imagPart(z_j)).
    cx_vec w(size(z));
    w.fill(arma::datum::nan);

    const auto D = _realPart.domain();
    const unsigned m = D.m();
    for(unsigned j = 0; j <= m; ++j)
    {
        const auto inD = D.isOnC(j, z);
        w(inD) = _realPart.evalOn(z(inD), j)
            + 1.i*(_constants(j) + _imagPart.evalOn(z(inD), j));
    }

    return w;
}

}; // namespace ModifiedSchwarz
