# ModifiedSchwarz

A modified Schwarz problem solver in C++.

## License

All work in this repository, unless otherwise specified, is Copyright 2017 Everett Kropf.

This file is part of ModifiedSchwarz.

ModifiedSchwarz is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ModifiedSchwarz is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ModifiedSchwarz.  If not, see <http://www.gnu.org/licenses/>.

## Setup

ModifiedSchwarz relies on the following external libraries:

* [cmake](https://cmake.org) build system. At least version 3.5.

* [Armadillo](http://arma.sourceforge.net) linear algebra template library. Need version 7 or better.

    For best results, Armadillo relies on the following packages:

    * LAPACK, BLAS and ATLAS. On macOS/OS X these are already supplied under the Accelerate Framework.
    * On Linux systems, OpenBLAS is preferred to BLAS, but not required.
    * [ARPACK](http://www.caam.rice.edu/software/ARPACK/).
    * [SuperLU](http://crd-legacy.lbl.gov/~xiaoye/SuperLU/). Armadillo requires version 5 or better.

* [UnitTest++](https://github.com/unittest-cpp/unittest-cpp) (optional) for `make check` unit testing.
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) (optional) for `make doc` html doc stuff.

Once the auxiliary packages are installed (see below for OS specific notes), this repository is cloned, and you are in the repository base directory (probably `<something>/ModifiedSchwarz`), the following sequence of commands should build the library. (See the Linux section below if you have installed Armadillo manually.)

```bash
mkdir build
cd build
cmake ..
make
```

(Yes, the two dots are required following `cmake`.) Note there is no valid install target currently. (It hasn't been configured.)

If you've installed UnitTest++, tests can be run with `make check`. If you've installed Doxygen, you can make the HTML docs via `make doc`.

### OS X/macOS

All of the auxilary packages may be installed via [MacPorts](https://www.macports.org). I haven't tried with Homebrew, but this would probably be fine.

### Linux

I have only tested this on Ubuntu 16.04 LTS. Your mileage will vary with other distributions. The basic stuff (cmake, LAPACK, BLAS, etc.) can be installed via the normal `apt install` route. Note you MUST check the version of Armadillo and SuperLU that comes with the distribution; both packages were behind in 16.04.

As an example involving out-of-band packages, I'll show installing SuperLU and Armadillo, since it's what needed done on 16.04.

#### SuperLU

By default SuperLU builds as a static library; we'll build it as shared. In addition it tries to use supplied BLAS routines; we'll give the option to use the system libraries. Finally I'll show how to use an alternate install location.<super>*</super> So once the package is downloaded and unzipped, and you are in the directory, the following commands will build and install the package:

```bash
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON -Denable_blaslib=OFF -DCMAKE_INSTALL_PREFIX=/opt/local ..
make
make test
sudo make install
```

<sub>\* I like to install non package managed software to `/opt/local`, making it easier to track.</sub>

#### Armadillo

As before, once the package is downloaded, unzipped, and you are in the directory, give the following commands:

```bash
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/opt/local -DCMAKE_INSTALL_PREFIX=/opt/local ..
make
sudo make install
```

Note that when you configure ModifiedSchwarz, you will need to modify the `cmake` command to be

```bash
cmake -DCMAKE_PREFIX_PATH=/opt/local ..
```
