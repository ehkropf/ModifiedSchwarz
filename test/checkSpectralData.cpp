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
    refL.load("../test/refmat.dat");

    CHECK(arma::approx_equal(L, refL, "absdiff", 1e-4));
}

TEST(Sharing)
{
    SpectralData data(domainExample3());
    SpectralData data2 = data;

    CHECK(&data.matrix() == &data2.matrix());
}
