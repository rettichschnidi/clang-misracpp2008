// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-10-1 %s

// Only difference is caseness
int abc; // expected-note {{Typographically ambiguous identifier 'abc'}}
int aBc; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

// Only difference is the underscore
int b_b_; // expected-note {{Typographically ambiguous identifier 'b_b_'}} // expected-note {{Typographically ambiguous identifier 'b_b_'}}
int bb; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}} // expected-note {{Typographically ambiguous identifier 'bb'}}
int b___b; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int c0; // expected-note {{Typographically ambiguous identifier 'c0'}}
int cO; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int dI; // expected-note {{Typographically ambiguous identifier 'dI'}}
int d1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int el; // expected-note {{Typographically ambiguous identifier 'el'}}
int eI; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int fl; // expected-note {{Typographically ambiguous identifier 'fl'}}
int f1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int gS; // expected-note {{Typographically ambiguous identifier 'gS'}}
int g5; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int hZ; // expected-note {{Typographically ambiguous identifier 'hZ'}}
int h2; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int iB; // expected-note {{Typographically ambiguous identifier 'iB'}}
int i8; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int jrn; // expected-note {{Typographically ambiguous identifier 'jrn'}}
int jm; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

// Regression test: Typedefs of an anoymous type should not get reported.
typedef enum {
  ENUM1_ENTRY_ONE
} myEnum1;

typedef enum {
  ENUM2_ENTRY_ONE
} myEnum2;

void func (int aVariable, int _anotherVariable) { // expected-note {{Typographically ambiguous identifier 'aVariable'}}  { // expected-note {{Typographically ambiguous identifier '_anotherVariable'}}
  int a_Variable; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
  int anotherVariable; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
}
