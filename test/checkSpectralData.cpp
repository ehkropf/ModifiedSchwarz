#include <iostream>

#include "UnitTest++/UnitTest++.h"

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
