/*
 *  Example of ModifiedSchwarz use.
 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "Problem.h"

#define STDOUT(S) std::cout << S << std::endl

#define MFNAME "ex1.meta"
#define DFNAME "ex1.data"

using namespace ModifiedSchwarz;

////////////////////////////////////////////////////////////////////////
struct GridExtents
{
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    GridExtents() {}

    GridExtents(double xmin, double xmax, double ymin, double ymax)
        : xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax)
    {}

    GridExtents(colvec extents)
    {
        *this = GridExtents(extents(0), extents(1), extents(2), extents(3));
    }

    colvec array() const { return colvec{xmin, xmax, ymin, ymax}; }
};

struct GridInformation
{
    UnitCircleDomain domain;
    unsigned npts;
    GridExtents extents;

    enum StreamType { File, Readable };
    StreamType streamtype;

    GridInformation(UnitCircleDomain domain, unsigned npts)
        : domain(domain),
          npts(npts),
          extents(-1., 1., -1., 1.),
          streamtype(File)
    {}
};

std::ostream& operator<<(std::ostream& os, GridInformation& g)
{
    switch (g.streamtype)
    {
        case GridInformation::File:
            os << "m=" << g.domain.m() << std::endl;
            os.precision(15);
            os.setf(std::ios::fixed);
            g.domain.centers().raw_print(os);
            g.domain.radii().raw_print(os);
            os << "res=" << g.npts << std::endl;
            g.extents.array().t().raw_print(os);
            break;

        case GridInformation::Readable:
            os << "Inner holes: " << g.domain.connectivity() << "\n"
                << "Centers:\n" << g.domain.centers()
                << "Radii:\n" << g.domain.radii()
                << "Resolution: " << g.npts << "\n"
                << "X-extents: [" << g.extents.xmin << "," << g.extents.xmax << "]\n"
                << "Y-extents: [" << g.extents.ymin << "," << g.extents.ymax << "]"
                << std::endl;
            break;
    }
    return os;
}

////////////////////////////////////////////////////////////////////////
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

    Solution sol = problem.solve();
    STDOUT("Solver run.");

    /*
     *  Grid points in domain for evaluation.
     */
    unsigned res = 400;
    cx_vec z = vectorise(domain.ngrid(res));
    auto mask = domain.inDomain(z);
    z = z(find(mask));

    /*
     * Output grid metadata.
     */
    auto gmeta = GridInformation(domain, res);
    STDOUT("\nWriting metadata");
    std::ofstream ofs(MFNAME, std::ios::out);
    ofs << gmeta;
    ofs.close();

    gmeta.streamtype = GridInformation::Readable;
    STDOUT("\nReadable:\n" << gmeta);

    /*
     *  Solution can be evaulated like a function.
     */
    STDOUT("evaluating points " << z.n_elem << " points ...");
    cx_vec w = sol(z);
    STDOUT("done; OMG that's slow without FMM!");

    auto&& data = cx_mat(join_rows(z, w));
    STDOUT("saving data to ex1.data");
    data.save("ex1.data", arma::raw_binary);

    std::string cmd("../example/drawex.py " DFNAME " " MFNAME " ex1.png");
    STDOUT("Creating image: " << cmd);
    system(cmd.c_str());

    cmd = std::string("open ex1.png");
    STDOUT("Showing image: " << cmd);
    system(cmd.c_str());

    return 0;
}
