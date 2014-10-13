// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-13-4 %s


unsigned int u1 = 1U; // Compliant
unsigned int u2 = 1u; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

long l1 = 1L; // Compliant
long l2 = 1l; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

unsigned long ul0 = 0x1fUL; // Compliant
unsigned long ul1 = 0x1bUL; // Compliant
unsigned long ul2 = 0x1buL; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}
unsigned long ul3 = 1Ul; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}
unsigned long ul4 = 1ul; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

float f1 = 1.0F; // Compliant
float f2 = 1.0f; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}

void func(float &f) {
  f = 10.0F; // Compliant
  f = 10.0f; // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}
}

// Regression test - macros got misinterpreted
#define STX_ETX_BUFFER_SIZE_GOOD   180 ///< "u", "l", "f" in a comment, all lowercase
unsigned char buffer1[STX_ETX_BUFFER_SIZE_GOOD]; // Compliant
#define STX_ETX_BUFFER_SIZE_FAIL   180u
unsigned char buffer2[STX_ETX_BUFFER_SIZE_FAIL];  // expected-error {{Literal suffixes shall be upper case. (MISRA C++ 2008 rule 2-13-4)}}
