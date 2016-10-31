#include <iostream>
#include <cmath>

#include "ModifiedSchwarz.hpp"

int main()
{
    using namespace ModifiedSchwarz;

    // Sample domain.
    UnitCircleDomain domain = domainExample3();
    unsigned m = domain.m();
    cvecd dv = domain.getCenters();
    vecd qv = domain.getRadii();

    // Series truncation level.
    unsigned N = 8;

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

    // Blocks L_{0,j}.
    for (uint j = 0; j < m; ++j)
    {
        if (dv(j) == 0.0)
        {
            std::cout << "Block L_{0," << j+1 << "} has dv_" << j+1 << " = 0." << std::endl;
//            cvecd tmp(N);
//            complexd logdvj = std::log(dv(j));
//            for (uint i = 0; i < N; ++i)
//            {
//                tmp(i) = double(i+1)*logdvj;
//            }
//
//            uint c0 = Q-1 + j*N;
//            uint c1 = c0 + N-1; //Q-1 + j*N - 1;
//            L(arma::span(0, N-1), arma::span(c0, c1)) = -i2pi*arma::diagmat(arma::exp(tmp));
        }
        else
        {
            std::cout << "Block L_{0," << j+1 << "} is wrt non-zero center." << std::endl;
//            uint c0 = Q-1 + j*N;
//
//            cvecd tmp(N);
//            complexd logdvj = std::log(dv(j));
//            for (uint i = 0; i < N; ++i)
//            {
//                tmp(i) = double(i)*logdvj;
//            }
//            L(arma::span(0, N-1), c0+1) = qv(j)*arma::exp(tmp);
//
//            for (uint n = 3; n <= N+1; ++n)
//            {
//                L(arma::span(n-2, N-1), c0+n-1)
//                    = qv(j)*L(arma::span(n-3, N-2), c0+n-2)%arma::regspace(n-2, N-1)/(n-2);
//            }
        }
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
