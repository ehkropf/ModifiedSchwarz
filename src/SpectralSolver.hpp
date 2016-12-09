#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "SchwarzTypes.hpp"
#include "SpectralData.hpp"
#include "SpectralSolution.hpp"
#include "Problem.hpp"

namespace ModifiedSchwarz
{

////////////////////////////////////////////////////////////////////////

//! Forward declare for typedef.
class SpectralSolver;

//! Spectral problem typedef.
using SpectralProblem = Problem<SpectralSolver, SpectralSolution>;

////////////////////////////////////////////////////////////////////////
/*!
 * Solves the modified Schwarz problem via the spectral method.
 * Call solve() with a previous solution to reuse the SpectralData
 * created for the last solver run. Saves reconstructing the spectral
 * matrix which is unique per domain+truncation.
 */
class SpectralSolver
{
    SpectralDataSPtr _data;

public:
    SpectralSolver() {}

    SpectralSolution solve(const SpectralProblem&);
    SpectralSolution solve(const SpectralProblem& problem, const SpectralSolution& prevSolution)
    {
        _data = prevSolution.data();
        return solve(problem);
    }

    static SpectralProblem problem(UnitCircleDomain domain, cx_mat boundaryData)
    {
        return SpectralProblem(domain, boundaryData, SpectralSolver());
    }
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
