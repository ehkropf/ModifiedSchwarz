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

#include <iostream>

#include "UnitTest++.h"

#include "UnitCircleDomain.hpp"
#include "SpectralData.hpp"

using namespace ModifiedSchwarz;

TEST(Matrix)
{
    SpectralData data(domainExample3(), 64);
    const cx_mat& L = data.matrix();

    cx_mat refL;
    refL.load("../test/refMatrix.dat");

    CHECK(arma::approx_equal(L, refL, "absdiff", 1e-4));
}

TEST(Sharing)
{
    SpectralData::Ptr pData = std::make_shared<SpectralData>(domainExample3());
    SpectralData::Ptr pData2 = pData;

    CHECK(&pData->matrix() == &pData2->matrix());
}
