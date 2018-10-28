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

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <armadillo>

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
/*!
 * Vector polynomial evaluation.
 *
 * For n+1 coefficients in vector a and any x[i] in vector x, a degree
 * n polynomial over x is evaluated by
 *
 *     a[0]*x[i]^n + a[1]*x[i]^(n-1) + ... + a[n-1]*x[i] + a[n]
 *
 * using Horner's method.
 */
template <typename ArmaMatLike, typename ArmaVecLike>
ArmaMatLike polyval(const ArmaVecLike& a, const ArmaMatLike& x)
{
    ArmaMatLike pn(arma::size(x), arma::fill::zeros);
    for (const auto& ai : a) pn = pn%x + ai;

    return pn;
}

//! Recursively calculate the n-th derivative of a differentiable class.
/*! The class must have the method `derivatvive()` defined, returning the
 *  same class type. If n == 0, a copy of the class is returned.
 */
template <typename Differentiable>
Differentiable recursNthDeriv(const Differentiable& C, unsigned n)
{
    if (n > 1) return recursNthDeriv(C, n-1).derivative();
    if (n == 0) return Differentiable(C);
    return C.derivative();
}

}; // namespace ModifiedSchwarz

#endif // UTILITY_HPP
