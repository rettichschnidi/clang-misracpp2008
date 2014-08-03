// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-2-2 %s

#include <limits>
#include <cmath>

float getFloat();

void violators(float a, float b) {
  if (a == b) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (a == 666.666F) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (a == getFloat()) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (1U == getFloat()) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }

  if (a <= b && a >= b) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if ((a <= b) && (a >= b)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (a < b || a > b) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if ((a < b) || (a > b)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
}

void compliant(float a, float b, float c) {
  if (std::abs(a - b) <= std::numeric_limits<float>::epsilon()) {
  }

  if (a < b || b < c) { // Compliant - not a circumvention of this rule
  }
}
