/*
 * Copyright 2017 Everett Kropf.
 *
 * This file is part of ModifiedSchwarz.
 *
 * ModifiedSchwarz is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ModifiedSchwarz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ModifiedSchwarz.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "UnitTest.h"
#include "TestFunctions.hpp"

#include "SchwarzTypes.h"
#include "BoundaryValues.hpp"
#include "RealInterpolant.h"
#include "ComplexInterpolant.h"

using namespace ModifiedSchwarz;

////////////////////////////////////////////////////////////////////////////////
// It's assumed that c.n_elem is even.
void coeffOut(const cx_vec& c)
{
    unsigned N = c.n_elem;

    std::cout << "Coeff (1,5) and (-1,-5):\n"
            << arma::join_horiz(c.rows(1, 5), flipud(c.rows(N-5, N-1)))
            <<"... (" << N/2-5 << ", " << N/2-1 << ") and ("
            << -int(N/2-5) << ", " << -int(N/2-1) << "): \n"
            << arma::join_horiz(c.rows(N/2-5, N/2-1), arma::flipud(c.rows(N/2+1, N/2+5)));
}

////////////////////////////////////////////////////////////////////////////////
SUITE(FFTSuite)
{

TEST(FFTLabel)
{
    TEST_FILE("FFT");
}

struct Fixture
{
    using Function = std::function<mat(cx_mat&)>;

    static constexpr unsigned N = 256;

    UnitCircleDomain domain;
    BoundaryPoints eval_points;
    ComplexBoundaryValues::Function g;
    RealBoundaryValues::Function h;

    Fixture()
        : domain(domainExample3()),
          eval_points(BoundaryPoints(domain, N))
    {
        g = [this](const cx_mat& z) { return polesInHoles(z, domain); };
        h = [this](const cx_mat& z) { return real(polesInHoles(z, domain)); };
    }
};

TEST_FIXTURE(Fixture, FFT)
{
    TEST_LINE("FFT interp");

    

    SDEBUG("Output results.");
    coeffOut(c);
}

} // SUITE
