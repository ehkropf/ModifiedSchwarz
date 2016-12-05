#ifndef SCHWARZTYPES_HPP
#define SCHWARZTYPES_HPP

#include <complex>
#include <armadillo>

namespace ModifiedSchwarz
{

typedef std::complex<double> ComplexDouble;

typedef arma::Mat<ComplexDouble> cmatd;
typedef arma::Col<ComplexDouble> cvecd;
typedef arma::Col<double> vecd;

const ComplexDouble i2pi(0.0, 2.0*arma::datum::pi);

////////////////////////////////////////////////////////////////////////
cvecd polyval(const cvecd& a, const cvecd& x);

}; // namespace ModifiedSchwarz

#endif // SCHWARZTYPES_HPP
