#ifndef CAUCHY_HPP
#define CAUCHY_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

class ComplexInterpolant;

class Cauchy
{
    UnitCircleDomain _domain;

public:
    Cauchy(const ComplexInterpolant&, const UnitCircleDomain&, unsigned N = 128);

    template<typename ArmaMatLike>
    ArmaMatLike operator()(const ArmaMatLike& z) const;
};

}; // namespace ModifiedSchwarz

#endif // CAUCHY_HPP
