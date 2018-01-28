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
#include "SpectralMethod.h"
#include "SpectralData.h"

using namespace ModifiedSchwarz;
using namespace arma;

TEST(SpectralMethodLabel)
{
    TEST_FILE("Spectral method check");
}

SUITE(SpectralMethodTest)
{

    class TestFixture
    {
        public:
            UnitCircleDomain domain;
            RealBoundaryValues imaginary_part;
            RealBoundaryValues boundary_values;
            ComplexBoundaryValues::Function test_function;

            static constexpr unsigned npts = 200;

            TestFixture()
                : domain(domainExample3())//,
            {
                const UnitCircleDomain& D = domain;
                test_function = [&D](const cx_vec& z){ return polesInHoles(z, D); };
                imaginary_part = RealBoundaryValues(BoundaryPoints(domain, npts),
                        [this](const cx_vec& z){ return imag(test_function(z)); });
            }
    };

    TEST_FIXTURE(TestFixture, TestRHS)
    {
        TEST_LINE("Right hand side");

        SpectralConstants::setTruncation(64);
        SpectralMethod method(Problem(domain, imaginary_part));
        cx_vec rhs = method.computeRHS(100);

        cx_vec refRHS;
        CHECK(refRHS.load("../test/refRHS.dat"));

        CHECK(approx_equal(rhs.head_rows(rhs.n_rows/2), refRHS, "absdiff", 1e-4));

        TEST_DONE;
    }

    TEST_FIXTURE(TestFixture, TestResidual)
    {
        TEST_LINE("Residual");

        SpectralMethod method(Problem(domain, imaginary_part));

        cx_vec rhs = method.computeRHS();
        const cx_mat& A = method.matrix();
        cx_vec x = solve(A, rhs);

        cx_vec res = rhs - A*x;
        CHECK(max(abs(res)/abs(rhs)) < 100*eps2pi);

        TEST_DONE;
    }

    TEST_FIXTURE(TestFixture, TestSolution)
    {
        TEST_LINE("Solution");

        SpectralMethod method(Problem(domain, imaginary_part));
        Solution sol = method.solve();

        SpectralData& data = *std::dynamic_pointer_cast<SpectralData>(sol.solverDataPtr());
        CHECK(data.domain() == domain);

        cx_vec bv(vectorise(domain.boundaryPoints(10)));
        CHECK(approx_equal(polesInHoles(cx_vec(vectorise(bv)), domain), sol(vectorise(bv)), "absdiff", 1e-6));

        TEST_DONE;
    }

}
