// RUN: %clang -fsyntax-only -Wconversion -Werror -Xclang -verify %s

short truncateImplicitly(int i) {
  return i; // expected-error {{implicit conversion loses integer precision: 'int' to 'short'}}
}

short truncateExplicitly(int i) {
  return static_cast<short>(i);
}
