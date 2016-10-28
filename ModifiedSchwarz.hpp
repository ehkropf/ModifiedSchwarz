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

class FundamentalDomain
{
    cvecd _centers;
    vecd _radii;

    public:
        FundamentalDomain(const cvecd &centers, const vecd &radii)
            : _centers(centers), _radii(radii) {}

        const cvecd &getCenters() const { return _centers; }
        const vecd &getRadii() const { return _radii; }

        unsigned connectivity() const { return unsigned(_centers.n_elem) + 1; }
        unsigned m() const { return unsigned(_centers.n_elem); }
};

};

#endif // MODIFIED_SCHWARZ_HPP
