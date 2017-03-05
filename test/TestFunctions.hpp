#ifndef TESTSHARED_HPP
#define TESTSHARED_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

template<typename ArmaMatLike>
ArmaMatLike polesInHoles(const ArmaMatLike& z, const UnitCircleDomain& D)
{
    ArmaMatLike w(size(z), arma::fill::zeros);
    for (auto & d : D.centers()) w += 1./(z - d);

    return w;
}

}; // namespace ModifiedSchwarz

#endif // TESTSHARED_HPP
