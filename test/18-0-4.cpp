// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-0-4 %s
#include <ctime> // expected-error {{The time handling functions of library <ctime> shall not be used. (MISRA C++ 2008 rule 18-0-4)}}
