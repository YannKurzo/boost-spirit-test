# boost-spirit-test v1.0
This repository is used to test the Spirit parser tool of the boost library and using the autoconf tools.

### Compilation and installation

##### Prerequisite
- To be able to compile, the following tools are necessary:
  * a UNIX like environment (Linux / Cygwin for Windows / ...)
  * the "make" command
  * The boost library must be installed

##### Compilation
- For the compilation, run the following commands:
  * `clone "https://github.com/YannKurzo/boost-spirit-test.git"`
  * `mkdir boost-spirit-test_build`
  * `cd boost-spirit-test_build`
  * `../boost-spirit-test/configure`
  * `make`
  * `make install`
  * The program can now be used.
- If the configure script fails at finding the boost library, use the following command for the configuration:
  * `../boost-spirit-test/configure --with-boost=BOOST_PATH`
  * where `BOOST_PATH` is the path to the boost library

##### Compilation on Windows to be able to launch the program outside Cygwin
- With the default configuration, the executable can only be used on Cygwin. To be able to use it as a normal program on Windows, some options must be passed to the configure script.
- We must use the mingw compiler.
- We must link the libraries as static.
- You can use the following commands:
  * `clone "https://github.com/YannKurzo/boost-spirit-test.git"`
  * `mkdir boost-spirit-test_build`
  * `cd boost-spirit-test_build`
  * `../boost-spirit-test/configure CXX=x86_64-w64-mingw32-g++ CXXFLAGS="-static-libgcc -static-libstdc++"`
  * `make`
  * The executable is located in `boost-spirit-test_build/src/`
- If the configure script fails at finding the boost library, use the following command for the configuration:
  * `../boost-spirit-test/configure --with-boost=BOOST_PATH CXX=x86_64-w64-mingw32-g++ CXXFLAGS="-static-libgcc -static-libstdc++"`
  * where `BOOST_PATH` is the path to the boost library

##### Help
- Help can be found by using:
  * `./configure --help`
- This program uses the autoconf / automake tools for the compilation.


### Copyright
Copyright 2015 Yann Kurzo. All rights reserved.
This project is released under the GNU Public License (see LICENSE file).
