#include "CauchyInterpolant.hpp"

namespace ModifiedSchwarz
{

template<typename ArmaMatLike>
ArmaMatLike Cauchy::operator()(const ArmaMatLike& z) const
{
    return z;
}

}; // namespace ModifiedSchwarz
