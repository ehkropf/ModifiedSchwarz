#include <iostream>

#include "ModifiedSchwarz.hpp"
#include "exampleDomain3.hpp"

namespace MS = ModifiedSchwarz;

int main()
{
    MS::FundamentalDomain domain(ExampleDomain3::centers, ExampleDomain3::radii);

    std::cout << "Exmaple domain has centers\n"
        << domain.getCenters()
        << "\nwith radii\n"
        << domain.getRadii() << std::endl;

    return 0;
}
