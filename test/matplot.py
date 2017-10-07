#!/opt/local/bin/python3

# Copyright 2017 Everett Kropf.
#
# This file is part of ModifiedSchwarz.
#
# ModifiedSchwarz is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ModifiedSchwarz is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ModifiedSchwarz.  If not, see <http://www.gnu.org/licenses/>.

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import os
import sys

def readMatrixFromFile(fname):
    """Read matrix in ARMA ASCII format from file.

    Reads complex matrix from fname expecting ARMA ASCII format.
    """

    f = open(fname, 'r')

    line = f.readline()
    if not line.startswith('ARMA_MAT_TXT'):
        raise Exception('Not ARMA_ASCII!')

    line = f.readline()
    rows, cols = line.strip('\n').split(sep=' ')
    rows = int(rows)
    cols = int(cols)
    L = np.zeros((rows, cols), dtype=np.complex64)

    i = 0
    for line in f:
        x = line.strip(' \n').split(' ')
        L[i,:] = [complex(float(a[0]), float(a[1])) for a in [s.strip('()').split(',') for s in x]]
        i += 1

    f.close()

    return L


if __name__ == "__main__":
    # Plot script.

    matname = sys.argv[1]
    L = readMatrixFromFile(matname)

    Lno = np.abs(L) == 0. #< np.spacing(1.)
    La = (np.angle(-L) + np.pi)/(2*np.pi)
    La[Lno] = np.nan

    fig = plt.figure()
    ax = fig.gca()
    ax.imshow(La,
              aspect='equal',
              cmap = 'hsv',
              interpolation='none',
              vmin = 0.,
              vmax = 1.)

    matplotimg = "matplot.png"
    fig.savefig(matplotimg, format="png", bbox_inches="tight")
    os.system("open " + matplotimg)
