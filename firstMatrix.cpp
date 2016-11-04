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
        L(span(0, N-1), span(Q, Q+N-1)).diag().fill(i2pi);
    }

    // Blocks L_{0,j}.
    for (uint j = 1; j <= m; ++j)
    {
        uint c0 = Q + j*N + (j-1);
        complexd dj = dv(j-1);
        double qj = qv(j-1);

        if (dv(j-1) == 0.)
        {
            cvecd tmp(N);
            tmp(0) = -i2pi*qj;
            for (uint i = 1; i < N; ++i)
            {
                tmp(i) = qj*tmp(i-1);
            }
            L(span(0, N-1), span(c0+1, c0+N)).diag() = tmp;
        }
        else
        {
            cvecd tmp(N);
            tmp(0) = -i2pi*qj;
            for (uint i = 1; i < N; ++i)
            {
                tmp(i) = dj*tmp(i-1);
            }
            L(span(0, N-1), c0+1).diag() = tmp;

            for (uint n = 3; n <= N+1; ++n)
            {
                L(span(n-2, N-1), c0+n-1)
                    = qj*L(span(n-3, N-2), c0+n-2)%regspace(double(n-2), double(N-1))/double(n-2);
            }
        }
    }

    // Blocks L_{p,0}.
    for (uint p = 1; p <= m; ++p)
    {
        uint r0 = p*N + (p-1);
        complexd dp = dv(p-1);
        double qp = qv(p-1);

        if (dv(p-1) == 0.)
        {
            cvecd tmp(N);
            tmp(0) = i2pi*qp*qp;
            for (uint i = 1; i < N; ++i)
            {
                tmp(i) = qp*tmp(i-1);
            }
            L(span(r0+1, r0+N), span(0, N-1)).diag() = tmp;
        }
        else
        {
            cvecd tmp(N);
            tmp(0) = i2pi*qp*dp;
            for (uint i = 1; i < N; ++i)
            {
                tmp(i) = dp*tmp(i-1);
            }
            L(r0, span(0, N-1)) = tmp.st();

            L(r0+1, 0) = i2pi*qp*qp;
            for (uint n = 2; n <= N; ++n)
            {
                L(span(r0+1, r0+n), n-1)
                   = L(span(r0, r0+n-1), n-2)%(n*qp/regspace(1., double(n)));
            }
        }
    }

    // Blocks L_{p,j}.
    for (uint p = 1; p <= m; ++p)
    {
        uint r0 = p*N + (p-1);
        complexd dp = dv(p-1);
        double qp = qv(p-1);
        vecd ktmp = regspace(-1., -double(N+1));

        for (uint j = 1; j <= m; ++j)
        {
            if (j == p) { continue; }

            uint c0 = Q + j*N + (j-1);
            complexd dj = dv(j-1);
            double qj = qv(j-1);

            cvecd qtmp(N+1);
            qtmp(0) = qp;
            cvecd dtmp(N+1);
            complexd djp = dj - dp;
            dtmp(0) = 1./djp;
            for (uint i = 1; i < N+1; ++i)
            {
                qtmp(i) = qp*qtmp(i-1);
                dtmp(i) = dtmp(i-1)/(dj - dp);
            }
            L(span(r0, r0+N), c0+1) = -i2pi*qj*qtmp%dtmp;

            for (uint n = 3; n <= N+1; ++n)
            {
                L(span(r0, r0+N), c0+n-1)
                    = (qj/djp)*L(span(r0, r0+N), c0+n-2)%(ktmp - double(n-3))/(n-2);
            }
        }
    }

    // Blocks L_{p,p}.
    for (uint p = 1; p <= m; ++p)
    {
        uint r0 = p*N + (p-1);
        L(span(r0, r0+N), span(r0, r0+N)).diag().fill(-i2pi*qv(p-1));
    }

    L.save("Lmatrix.dat", arma_ascii);

    return 0;
}
