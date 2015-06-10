// RUN: %clang -fsyntax-only -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-2-2 %s

#include <limits>
#include <cmath>

float getFloat() { return 1.0F; }

void simpleViolations(float a, float b) {
  // Simplest case
  if (a == b) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (a == 0.0F) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (a == -0.0F) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (a == getFloat()) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (1U == getFloat()) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
}

void obfuscatedViolationsViaArray(float a, float b, float c) {
  const float limit[2] = { a, b };
  if ((c > limit[0]) && (c < limit[1]) ) { // Compliant
  }
  if ((c > limit[0]) && (c < limit[0]) ) {  // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }

  if (c == limit[1]) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
}

void obfuscatedViolations(float a, float b) {
  if (a <= b && a >= b) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if (a < b || a > b) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  // Extra parenteses have to work as well
  if ((a <= b) || (a >= b)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
}

// Obfuscations by abusing (more or less) complicated constant expressions which evaluate
// to the desired value.
// TODO: Does this really ALWAYS work? How about rounding errors?
void obfuscatedViolationsWithCostexpr(float a) {
  if (a == (8.3F - 8.3F)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if ((a < 0.0F || a > (-8.0F + 8.0F))) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }

  if ((a < (1.1F - 2 * 0.55F) || a > (-8.0F + 10 * 0.8F))) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
}
// Make sure we can deal with (negative) float/double/integer literals
void obfuscatedViolationsLiterals(float a) {
  // Floats
  if ((a < 1.0F) || (a > 1.0F)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if ((a < -1.0F) || (a > -1.0F)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  // Doubles
  if ((a < 2.0) || (a > 2.0)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if ((a < -5.0) || (a > -5.0)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  // Integers
  if ((a < 3) || (a > 3)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
  if ((a < -3) || (a > -3)) { // expected-error {{Floating-point expressions shall not be directly or indirectly tested for equality or inequality. (MISRA C++ 2008 rule 6-2-2)}}
  }
}

void compliant(float a, float b, float c) {
  if (std::abs(a - b) <= std::numeric_limits<float>::epsilon()) {
  }

  if (a < b || b < c) { // Compliant - not a circumvention of this rule
  }

  // This is not an obfuscated equal comparisation
  if ((a < 5) || (a > 6)) {
  }

  // This is not an obfuscated equal comparisation
  if ((a < (5 + 2)) || (a > (5 + 1))) {
  }
}
