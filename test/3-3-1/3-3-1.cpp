// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-3-1 %s
#include "3-3-1.hpp"

int integerExtern; // Compliant, as declared extern in header
void functionExplicitExtern() {} // Compliant, as declared extern in header
void functionImplicitExtern() {} // Compliant, as declared extern in header

static int integerLocalStatic; // Compliant
static int functionLocalStatic(); // Compliant

namespace {
int integerInAnonymousNamespace;
void functionInAnonymousNamespace() {}
}
int integerLocalNonStatic; // expected-error {{Objects or functions with external linkage shall be declared in a header file. (MISRA C++ 2008 rule 3-3-1)}}
int functionLocalNonStatic(); // expected-error {{Objects or functions with external linkage shall be declared in a header file. (MISRA C++ 2008 rule 3-3-1)}}

const int constImpliesStatic = 1; // Compliant

static int func() {
  int autoVar = 0; // Compliant
  return autoVar;
}

int main(int, char **) { // Compliant
  return 0;
}

static void funcWithLocalClass() {
  class LocalClass {
    void method() {} // Compliant
  };
}

