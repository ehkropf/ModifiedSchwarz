#include "SpectralData.hpp"

int main()
{
    using namespace ModifiedSchwarz;

    // Spectral truncation level.
    unsigned N = 64;

    SpectralData smat(domainExample3(), N);

    const cx_mat& L = smat.matrix();
    L.save("Lmatrix.dat", arma::arma_ascii);

    return 0;
}
