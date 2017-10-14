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

namespace ModifiedSchwarz
{

template <typename Matrix>
class FunctionLike
{
public:
    virtual ~FunctionLike() = default;

    //! Provides function-like evaulation.
    inline virtual Matrix operator()(const Matrix&) const;

    //! Called by operator(). Calls evalInto(.,.).
    virtual Matrix eval(const Matrix&) const;

    //! Must override to allow evaluation into a given target matrix.
    virtual void evalInto(const Matrix&, Matrix&) const = 0;
};

//////////////////////////////////////////////////////////////////////////////////
template <typename Matrix>
Matrix FunctionLike<Matrix>::operator()(const Matrix& z) const
{
    return eval(z);
}

//////////////////////////////////////////////////////////////////////////////////
template <typename Matrix>
Matrix FunctionLike<Matrix>::eval(const Matrix& z) const
{
    Matrix w(size(z));
    evalInto(z, w);
}

}; //namespace ModifiedSchwarz

#endif // FUNCLIKE_HPP
