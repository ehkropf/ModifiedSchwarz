#ifndef SCHWARZTYPES_HPP
#define SCHWARZTYPES_HPP

#include <complex>
#include <armadillo>

namespace ModifiedSchwarz
{

using uvec = arma::uvec;
using mat = arma::mat;
using cx_double = arma::cx_double;
using cx_vec = arma::cx_vec;
using cx_mat = arma::cx_mat;
using colvec = arma::colvec;

const double pi = std::acos(-1);
const cx_double i2pi(0.0, 2.0*pi);
const double eps2pi = std::numeric_limits<double>::epsilon()*2.*pi;


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
cx_vec polyval(const cx_vec& a, const cx_vec& x);

}; // namespace ModifiedSchwarz

#endif // SCHWARZTYPES_HPP
