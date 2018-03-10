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

#include "ZFMM_Wrapper.h"

namespace ModifiedSchwarz
{

//------------------------------------------------------------------------------
ZFMM2dSet::ZFMM2dSet()
    : iprec(5),
      ifpot(false),
      ifgrad(false),
      ifhess(false),
      ifpottarg(true),
      ifgradtarg(false),
      ifhesstarg(false)
{}

//------------------------------------------------------------------------------
ZFMM2d::ZFMM2d(const cx_vec& source, const cx_vec& dipstr, const cx_vec& target, ZFMM2dSet set)
        : set(set)
{
    int nsource = source.n_elem;
    int ntarget = target.n_elem;

    if (set.ifpot) pot.zeros(nsource);
    if (set.ifgrad) grad.zeros(nsource);
    if (set.ifhess) hess.zeros(nsource);
    if (set.ifpottarg) pottarg.zeros(ntarget);
    if (set.ifgradtarg) gradtarg.zeros(ntarget);
    if (set.ifhesstarg) hesstarg.zeros(ntarget);

    zfmm2dparttarg_(
            &ierr, &set.iprec,
            &nsource, source.memptr(), dipstr.memptr(),
            &set.ifpot, pot.memptr(),
            &set.ifgrad, grad.memptr(),
            &set.ifhess, hess.memptr(),
            &ntarget, target.memptr(),
            &set.ifpottarg, pottarg.memptr(),
            &set.ifgradtarg, gradtarg.memptr(),
            &set.ifhesstarg, hesstarg.memptr()
            );
}

}; // namespace ModifiedSchwarz
