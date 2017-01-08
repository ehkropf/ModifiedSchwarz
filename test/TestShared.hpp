#ifndef TESTSHARED_HPP
#define TESTSHARED_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

template<typename MatrixType>
MatrixType polesInHoles(const MatrixType& z, const UnitCircleDomain& D)
{
    MatrixType w(size(z), arma::fill::zeros);
    for (auto & d : D.centers()) w += 1./(z - d);

    return w;
}

}; // namespace ModifiedSchwarz

#endif // TESTSHARED_HPP
