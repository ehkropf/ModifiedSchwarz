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

#include "SchwarzTypes.hpp"

namespace ModifiedSchwarz
{

template <typename Amatrix, typename Bmatrix = Amatrix>
class FunctionLike
{
public:
    virtual ~FunctionLike() = default;

    //! Provides function-like evaulation. Wrapper for eval()
    inline virtual Bmatrix operator()(const Amatrix&) const;

    //! Wrapper for evalInto(). Initializes target matrix with NaN values.
    inline virtual Bmatrix eval(const Amatrix&) const;

    //! Must override to define evaluation into a given target matrix.
    virtual void evalInto(const Amatrix&, Bmatrix&) const = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// Basic template. Do we need specialization?
//
template <typename Amatrix, typename Bmatrix>
Bmatrix FunctionLike<Amatrix, Bmatrix>::operator()(const Amatrix& z) const
{
    return eval(z);
}

template <typename Amatrix, typename Bmatrix>
Bmatrix FunctionLike<Amatrix, Bmatrix>::eval(const Amatrix& z) const
{
    Bmatrix w(size(z));
    w.fill(nan);
    evalInto(z, w);

    return w;
}

}; //namespace ModifiedSchwarz

#endif // FUNCLIKE_HPP
