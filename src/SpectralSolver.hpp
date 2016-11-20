#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "SpectralMatrix.hpp"
#include "SpectralSolution.hpp"
#include "SchwarzSolver.hpp"
#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Spectral Schwarz solver.
 */
class SolverSpectral : public SchwarzSolver
{
    SpectralMatrix _domainMatrix;

public:
    SolverSpectral(const SolverSpectral& other) : _domainMatrix(other.getMatrix()) {}
    virtual ~SolverSpectral() {}

    const SpectralMatrix& getMatrix() const { return _domainMatrix; }

    virtual SchwarzSolution solve(const SchwarzProblem& problem)
    { return SpectralSolution(cmatd()); }

    virtual SchwarzSolution solve(const SchwarzProblem& problem,
            SchwarzSolution& previous)
    { return SpectralSolution(cmatd()); }
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
