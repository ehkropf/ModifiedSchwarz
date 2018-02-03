/*
 *  Example of ModifiedSchwarz use.
 */

#include <iostream>

#include "Problem.h"

#define STDOUT(S) std::cout << S << std::endl

using namespace ModifiedSchwarz;

/*
 *  Function defined by simple pole in each interior circle center.
 */
cx_vec polesInHoles(const cx_vec& z, const UnitCircleDomain& D)
{
    cx_vec w(size(z), arma::fill::zeros);
    for (auto& d : D.centers()) w += 1./(z - d);

    return w;
}

////////////////////////////////////////////////////////////////////////
int main()
{
    UnitCircleDomain domain = domainExample3();

    /*
     *  Imaginary part to define the problem.
     */
    auto h = [&domain](const cx_vec& z) -> colvec { return imag(polesInHoles(z, domain)); };

    /*
     *  Default number of BoundaryPoints on each boundary circle is 256.
     */
    RealBoundaryValues hv(BoundaryPoints(domain), h);

    /*
     *  Sample points in RealBoundaryValues are used to create an interpolant
     *  which will be used so solver can choose the proper number of points
     *  to use on the boundary.
     */
    Problem problem(hv);
    STDOUT(problem);

    Solution sol = problem.solve();
    STDOUT("Solver run.");

    /*
     *  Grid points in domain for evaluation.
     */
    cx_vec z = vectorise(domain.ngrid(400));
    auto mask = domain.inDomain(z);
    z = z(find(mask));

    /*
     *  Solution can be evaulated like a function.
     */
    STDOUT("evaluating points ...");
    cx_vec w = sol(z);
    STDOUT("done");

    STDOUT("z rows: " << z.n_rows);
    STDOUT("w rows: " << w.n_rows);
    //cx_mat(join_rows(z, w)).save("ex1.data", arma::arma_ascii);

    return 0;
}
