#ifndef MODIFIED_SCHWARZ_HPP
#define MODIFIED_SCHWARZ_HPP

#include <complex>
#include <armadillo>

namespace ModifiedSchwarz
{

typedef std::complex<double> complexd;

typedef arma::Col<complexd> cvecd;
typedef arma::Col<double> vecd;

class FundamentalDomain
{
    cvecd _centers;
    vecd _radii;

    public:
        FundamentalDomain(const cvecd &centers, const vecd &radii)
            : _centers(centers), _radii(radii) {}

        const cvecd &getCenters() const { return _centers; }
        const vecd &getRadii() const { return _radii; }
};

};

#endif // MODIFIED_SCHWARZ_HPP
