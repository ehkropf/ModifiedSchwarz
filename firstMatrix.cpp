#include <iostream>
#include <cmath>

#include "ModifiedSchwarz.hpp"
#include "exampleDomain3.hpp"

int main()
{
    using namespace ModifiedSchwarz;

    // Sample domain.
    UnitCircleDomain domain(ExampleDomain3::centers, ExampleDomain3::radii);
    unsigned m = domain.m();
    cvecd dv = domain.getCenters();
    vecd qv = domain.getRadii();

    // Series truncation level.
    unsigned N = 16;

    // Number of unknowns.
    unsigned Q = (m + 1)*N - 1;

    // L matrix.
    cmatd L(Q, 2*Q, arma::fill::zeros);

    // Block L_{0,0}.
    {
        cvecd tmp(N-1);
        tmp.fill(i2pi);
        L(arma::span(0, N-2), arma::span(Q, Q+N-2)) = arma::diagmat(tmp);
    }

    // Blocks L_{p,p}.
    for (uint p = 1; p <= m; ++p)
    {
        cvecd tmp(N);
        tmp.fill(-i2pi);
        uint r0 = p*N - 1;
        uint r1 = (p+1)*N - 2;
        L(arma::span(r0, r1), arma::span(r0, r1)) = arma::diagmat(tmp);
    }

    L.save("Lmatrix.dat", arma::arma_ascii);

    return 0;
}
