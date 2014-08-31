// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-13-4 %s

unsigned int u1 = 1U; // Compliant
unsigned int u2 = 1u; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

unsigned int l1 = 1L; // Compliant
unsigned int l2 = 1l; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

unsigned int ul1 = 0x1bUL; // Compliant
unsigned int ul2 = 0x1buL; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}
unsigned int ul3 = 1Ul; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}
unsigned int ul4 = 1ul; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

float f1 = 1.0F; // Compliant
float f2 = 1.0f; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

void func(float &f) {
  f = 10.0F; // Compliant
  f = 10.0f; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}
}
