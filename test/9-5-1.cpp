// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 9-5-1 %s

union MyNastyIllegalUnion { // expected-error {{Unions shall not be used. (MISRA C++ 2008 rule 9-5-1)}}
  int a;
  int b;
};
