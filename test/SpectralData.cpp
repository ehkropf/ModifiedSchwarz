#include <iostream>

#include "UnitTest++/UnitTest++.h"

#include "UnitCircleDomain.hpp"
#include "SpectralData.hpp"

using namespace ModifiedSchwarz;

TEST(Sharing)
{
    SpectralDataSPtr data(new SpectralData(domainExample3()));

    {
        SpectralDataSPtr data2 = data;
        CHECK_EQUAL(data.use_count(), 2);
    }

    CHECK_EQUAL(data.use_count(), 1);
}
