#ifndef SPECTRALSOLVER_HPP
#define SPECTRALSOLVER_HPP

#include "Solver.hpp"

//#include "SpectralMatrix.hpp"
//#include "SpectralSolution.hpp"
//#include "SchwarzSolver.hpp"
//#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

/*!
 * Solves the modified Schwarz problem via the spectral method.
 */
class SpectralSolver : public Solver
{
    // Spectral domain matrix pointer goes here.

public:
    virtual Solver& newCopy() { return *(new SpectralSolver); }

    virtual SolutionUPtr solve(const Problem&);
    virtual SolutionUPtr solve(const Problem&, Solution&);
};

}; // namespace ModifiedSchwarz

#endif // SPECTRALSOLVER_HPP
