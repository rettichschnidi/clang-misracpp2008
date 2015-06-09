// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-4-1 %s
#include <new> // std::nothrow
void newPlain() {
  int *i = new int; // expected-error {{Dynamic heap memory allocation shall not be used. (MISRA C++ 2008 rule 18-4-1)}}
  delete i;
}

void newArray() {
  int *i = new int[10]; // expected-error {{Dynamic heap memory allocation shall not be used. (MISRA C++ 2008 rule 18-4-1)}}
  delete[] i;
}

void newNoThrowPlain() {
  int *i = new (std::nothrow) int; // expected-error {{Dynamic heap memory allocation shall not be used. (MISRA C++ 2008 rule 18-4-1)}}
  delete i;
}

void newNoThrowArray() {
  int *i = new (std::nothrow) int[10]; // expected-error {{Dynamic heap memory allocation shall not be used. (MISRA C++ 2008 rule 18-4-1)}}
  delete[] i;
}

void newPlacement() {
  int dummy;
  int *i = new (&dummy) int;
}

void newPlacementArray() {
  int dummy[11];
  int *i = new (&dummy[1]) int[10];
}
