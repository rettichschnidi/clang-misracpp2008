// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 27-0-1 %s
#include <cstdio> // expected-error {{The stream input/output library <cstdio> shall not be used. (MISRA C++ 2008 rule 27-0-1)}}
