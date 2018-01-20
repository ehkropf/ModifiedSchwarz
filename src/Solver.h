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

#ifndef SOLVER_H
#define SOLVER_H

#include "SchwarzTypes.h"

namespace ModifiedSchwarz
{

class Problem;
class Solution;

///////////////////////////////////////////////////////////////////////////
/*!
 * Exists to dispatch Problem and (possibly) previous Solution data
 * to the proper solver method.
 *
 * Some solver methods may be accelerated by using previously computed
 * data, and this is passed around via a shared pointer stored in each
 * solution as appropriate.
 */
struct Solver
{
    enum Method { Spectral };
    Method method;

    Solver();
    Solver(Method method);

    Solution solve(const Problem&);
    Solution solve(const Problem&, const Solution&);
};

}; // namespace ModifiedSchwarz

#endif // SOLVER_H
