// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 4-10-2 %s

#include <cstddef>

void f1(int i);
void f2(int *p);
void f3(char *p);
void f4(int, int *);

class T {
public:
  void f(int *p);
};

template <typename T>
void tf(T *);

class C {
  void f();
};

void test_function() {
  f1(0);
  f2(0); // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}
  f3(0); // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}
  f3(NULL);
  f3(nullptr);

  T t;
  t.f(0);     // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}
  tf<int>(0); // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}
  f4(0, 0);   // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}

  f2(nullptr);
  f4(0, nullptr);

  int *a = 0;      // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}
  bool b = a == 0; // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}
  int *c = NULL;
  bool d = c == NULL;
  int *e = nullptr;
  bool f = e == nullptr;

  int (C::*fptrNull)() = NULL;
  int (C::*fptrNullptr)() = nullptr;
  int (C::*fptr0)() = 0; // expected-error {{Literal zero (0) shall not be used as the null-pointer-constant. (MISRA C++ 2008 rule 4-10-2)}}
}
