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

#include "UnitTest.h"

#include "SchwarzTypes.h"
#include "ZFMM_Wrapper.h"

using namespace ModifiedSchwarz;

SUITE(FMMTest)
{

TEST(FMMTestLabel)
{
    TEST_FILE("FMM evaluation");
}

TEST(FMMEvalCheck)
{
    TEST_LINE("Result check");

    int nsource = 800;
    int ntarget = 1000;

    colvec phi;

    phi.randu(nsource);
    phi *= 2.*pi;
    cx_vec source = arma::exp(cx_double(0., 1.)*phi);

    cx_vec dipstr = arma::ones<cx_vec>(nsource);

    phi.randu(ntarget);
    phi *= 2.*pi;
    cx_vec target = arma::exp(cx_double(0., 1.)*phi) + 2.;

    cx_vec pottarg(ntarget);

    ZFMM2d fmm(source, dipstr, target);

    cx_mat I = arma::repmat(-source.st(), target.n_elem, 1);
    I.each_col() += target;
    cx_vec result = (1./I)*dipstr;

    CHECK(arma::approx_equal(result, fmm.pottarg, "reldiff", 1e-14));

    TEST_DONE;
}

} // SUITE
