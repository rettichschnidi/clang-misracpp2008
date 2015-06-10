// RUN: %clang -fsyntax-only -ferror-limit=0 -Wno-parentheses -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-2-1 %s

int f1();

void f(int a, int b) {
  int z = 1;
  int zz = a = 2; // expected-error {{Assignment operators shall not be used in sub-expressions. (MISRA C++ 2008 rule 6-2-1)}}
  int t = a != b;

  b = b; // Compliant

  a = b = zz; // expected-error {{Assignment operators shall not be used in sub-expressions. (MISRA C++ 2008 rule 6-2-1)}}

  if (a) { // Compliant
  }
  if (a = b) { // expected-error {{Assignment operators shall not be used in sub-expressions. (MISRA C++ 2008 rule 6-2-1)}}
  }
  if ((a = b)) { // expected-error {{Assignment operators shall not be used in sub-expressions. (MISRA C++ 2008 rule 6-2-1)}}
  }

  if (int v = a) { // Compliant
  }
  if (int v = f1()) { // Compliant
  }

  while (int v = f1()) { // Compliant
  }
  while (z = f1()) { // expected-error {{Assignment operators shall not be used in sub-expressions. (MISRA C++ 2008 rule 6-2-1)}}
  }
}

struct S {
  int i;
  operator bool() { return i == 1; }
};

void complicatedCases(S s) {
  if (S s1 = s) { // Compliant
  }

  S s2;
  if (s2 = s) { // expected-error {{Assignment operators shall not be used in sub-expressions. (MISRA C++ 2008 rule 6-2-1)}}
  }
}
