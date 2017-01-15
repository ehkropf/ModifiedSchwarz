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


}; // namespace ModifiedSchwarz

#endif // SCHWARZTYPES_HPP
