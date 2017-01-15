#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <armadillo>

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

#endif // UTILITY_HPP
