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

#pragma once

#include "SchwarzTypes.h"

namespace ModifiedSchwarz
{

//! Define call to Fortran function.
extern "C" void zfmm2dparttarg_(
        int* ier, int* iprec,
        int* nsource, const cx_double* source, const cx_double* dipstr,
        int* ifpot, cx_double* pot,
        int* ifgrad, cx_double* grad,
        int* ifhess, cx_double* hess,
        int* ntarget, const cx_double* target,
        int* ifpottarg, cx_double* pottarg,
        int* ifgradtarg, cx_double* gradtarg,
        int* ifhesstarg, cx_double* hesstarg);

//------------------------------------------------------------------------------
/*!
 *  Settings structure for calling ZFMM2D.
 *
 *  Defaults via the default constructor:
 *    * `iprec == 5`
 *    * `ifpot == false`
 *    * `ifgrad == false`
 *    * `ifhess == false`
 *    * `ifpottarg == true`
 *    * `ifgradtarg == false`
 *    * `ifhesstarg == false`
 */
struct ZFMM2dSet {
    int iprec;
    int ifpot;
    int ifgrad;
    int ifhess;
    int ifpottarg;
    int ifgradtarg;
    int ifhesstarg;

    ZFMM2dSet();
};

//------------------------------------------------------------------------------
/*!
 *  Call Fortran function on construction.
 *
 *  \param source a complex vector of source points.
 *  \param dipstr a complex vector of dipole strengths, same size as `source`.
 *  \param target a complex vector of target points.
 */
struct ZFMM2d {
    //! Behaviour settings.
    ZFMM2dSet set;

    //! Output parameters.
    int ierr;
    cx_vec pot;
    cx_vec grad;
    cx_vec hess;
    cx_vec pottarg;
    cx_vec gradtarg;
    cx_vec hesstarg;

    ZFMM2d(const cx_vec& source, const cx_vec& dipstr, const cx_vec& target, ZFMM2dSet set = ZFMM2dSet());
};

} // namespace ModifiedSchwarz
