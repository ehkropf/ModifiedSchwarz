#!/opt/local/bin/python

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import os
import sys

def readMatrixFromFile(fname):
    '''
    Read matrix from file fname.
    '''

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

    Lno = np.abs(L) < np.spacing(1.)
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
