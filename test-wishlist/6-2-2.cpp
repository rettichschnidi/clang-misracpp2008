// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-2-2 %s

void obfuscatedViolations(float a, float b) {
  // Adding an extra parameter for obfuscation
  if (a <= b && true && a >= b) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
}
