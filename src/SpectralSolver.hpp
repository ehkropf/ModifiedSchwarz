#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "SpectralMatrix.hpp"
#include "Solver.hpp"

namespace ModifiedSchwarz
{

/*!
 * Solves the modified Schwarz problem via the spectral method.
 */
class SpectralSolver : public Solver
{
    SpectralMatrixSPtr _domainData;

public:
    virtual Solver& newCopy() { return *(new SpectralSolver); }

    virtual SolutionUPtr solve(const Problem&);
    virtual SolutionUPtr solve(const Problem&, Solution&);
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
