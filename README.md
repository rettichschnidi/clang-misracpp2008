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

Work plan
=========
Work to do, not necessarly in the listed order:

- Implement/Cover as many rules as possible as Clang plugin/options
- Implement as many of the remaining rules as possible as custom Clang Static
Analyzer checkers
- Implement as many of the remaining rules by other means
- Integrate all checkers into a unified web front end that supports the user
with the creation of all the necessary documentation (compliance matrix,
deviations, sign-offs, etc.)  to achieve MISRA compliance
- Repeat everything for MISRA C:2012

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
1. Make sure the rule is not [yet covered](https://github.com/rettichschnidi/clang-misracpp2008/wiki/Progress).
2. Check the `test-wishlist` folder for already existing test code
3. Move/Add a file with the test cases to the `test` folder
4. Implement checker logic - [Dumping the AST](http://clang.llvm.org/docs/IntroductionToTheClangAST.html#examining-the-ast)
of your test code may help you
5. Call `cmake` in the build directory to get the new rule detected
6. Call `make check-misracpp2008` in the build directory to run the tests
7. Optional, if possible: Let the new checker run on your embedded project(s) to
make sure it works as intended, update your tests and fix detected bugs
8. Commit and create a pull request

In case you figure that you can not come up with some usable checker logic,
instead of hiding away or deleting your test code, please move it from `test` to
`test-wishlist` where it can be picked up by someone else.

Coding Style
============
This project follows (tries to...) the [LLVM Coding Standard](http://llvm.org/docs/CodingStandards.html).
At the very least the code has to be formatted using clang-format and the LLVM
coding style.

For testing code feel free to lift the restrictions as necessary. For example,
by using the `.clang-format` file in the test directory.

Running Tests
=============
`make check-misracpp2008`

Building Documentation
======================
`make doxygen-misracpp2008`

Usage
=====
The OffendingProject included in the `examples` directory can be built this way:

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
