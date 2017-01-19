#ifndef COMPLEXINTERP_HPP
#define COMPLEXINTERP_HPP

#include "SchwarzTypes.hpp"
#include "RealInterpolant.hpp"

namespace ModifiedSchwarz
{

class ComplexInterpolant
{
public:
    ComplexInterpolant(const RealInterpolant&, const RealInterpolant&);

    template<typename ArmaMatLike>
    ArmaMatLike operator()(const ArmaMatLike& z) const;
};

}; // namespace ModifiedSchwarz

#endif // COMPLEXINTERP_HPP
