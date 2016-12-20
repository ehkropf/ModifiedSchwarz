#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "SpectralMethod.hpp"
#include "UnitCircleDomain.hpp"

cx_vec polesInHoles(const cx_vec&, const UnitCircleDomain&);

TEST(theRHS)
{
    using namespace ModifiedSchwarz;
    using namespace arma;

    auto D = domainExample3();

    auto g = [&D](const cx_vec& z) -> colvec { return real(polesInHoles(z, D)); };
}
