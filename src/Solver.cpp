#include "Solver.hpp"
#include "SpectralMethod.hpp"

#include <cassert>

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////////////
Solver::Solver()
    : method(Method::Spectral) {}

Solver::Solver(Method method)
    : method(method) {}

////////////////////////////////////////////////////////////////////////////////
Solution Solver::solve(const Problem& p)
{
    switch(method)
    {
        case Spectral:
            return SpectralMethod(p).solve();
            break;

        default:
            // NEVER should be here. Means enum was added without method implementation.
            assert(false);
    }
}

Solution Solver::solve(const Problem& p, const Solution& prev)
{
    switch(method)
    {
        case Spectral:
            return SpectralMethod(p, prev).solve();
            break;

        default:
            // NEVER should be here. Means enum was added without method implementation.
            assert(false);
    }
}

}; // ModifiedSchwarz
