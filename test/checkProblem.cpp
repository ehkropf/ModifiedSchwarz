#include <armadillo>

#include "UnitTest++/UnitTest++.h"

#include "Problem.hpp"
#include "UnitCircleDomain.hpp"

using namespace ModifiedSchwarz;

struct ASolution
{
    static const bool value = true;
};

class ASolver;
typedef Problem<ASolver, ASolution> AProblem;

class ASolver
{
public:
    ASolution solve(const AProblem&) { return ASolution(); }
    ASolution solve(const AProblem& prob, const ASolution&) { return solve(prob); }
};

TEST(solve1)
{
    AProblem problem(domainExample3(), cx_mat(1, 3, arma::fill::zeros), ASolver());
    ASolution sol = problem.solve();

    CHECK(sol.value);
}
