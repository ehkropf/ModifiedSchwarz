# ModifiedSchwarz

A modified Schwarz problem solver in c++.

This is a work in progress and is purposfuly not licensed. It is provided for viewing purposes only.

All work in this repository, unless otherwise specified, is copyright 2016 Everett Kropf.

## Setup

ModifiedSchwarz relies on the following external libraries:

* [Armadillo](http://arma.sourceforge.net) linear algebra template library. Need version 7 or better.

    For best results, Armadillo relies on the following packages:

    * LAPACK, BLAS and ATLAS. On MacOS/OS X these are already supplied under the Accelerate Framework.
    * On Linux systems, OpenBLAS is preferred to BLAS, but not required.
    * [ARPACK](http://www.caam.rice.edu/software/ARPACK/).
    * [SuperLU](http://crd-legacy.lbl.gov/~xiaoye/SuperLU/). Armadillo requires version 5 or better.

* [UnitTest++](https://github.com/unittest-cpp/unittest-cpp) for `make check` unit testing.
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) for `make doc` html doc stuff.

### OS X/macOS

All of the auxilary packages may be installed via [MacPorts](https://www.macports.org). I haven't tried with Homebrew, but this would probably be fine.

### Linux

I have only tested this on Ubuntu 16.04 LTS. Your mileage will vary with other distributions. You MUST check the version of Armadillo and SuperLU that comes with the distribution; both packages were behind in 16.04.
