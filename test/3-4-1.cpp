// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-4-1 %s

int squareNatural(int value) {
  int square = value * value; // expected-error {{An identifier declared to be an object or type shall be defined in a block that minimizes its visibility. (MISRA C++ 2008 rule 3-4-1)}}

  if (value >= 0) {
    struct A {
      int i;
      int func();
    };

    A a = {square};
    return a.i;
  }

  return 0;
}
