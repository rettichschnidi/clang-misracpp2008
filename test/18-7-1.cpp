// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-7-1 %s
#include <csignal> // expected-error {{The signal handling facilities of <csignal> shall not be used. (MISRA C++ 2008 rule 18-7-1)}}
