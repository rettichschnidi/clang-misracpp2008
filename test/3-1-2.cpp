// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-1-2 %s

void regularFunction() {
  void localFunction(); // expected-error {{Functions shall not be declared at block scope. (MISRA C++ 2008 rule 3-1-2)}}
  localFunction();
}

class C {
  void method() { void localFunction(); } // expected-error {{Functions shall not be declared at block scope. (MISRA C++ 2008 rule 3-1-2)}}
};

// Regression tests: Methods within local classes are permitted
void f() {
  struct S {
    S() {}
  };
}
