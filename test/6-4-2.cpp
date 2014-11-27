// RUN: %clang -fsyntax-only -std=c++11 -Wno-empty-body -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-4-2 %s

void compliant(int a, int b, int c, int d, int e, int f) {
  if (a) {
  }

  if (b) {
  } else if (c) {
  } else {
  }

  // Regression test for bug #5
  if (d) {
  } else if (e) {
  } else if (f) {
  } else {
  }
}

void violations(int x, int y) {
  if (x) { // expected-error {{All if ... else if constructs shall be terminated with an else clause. (MISRA C++ 2008 rule 6-4-2)}}
  } else if (y) {
  }
}
