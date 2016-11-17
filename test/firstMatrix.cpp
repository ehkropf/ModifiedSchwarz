#include "ModifiedSchwarz.hpp"

int main()
{
    using namespace ModifiedSchwarz;

    // Spectral truncation level.
    unsigned N = 64;

    SpectralMatrix smat(domainExample3(), N);

    const cmatd& L = smat.getMatrix();
    L.save("Lmatrix.dat", arma::arma_ascii);

    return 0;
}
