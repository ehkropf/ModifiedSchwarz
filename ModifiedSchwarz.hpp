#ifndef MODIFIED_SCHWARZ_HPP
#define MODIFIED_SCHWARZ_HPP

#include <complex>
#include <cmath>
#include <armadillo>

namespace ModifiedSchwarz
{

typedef std::complex<double> complexd;

typedef arma::Mat<complexd> cmatd;
typedef arma::Col<complexd> cvecd;
typedef arma::Col<double> vecd;

const complexd i2pi(0.0, 2.0*arma::datum::pi);

class UnitCircleDomain
{
    cvecd _centers;
    vecd _radii;

    public:
        UnitCircleDomain(const cvecd &centers, const vecd &radii)
            : _centers(centers), _radii(radii) {}

        const cvecd &getCenters() const { return _centers; }
        const vecd &getRadii() const { return _radii; }

        unsigned connectivity() const { return unsigned(_centers.n_elem) + 1; }
        unsigned m() const { return unsigned(_centers.n_elem); }
};

/*
 * Example domain defined in matlab code (it's cannon at this point):
 *
 *   D = circleRegion(...
 *              circle(0, 1), ...
 *              circle(-0.2517+0.3129i, 0.2377), ...
 *              circle(0.2307-0.4667i, 0.1557));
 *
 */
UnitCircleDomain domainExample3()
{
    cvecd centers{ complexd(-0.2517, 0.3129), complexd(0.2307, -0.4667) };
    vecd radii{ 0.2377, 0.1557 };

    return UnitCircleDomain(centers, radii);
}

}; // namespace ModifiedSchwarz

#endif // MODIFIED_SCHWARZ_HPP
