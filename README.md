About [![Build Status](https://travis-ci.org/rettichschnidi/clang-misracpp2008.svg?branch=master)](https://travis-ci.org/rettichschnidi/clang-misracpp2008)
=====

clang-misracpp2008 is a project which tries to create an open source checker for
the MISRA C++:2008 rules using the LLVM/Clang infrastructure.

Some rules can easily be checked by enabling compiler-provided flags. For those
rules the suitable switches are listed. Other rules require custom logic, which
is implemented as a plugin.

Progress
========
This project is in an early stage and has not yet been tested extensively!

Have a look at the [progress page in the wiki](https://github.com/rettichschnidi/clang-misracpp2008/wiki/Progress).

Installation
============
It is assumed that you have already have compiled LLVM/Clang from SVN. To add
clang-misracpp2008, the following steps are required:

    export LLVM_CHECKOUT_FOLDER=~/llvm # Adjust to your situation
    cd ${LLVM_CHECKOUT_FOLDER}/tools/clang/tools
    git clone https://github.com/rettichschnidi/clang-misracpp2008.git
    echo 'add_subdirectory(clang-misracpp2008)' >>  CMakeLists.txt

The next time you build LLVM/Clang, clang-misracpp2008 gets picked up and built.

Please note that only the CMake build system is supported.

Bugs
====
When reporting a bug, please include a code snippet which triggers the flaw.

Contributions
=============
To contribute code for a new rule checker, add a file with the test cases to the
"test" folder and implement the checker logic afterwards. The new checker will
get detected when explicitly calling cmake in the build directory.

Please try to follow the [LLVM Coding Standard](http://llvm.org/docs/CodingStandards.html).
At the very least format your code (sans testing code) with clang-format using
the LLVM coding style.

Running Tests
=============
`make check-misracpp2008`

Building Documentation
======================
`make doxygen-misracpp2008`

Usage
=====
The OffendingProject included in the examples directory can be built this way:

    export LLVM_BUILD_DIR=~/build_llvm # Adjust to your situation
    cd ${LLVM_CHECKOUT_FOLDER}/tools/clang/tools/clang-misracpp2008/examples/OffendingProject
    mkdir -p build && cd build
    cmake -DCMAKE_CXX_FLAGS="-Xclang -load -Xclang \
             ${LLVM_BUILD_DIR}/lib/misracpp2008.so -Xclang -add-plugin -Xclang \
             misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang all" \
           -DCMAKE_CXX_COMPILER="${LLVM_BUILD_DIR}/bin/clang++" \
           -DCMAKE_C_COMPILER="${LLVM_BUILD_DIR}/bin/clang" ../
    make

You will get some MISRA C++:2008 violations reported.
