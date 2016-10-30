#ifndef EXAMPLE_DOMAIN_3_HPP
#define EXAMPLE_DOMAIN_3_HPP

#include "ModifiedSchwarz.hpp"

// D = circleRegion(...
//            circle(0, 1), ...
//            circle(-0.2517+0.3129i, 0.2377), ...
//            circle(0.2307-0.4667i, 0.1557));

namespace ExampleDomain3
{

using namespace ModifiedSchwarz;

cvecd centers{ complexd(0.0, 0.0), complexd(-0.2517, 0.3129), complexd(0.2307, -0.4667) };
vecd radii{ 1.0, 0.2377, 0.1557 };

// UnitCircleDomain exampleDomain = UnitCircleDomain(centers, radii);

};

#endif // EXAMPLE_DOMAIN_3_HPP
