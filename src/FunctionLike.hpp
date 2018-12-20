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

#ifndef FUNCLIKE_HPP
#define FUNCLIKE_HPP

#include "SchwarzTypes.h"

namespace ModifiedSchwarz
{

//! Abstract base class to provide function like behaviour.
/*!
 * Derived classes only need to define the abstract funcDefinition() member
 * function to provide behaviour such that given Amatrix type and
 * Bmatrix type a derived class instance f provides
 *     Bmatrix w = f(const Amatrix& z)
 * behaviour.
 */
template <typename Amatrix, typename Bmatrix = Amatrix>
class FunctionLike
{
public:
    //! Virtual destructor required for abstract class.
    virtual ~FunctionLike() = default;

    //! Provides function-like evaulation.
    /*!  Initializes a target Bmatrix with NaN values, and then calls
     *   funcDefinition to evaluate the funciton.
     *   TODO: Add warning if w.has_nan()?
     */
    virtual Bmatrix operator()(const Amatrix&) const;

    //! Provides function definition for `operator()`.
    /*! Amatrix is the function input, and function output is to be
     *  stored in Bmatrix. All subclasses must override this.
     */
    virtual void funcDefinition(const Amatrix&, Bmatrix&) const = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// Basic template. Do we need specialization?
//
template <typename Amatrix, typename Bmatrix>
Bmatrix FunctionLike<Amatrix, Bmatrix>::operator()(const Amatrix& z) const
{
    Bmatrix w(size(z));
    w.fill(nan);
    funcDefinition(z, w);

    return w; //eval(z);
}

} //namespace ModifiedSchwarz

#endif // FUNCLIKE_HPP
