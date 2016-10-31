#include <iostream>
#include <cmath>

#include "ModifiedSchwarz.hpp"

int main()
{
    using namespace ModifiedSchwarz;
    using namespace arma;

    // Sample domain.
    unsigned m;
    cvecd dv;
    vecd qv;
    {
        UnitCircleDomain domain = domainExample3();
        m = domain.m();
        dv = domain.getCenters();
        qv = domain.getRadii();
    }

    // Series truncation level.
    unsigned N = 8;

    // Number of unknowns.
    unsigned Q = m*(N + 1) + N;

    // L matrix.
    cmatd L(Q, 2*Q, fill::zeros);

    // Block L_{0,0}.
    {
        cvecd tmp(N);
        tmp.fill(i2pi);
        L(span(0, N-1), span(Q, Q+N-1)) = diagmat(tmp);
    }

    // Blocks L_{0,j}.
    for (uint j = 1; j <= m; ++j)
    {
        uint c0 = Q + j*N + (j-1);

        if (dv(j-1) == 0.)
        {
            cvecd tmp(N);
            complexd logqvj = std::log(qv(j-1));
            for (uint i = 0; i < N; ++i)
            {
                tmp(i) = double(i+1)*logqvj;
            }

            uint c1 = c0 + N;
            L(span(0, N-1), span(c0+1, c1)) = -i2pi*diagmat(exp(tmp));
        }
        else
        {
            cvecd tmp(N);
            complexd logdvj = std::log(dv(j-1));
            for (uint i = 0; i < N; ++i)
            {
                tmp(i) = double(i)*logdvj;
            }
            L(span(0, N-1), c0+1) = -i2pi*qv(j-1)*exp(tmp);

            for (uint n = 3; n <= N+1; ++n)
            {
                L(span(n-2, N-1), c0+n-1)
                    = qv(j-1)*L(span(n-3, N-2), c0+n-2)%regspace(double(n-2), double(N-1))/double(n-2);
            }
        }
    }

    // Blocks L_{p,0}.
    for (uint p = 1; p <= m; ++p)
    {
        uint r0 = p*N + (p-1);

        if (dv(p-1) == 0.)
        {
            cvecd tmp(N);
            tmp(0) = qv(p-1);
            for (uint i = 1; i < N; ++i)
            {
                tmp(i) = qv(p-1)*tmp(i-1);
            }
            L(span(r0+1, r0+N), span(0, N-1)) = diagmat(i2pi*qv(p-1)*tmp);
        }
        else
        {
            cvecd tmp(N);
            tmp(0) = dv(p-1);
            for (uint i = 1; i < N; ++i)
            {
                tmp(i) = dv(p-1)*tmp(i-1);
            }
            L(r0, span(0, N-1)) = i2pi*qv(p-1)*tmp.t();

            L(r0+1, 0) = i2pi*qv(p-1)*qv(p-1);
            for (uint n = 2; n <= N; ++n)
            {
                L(span(r0+1, r0+n), n-1)
                   = -n*qv(p-1)*L(span(r0, r0+n-1), n-2)/regspace(-1., -double(n));
            }
        }
    }

    // Blocks L_{p,p}.
    for (uint p = 1; p <= m; ++p)
    {
        cvecd tmp(N+1);
        tmp.fill(-i2pi);
        uint r0 = p*N + (p-1);
        uint r1 = r0 + N;
        L(span(r0, r1), span(r0, r1)) = diagmat(tmp);
    }

    L.save("Lmatrix.dat", arma_ascii);

    return 0;
}
