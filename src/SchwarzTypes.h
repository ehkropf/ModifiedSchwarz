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

#ifndef SCHWARZTYPES_H
#define SCHWARZTYPES_H

#include <complex>
#include <armadillo>

#ifdef DEBUG
#define SDEBUG(S) std::cout << "<debug> " << __FILE__ << "(" << __LINE__ << "): " << S << std::endl
#else
#define SDEBUG(S)
#endif // DEBUG

namespace ModifiedSchwarz
{

//! Column vector of unsigned integers.
using uvec = arma::uvec;

//! Unsinged integer matrix.
using umat = arma::umat;

//! Column vector of doubles.
using colvec = arma::colvec;

//! Row vector of doubles.
using rowvec = arma::rowvec;

//! Matrix of doubles.
using mat = arma::mat;

//! Complex double.
using cx_double = arma::cx_double;

//! Column vector of complex doubles.
using cx_vec = arma::cx_vec;

//! Row vector of complex doubles.
using cx_rvec = arma::cx_rowvec;

//! Matrix of complex doubles.
using cx_mat = arma::cx_mat;

//! Does this really need introduction?
const double pi = std::acos(-1);

//! Useful constant.
const cx_double i2pi(0.0, 2.0*pi);

//! Scaled machine epsilon.
const double eps2pi = std::numeric_limits<double>::epsilon()*2.*pi;

//! Not a number.
const double nan = arma::datum::nan;

//! Point threshold to use FMM.
const unsigned min_pts_for_FMM = 1e4;

}; // namespace ModifiedSchwarz

#endif // SCHWARZTYPES_H
