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

#include "UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"
#include "CauchyInterpolant.hpp"
#include "TestFunctions.hpp"

#define DEBUG
#ifdef DEBUG
#define DEBUG_OUT(S) std::cout << S << std::endl
#else
#define DEBUG_OUT(S)
#endif // DEBUG

using namespace ModifiedSchwarz;

TEST(CauchyInterp)
{
    DEBUG_OUT("-----========== Cauchy Interp check ==========-----");

    unsigned n_pts = 18;
    auto D = domainExample3();

    // Create grid over domain -- square grid with some points in and some
    // points out. Observe output of relational operators on matrix. Can these
    // then be used to index the matrices for subviews? Or is find() requried?

    DEBUG_OUT("Create complex grid via repmats.");
    cx_mat Z = D.ngrid(n_pts);
//    cx_mat Z = cx_mat(arma::repmat(arma::linspace<rowvec>(-1., 1., n_pts), n_pts, 1),
//                     arma::repmat(arma::linspace<colvec>(-1., 1., n_pts), 1, n_pts));

//    DEBUG_OUT((abs(Z) < 1. - eps2pi));

    arma::Col<unsigned> mask(Z.n_elem);
    auto iter = mask.begin();
    auto end = mask.end();
    Z.for_each([&](cx_double& v)
            {
                bool isIn = abs(v) < 1. - eps2pi;
                for (unsigned j = 1; j <= D.m(); ++j) isIn &= abs(v - D.dv0(j)) > D.qv0(j) - eps2pi;
                if (iter != end) *(iter++) = isIn;
            });
    arma::Mat<unsigned> tmp(mask);
    tmp.reshape(size(Z));
    DEBUG_OUT(tmp);

    CHECK(true);

    DEBUG_OUT("-----========== Leaving Cauchy Interp check ==========-----");
}
