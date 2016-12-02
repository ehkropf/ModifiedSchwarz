#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "SchwarzTypes.hpp"
#include "SpectralData.hpp"
#include "SpectralSolution.hpp"

namespace ModifiedSchwarz
{

/*!
 * Solves the modified Schwarz problem via the spectral method.
 */
class SpectralSolver
{
    SpectralDataSPtr _data;

public:
    SpectralSolver() {}

    SpectralSolution solve(const Problem<SpectralSolver, SpectralSolution>&);
    SpectralSolution solve(
            const Problem<SpectralSolver, SpectralSolution>& problem,
            const SpectralSolution& prevSolution)
    {
        _data = prevSolution.data();
        return solve(problem);
    }
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
