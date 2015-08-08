# boost-autoconf v1.0
This repository is used to test the boost library with the autoconf tools. The configuration is based on the tutorial found on the http://www.randspringer.de/boost/upt.html website.

### Compilation and installation

##### Prerequisite
- To be able to compile, the following tools are necessary:
  * a UNIX like environment (Linux / Cygwin for Windows / ...)
  * the "make" command
  * The boost library must be installed
  
##### Compilation
- For the compilation, run the following commands:
  * `clone "https://github.com/YannKurzo/boost-autoconf.git"`
  * `mkdir boost-autoconf_build`
  * `cd boost-autoconf_build`
  * `../boost-autoconf/configure`
  * `make`
  * `make install`
  * The program can now be used.
- If the configure script fails at finding the boost library, use the following command for the configuration:
  * `../boost-autoconf/configure --with-boost=BOOST_PATH`
  * where `BOOST_PATH` is the path to the boost library

##### Compilation on Windows to be able to launch the program outside Cygwin
- With the default configuration, the executable can only be used on Cygwin. To be able to use it as a normal program on Windows, some options must be passed to the configure script.
- We must use the mingw compiler.
- We must link the libraries as static.
- You can use the following commands:
  * `clone "https://github.com/YannKurzo/boost-autoconf.git"`
  * `mkdir boost-autoconf_build`
  * `cd boost-autoconf_build`
  * `../boost-autoconf/configure CXX=x86_64-w64-mingw32-g++ CXXFLAGS="-static-libgcc -static-libstdc++"`
  * `make`
  * The executable is located in `boost-autoconf_build/src/`
- If the configure script fails at finding the boost library, use the following command for the configuration:
  * `../boost-autoconf/configure --with-boost=BOOST_PATH CXX=x86_64-w64-mingw32-g++ CXXFLAGS="-static-libgcc -static-libstdc++"`
  * where `BOOST_PATH` is the path to the boost library

##### Help
- Help can be found by using:
  * `./configure --help`
- This program uses the autoconf / automake tools for the compilation.


### Copyright
Copyright 2015 Yann Kurzo. All rights reserved.
This project is released under the GNU Public License (see LICENSE file).
