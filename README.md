About [![Build Status](https://travis-ci.org/rettichschnidi/clang-misracpp2008.svg?branch=master)](https://travis-ci.org/rettichschnidi/clang-misracpp2008)
=====

clang-misracpp2008 is a project which tries to create an open source checker for
the MISRA C++:2008 rules using the LLVM/Clang infrastructure.

Some rules can easily be checked by enabling compiler-provided warnings. For
those rules we simply name those switches. Other rules require custom logic and
are therefore realized as plugin.

Progress
========
Have a look at the [progress page in the wiki](https://github.com/rettichschnidi/clang-misracpp2008/wiki/Progress).

Installation
============
It is assumed that you have already have compiled LLVM/Clang from SVN. To add
clang-misracpp2008, the following steps are required:

    cd ~/${LLVM_CHECKOUT_FOLDER}/tools/clang/tools
    git clone https://github.com/rettichschnidi/clang-misracpp2008.git
    echo 'add_subdirectory(clang-misracpp2008)' >>  CMakeLists.txt

The next time you build LLVM/Clang, clang-misracpp2008 gets picked up and built.

Please note that only the CMake build system is supported.

Running tests
=============
`make check-misracpp2008`

Building documentation
======================
`make doxygen-misracpp2008`

Usage
=====
The OffendingProject included in the examples directory can be built this way:

    export LLVM_BUILD_DIR=~/build_llvm # Adjust to your situation
    cd ~/${LLVM_CHECKOUT_FOLDER}/tools/clang/tools
    cd clang-misracpp2008/examples/OffendingProject
    mkdir -p build && cd build
    cmake -DCMAKE_CXX_FLAGS="-Xclang -load -Xclang \
             ${LLVM_BUILD_DIR}/lib/misracpp2008.so -Xclang -add-plugin -Xclang \
             misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang all" \
           -DCMAKE_CXX_COMPILER="${LLVM_BUILD_DIR}/bin/clang++" \
           -DCMAKE_C_COMPILER="${LLVM_BUILD_DIR}/bin/clang" ../
    make

You will get some MISRA C++:2008 violations reported.
