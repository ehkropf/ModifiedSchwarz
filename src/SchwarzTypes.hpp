#ifndef SCHWARZTYPES_HPP
#define SCHWARZTYPES_HPP

#include <complex>
#include <armadillo>

namespace ModifiedSchwarz
{

//! Column vector of unsigned integers.
using uvec = arma::uvec;
//! Column vector of doubles.
using colvec = arma::colvec;
//! Matrix of doubles.
using mat = arma::mat;
//! Complex double.
using cx_double = arma::cx_double;
//! Column vector of complex doubles.
using cx_vec = arma::cx_vec;
//! Matrix of complex doubles.
using cx_mat = arma::cx_mat;

const double pi = std::acos(-1);
const cx_double i2pi(0.0, 2.0*pi);
const double eps2pi = std::numeric_limits<double>::epsilon()*2.*pi;

}; // namespace ModifiedSchwarz

#endif // SCHWARZTYPES_HPP
