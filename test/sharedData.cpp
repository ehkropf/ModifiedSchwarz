#include <iostream>

#include "UnitCircleDomain.hpp"
#include "SpectralData.hpp"

int main()
{
    using namespace ModifiedSchwarz;

    SpectralDataSPtr data(new SpectralData(domainExample3()));

    {
        SpectralDataSPtr data2 = data;
        std::cout << "Use count: " << data.use_count() << std::endl;
    }

    std::cout << "Use count: " << data.use_count() << std::endl;

    return 0;
}
