#include <iostream>

#include "UnitTest++/UnitTest++.h"

#include "UnitCircleDomain.hpp"
#include "SpectralData.hpp"

using namespace ModifiedSchwarz;

TEST(Sharing)
{
    SpectralData data(domainExample3());
    SpectralData data2 = data;

    CHECK(&data.matrix() == &data2.matrix());
}
