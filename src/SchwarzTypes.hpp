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
