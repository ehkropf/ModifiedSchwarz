#include "UnitCircleDomain.hpp"
#include "SpectralMatrix.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////
UnitCircleDomain domainExample3()
{
    cvecd centers{ ComplexDouble(-0.2517, 0.3129), ComplexDouble(0.2307, -0.4667) };
    vecd radii{ 0.2377, 0.1557 };

    return UnitCircleDomain(centers, radii);
}

////////////////////////////////////////////////////////////////////////
void
SpectralMatrix::constructMatrix(const uint truncation)
{
    using namespace arma;

    uint m = _domain.m();
    cvecd dv = _domain.getCenters();
    vecd qv = _domain.getRadii();

    // Series truncation level.
    uint N = truncation;
    vecd ktmp = -regspace(1., double(N+1));

    // Number of unknowns.
    uint Q = m*(N + 1) + N; // N = (Q - m)/(m + 1);

    // The matrix.
    _domainMatrix = cmatd(2*Q, 2*Q, fill::zeros);
    cmatd& L = _domainMatrix;

    // Double loop construction.
    for (uint p = 0; p <= m; ++p)
    {
        uint r0 = (p > 0) ? p*N + (p-1) : 0;
        ComplexDouble dp = (p > 0) ? dv(p-1) : 0.;
        double qp = (p > 0) ? qv(p-1) : 1.;

        for (uint j = 0; j <= m; ++j)
        {
            uint c0 = (j > 0) ? j*N + (j-1) : 0;
            ComplexDouble dj = (j > 0) ? dv(j-1) : 0.;
            double qj = (j > 0) ? qv(j-1) : 1.;

            if (j == 0)
            {
                if (p == 0)
                {
                    // Block L_{0,0}.
                    L(span(0, N-1), span(Q, Q+N-1)).diag().fill(i2pi);
                }
                else
                {
                    // Block L_{p,0}.
                    if (dp == 0.)
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
            }
            else
            {
                if (p == 0)
                {
                    // Block L_{0,j}.
                    if (dj == 0.)
                    {
                        cvecd tmp(N);
                        tmp(0) = -i2pi*qj;
                        for (uint i = 1; i < N; ++i)
                        {
                            tmp(i) = qj*tmp(i-1);
                        }
                        L(span(0, N-1), span(Q+c0+1, Q+c0+N)).diag() = tmp;
                    }
                    else
                    {
                        cvecd tmp(N);
                        tmp(0) = -i2pi*qj;
                        for (uint i = 1; i < N; ++i)
                        {
                            tmp(i) = dj*tmp(i-1);
                        }
                        L(span(0, N-1), Q+c0+1) = tmp;

                        for (uint n = 3; n <= N+1; ++n)
                        {
                            L(span(n-2, N-1), Q+c0+n-1)
                                = qj*L(span(n-3, N-2), Q+c0+n-2)
                                    %regspace(double(n-2), double(N-1))/double(n-2);
                        }
                    }
                }
                else if(p == j)
                {
                    // Block L_{p,p}.
                    uint r0 = p*N + (p-1);
                    L(span(r0, r0+N), span(r0, r0+N)).diag().fill(-i2pi*qv(p-1));
                }
                else
                {
                    // Block L_{p,j}.
                    cvecd qtmp(N+1);
                    qtmp(0) = qp;
                    cvecd dtmp(N+1);
                    ComplexDouble djp = dj - dp;
                    dtmp(0) = 1./djp;
                    for (uint i = 1; i < N+1; ++i)
                    {
                        qtmp(i) = qp*qtmp(i-1);
                        dtmp(i) = dtmp(i-1)/djp;
                    }
                    L(span(r0, r0+N), Q+c0+1) = -i2pi*qj*qtmp%dtmp;

                    for (uint n = 3; n <= N+1; ++n)
                    {
                        L(span(r0, r0+N), Q+c0+n-1)
                            = (qj/djp)*L(span(r0, r0+N), Q+c0+n-2)%(ktmp - double(n-3))/(n-2);
                    }
                }
            }
        }
    }

    L(span(Q, 2*Q-1), span(0, Q-1)) = conj(L(span(0, Q-1), span(Q, 2*Q-1)));
    L(span(Q, 2*Q-1), span(Q, 2*Q-1)) = conj(L(span(0, Q-1), span(0, Q-1)));
}

}; // namespace ModifiedSchwarz
