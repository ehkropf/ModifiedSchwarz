#!/opt/local/bin/python

from __future__ import print_function
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import os
import sys

if __name__ == "__main__":
    # Plot script.

    matname = sys.argv[1]
    f = open(matname, 'r')

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

    LL = np.abs(L)
    LL[LL == 0] = np.nan

    fig = plt.figure()
    ax = fig.gca()
    ax.imshow(LL, aspect='equal')

    matplotpdf = "matplot.pdf"
    fig.savefig(matplotpdf, format="pdf", bbox_inches="tight")
    os.system("open " + matplotpdf)
