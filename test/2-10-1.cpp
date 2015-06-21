// RUN: %clang -fsyntax-only -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-10-1 %s

#include <cstddef>
using namespace std; // Regression test - this should not cause a crash

// Only difference is caseness
int abc; // expected-note {{Typographically too close to 'aBc'}}
int aBc; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

// Only difference is the underscore
int b_b_;  // expected-note {{Typographically too close to 'bb'}} // expected-note {{Typographically too close to 'b___b'}}
int bb;    // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}} // expected-note {{Typographically too close to 'b___b'}}
int b___b; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int c0; // expected-note {{Typographically too close to 'cO'}}
int cO; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int dI; // expected-note {{Typographically too close to 'd1'}}
int d1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int el; // expected-note {{Typographically too close to 'eI'}}
int eI; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int fl; // expected-note {{Typographically too close to 'f1'}}
int f1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int gS; // expected-note {{Typographically too close to 'g5'}}
int g5; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int hZ; // expected-note {{Typographically too close to 'h2'}}
int h2; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int iB; // expected-note {{Typographically too close to 'i8'}}
int i8; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int jrn; // expected-note {{Typographically too close to 'jm'}}
int jm;  // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

// Regression test: Typedefs of an anoymous type should not get reported.
typedef enum {
  ENUM1_ENTRY_ONE
} myEnum1;

typedef enum {
  ENUM2_ENTRY_ONE
} myEnum2;

void func(int aVariable, int _anotherVariable) { // expected-note {{Typographically too close to 'a_Variable'}}  { // expected-note {{Typographically too close to 'anotherVariable'}}
  int a_Variable;                                // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
  int anotherVariable;                           // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
}

void anotherFunc(int aVariable, int _anotherVariable) { // Compliant - does not interfiere with the parameters of func()
}

template <typename FuncReturnType>
FuncReturnType templatedFunction() {
  return FuncReturnType{0};
}
int i1 = templatedFunction<int>();
float i2 = templatedFunction<float>();

template <typename FuncReturnType>
FuncReturnType templatedFunctionViolating(); // expected-note {{Typographically too close to 'templated_function_violating'}}
template <typename FuncReturnType>
FuncReturnType templated_function_violating(); // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

template <typename Type>
struct S {
  template <typename ReturnType>
  ReturnType templateMethod(); // expected-note {{Typographically too close to 'template_method'}}
  template <typename ReturnType>
  ReturnType template_method();                          // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
  template <typename AnotherType, typename another_type> // expected-note {{Typographically too close to 'another_type'}} // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
  AnotherType template_method_unrelated(another_type t);
  S() {}
};

void func() {
  S<float> sFloat;
  sFloat.templateMethod<float>();
  sFloat.templateMethod<double>();

  S<short> sInt;
  sInt.templateMethod<short>();
  sInt.templateMethod<int>();
}
