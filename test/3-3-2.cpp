// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-3-2 %s

static void compliantStaticFunc();
static void compliantStaticFunc() {}

void compliantNonStaticFunc();
void compliantNonStaticFunc() {}

static void nonCompliantStaticFun();
void nonCompliantStaticFun() { // expected-error {{If a function has internal linkage then all re-declarations shall include the static storage class specifier. (MISRA C++ 2008 rule 3-3-2)}}
}

class A {
  static void staticMethod();
};

void A::staticMethod() {}
