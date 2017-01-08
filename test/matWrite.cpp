#include "SpectralData.hpp"

int main()
{
    using namespace ModifiedSchwarz;

    SpectralData smat(domainExample3(), 64);
    const cx_mat& L = smat.matrix();
    L.save("Lmatrix.dat", arma::arma_ascii);

    return 0;
}
