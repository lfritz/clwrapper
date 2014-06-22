# clwrapper
This library contains a set of wrapper classes for the OpenCL API intended for programs written in C++ and using Qt. It's a thin wrapper, with most classes corresponding directly to OpenCL types and their member functions corresponding to OpenCL functions.

The source code is organized in three directories:
 * `cl`: the library itself,
 * `info`: a small command-line program that uses the library to print information on the OpenCL devices available, and
 * `test`: unit tests for the library.

## Requirements
The library itself depends on:
 * a C++ compiler that supports rvalue references (Visual Studio 2010 should work, or a recent version of clang or gcc),
 * Qt (http://qt-project.org/), and
 * GLM (http://glm.g-truc.net/).

The unit tests additionally need the googletest library (https://code.google.com/p/googletest/).

The location of GLM and googletest are hard-coded in the .pro files, so you may have to change those.

## License
The files `clew.h` and `clew.cpp` are open source under the terms of the Boost Software License, version 1.0 (see accompanying file LICENSE-CLEW). All other source code is copyright (c) 2014 Brain Innovation B.V., Maastricht, The Netherlands and is open source under the terms of the MIT license (see accompanying file LICENSE).
