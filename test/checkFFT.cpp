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
template <typename ArmaCxMat>
ArmaCxMat testFun(const ArmaCxMat& zv)
{
    const arma::cx_vec dv{
        arma::cx_double(-0.2517, 0.3129), arma::cx_double(0.2307, -0.4667) };
    ArmaCxMat wv = zv; // wv(zv.size(), arma::fill::zeros);
    for (const auto& d : dv) wv += 1/(zv - d);

    return wv;
}

////////////////////////////////////////////////////////////////////////////////
/*!
 *  Trig interpolant. Pass in FFT array; constant and coefficients will
 *  be extracted. Points to evaluate should of course be on the unit circle.
 *  WARNING: Asumes size of FFT array is even!!!
 */
arma::cx_vec trigInterp(const arma::cx_vec& c, const arma::cx_vec& z)
{
    const unsigned N = c.n_elem;

    const arma::cx_vec& pos_coeff(arma::flipud(c.rows(0, N/2)));
    arma::cx_vec pos_part(polyval(pos_coeff, z));

    const arma::cx_vec& neg_coeff(arma::join_vert(c.rows(N/2+1, N-1), arma::cx_vec{ 0. }));
    arma::cx_vec neg_part(polyval(neg_coeff, arma::cx_vec(1/z)));

    return pos_part + neg_part;
}

/*!
 *  Real-valued trig interpolant. Relies on c_k = conj(c_(-k)), and assumes
 *  FFT vector is full and even numbered.
 */
arma::colvec realTrigInterp(const arma::cx_vec& c, const arma::cx_vec& z)
{
    const unsigned N = c.n_elem;

    const arma::cx_vec& coeff(arma::join_vert(arma::flipud(c.rows(1, N/2-1)),
                arma::cx_vec{ 0. }));
    return c(0).real() + 2.*arma::real(polyval(coeff, z));
}

////////////////////////////////////////////////////////////////////////////////
// It's assumed that c.n_elem is even.

// TODO: This is pretty bloody clunky.
#ifdef DEBUG
void coeffOut(const cx_vec& c)
{
    const unsigned N = c.n_elem;

    SDEBUG("Coeff (1,5) and (-1,-5):\n"
            << arma::join_horiz(c.rows(1, 5), flipud(c.rows(N-5, N-1)))
            << "... (" << N/2-5 << ", " << N/2-1 << ") and ("
            << -int(N/2-5) << ", " << -int(N/2-1) << "): \n"
            << arma::join_horiz(c.rows(N/2-5, N/2-1), arma::flipud(c.rows(N/2+1, N/2+5)))
          );
}
#else
void coeffOut(const cx_vec&) {}
#endif

////////////////////////////////////////////////////////////////////////////////
SUITE(FFTSuite)
{

TEST(FFTLabel)
{
    TEST_FILE("FFT");
}

struct Fixture
{
    static constexpr unsigned N = 256;

    UnitCircleDomain domain;
    BoundaryPoints eval_points;

    Fixture()
        : domain(domainExample3()),
          eval_points(BoundaryPoints(domain, N))
    {}
};

TEST_FIXTURE(Fixture, FFT)
{
    TEST_LINE("FFT interp");

    // From the unit circle, take the N-point DFT of a given function.
    unsigned N = 128;
    arma::cx_vec unit_pts(arma::exp((arma::regspace(0, N-1)/N)*i2pi));
    arma::cx_vec w_pts(testFun(unit_pts));
    arma::cx_vec c(arma::fft(w_pts)/N);

    SDEBUG("Constant (complex): " << c(0));
    SDEBUG("Nyquist: " << c(N/2));
    coeffOut(c);

    // Take an odd/prime number of sample check points on the circle.
    unsigned Np = 13;
    arma::cx_vec sample_pts(arma::exp((arma::regspace(0, Np-1)/Np)*i2pi));
    arma::cx_vec sample_vals(testFun(sample_pts));

    // Use the trig interpolant to check values there.
    SDEBUG("Check values in trig interpolant:\n"
            << arma::abs(sample_vals - trigInterp(c, sample_pts)));
    CHECK(arma::approx_equal(sample_vals, trigInterp(c, sample_pts), "absdiff", 10.*eps2pi));

    // Use the real part of the function only and take the 128-point DFT.
    arma::cx_vec rc(arma::fft(arma::real(w_pts))/N);

    // For DFT of real function, suppose N is even.
    // Then first coeff is real.
    // The remaining N-1 is odd, so we have Nyquist component at N/2.
    //
    // Arranging the coefficients (c_k) so we have negative indices, that is
    //     k in {N-(N/2-1),...,N-1} ~ k in {-(N/2-1),...,-1}
    // where c_0 is constant and c_(N/2) is nyquist component. We have the relation
    //     c_(k) = conj(c_(-k))
    // where conj() is the complex conjugate.
    SDEBUG("Constant (real): " << rc(0));
    SDEBUG("Nyquist: " << rc(N/2));
    coeffOut(rc);

    // Does the trig interpolant return good values at the check points?
    SDEBUG("Value diff in real interpolant:\n"
            << arma::abs(arma::real(sample_vals) - realTrigInterp(rc, sample_pts)));
    CHECK(arma::approx_equal(arma::real(sample_vals), realTrigInterp(rc, sample_pts), "absdiff", 10.*eps2pi));

    TEST_DONE;
}

} // SUITE
