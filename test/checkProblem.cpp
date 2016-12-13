#include "UnitTest++/UnitTest++.h"

#include "Problem.hpp"
#include "UnitCircleDomain.hpp"

using namespace ModifiedSchwarz;

TEST(solve1)
{
    Problem problem(domainExample3(), mat(1, 3, arma::fill::zeros));

    CHECK(false);
}
