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

#ifndef TESTSHARED_HPP
#define TESTSHARED_HPP

#include "SchwarzTypes.h"
#include "UnitCircleDomain.h"

namespace ModifiedSchwarz
{

template<typename ArmaMatLike>
ArmaMatLike polesInHoles(const ArmaMatLike& z, const UnitCircleDomain& D)
{
    ArmaMatLike w(size(z), arma::fill::zeros);
    for (auto & d : D.centers()) w += 1./(z - d);

    return w;
}

}; // namespace ModifiedSchwarz

#endif // TESTSHARED_HPP
