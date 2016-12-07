#include "UnitTest++/UnitTest++.h"

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

using namespace ModifiedSchwarz;

TEST(Points)
{
    unsigned n = 16;
    UnitCircleDomain D = domainExample3();
    cmatd zb = D.boundaryPoints(n);

    CHECK_EQUAL(zb.n_cols, D.m()+1);
    CHECK_EQUAL(zb.n_rows, n);

    using namespace arma;
    double tol = std::numeric_limits<double>::epsilon()*2*std::acos(-1);
    CHECK(approx_equal(abs(zb.col(0)), vecd(n, fill::ones), "reldiff", tol));
    for (unsigned j = 0; j < D.m(); ++j)
        CHECK(approx_equal(abs(zb.col(j+1) - D.centers()(j)),
                           D.radii()(j)*vecd(n, fill::ones), "reldiff", tol));
}
