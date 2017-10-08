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

#define DEBUG_OUT(S) std::cout << S << std::endl;

using namespace ModifiedSchwarz;

TEST(CauchyInterp)
{
    DEBUG_OUT("-----========== Cauchy Interp check ==========-----")

    // Create grid over domain -- square grid with some points in and some
    // points out. Observe output of relational operators on matrix. Can these
    // then be used to index the matrices for subviews? Or is find() requried?

    using rowvec = arma::rowvec;
    DEBUG_OUT("Create complex grid via repmats.")
    cx_mat Z = cx_mat(arma::repmat(arma::linspace<rowvec>(-1., 1., 10), 10, 1),
                      arma::repmat(arma::linspace<colvec>(-1., 1., 10), 1, 10));
    DEBUG_OUT(Z)

    CHECK(true);

    DEBUG_OUT("-----========== Done with Cauchy Interp check ==========-----")
}
