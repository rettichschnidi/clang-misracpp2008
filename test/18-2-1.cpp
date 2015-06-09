// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-2-1 %s
#include <cstddef>

struct A {
  int one;
  int two;
};

void func() {
  int i = offsetof(A, one); // expected-error {{The macro offsetof shall not be used. (MISRA C++ 2008 rule 18-2-1)}}
}
