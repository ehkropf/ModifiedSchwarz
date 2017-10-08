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

#ifndef CAUCHY_HPP
#define CAUCHY_HPP

#include "SchwarzTypes.hpp"
#include "UnitCircleDomain.hpp"

namespace ModifiedSchwarz
{

class ComplexInterpolant;

class Cauchy
{
    UnitCircleDomain _domain;

public:
    Cauchy(const ComplexInterpolant&, const UnitCircleDomain&, unsigned N = 128);

    template<typename ArmaMatLike>
    ArmaMatLike operator()(const ArmaMatLike&) const;
};

}; // namespace ModifiedSchwarz

#endif // CAUCHY_HPP
