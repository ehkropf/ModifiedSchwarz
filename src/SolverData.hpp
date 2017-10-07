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

#ifndef SOLVERDATA_HPP
#define SOLVERDATA_HPP

#include <memory>

namespace ModifiedSchwarz
{

// FIXME: There should be a member to store the solver methed used. 
//        In this way, a solver instance can check for compatible previous
//        solution data.

///////////////////////////////////////////////////////////////////////////
/*!
 * Abstract class to store data specific to a solver method.
 */
class SolverData
{
public:
    virtual ~SolverData() = default;

    using Ptr = std::shared_ptr<SolverData>;
    using ConstPtr = std::shared_ptr<const SolverData>;
};

}; // namespace ModifiedSchwarz

#endif // SOLVERDATA_HPP
