// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-10-1 %s

// Only difference is caseness
int abc; // expected-error {{Typographically ambiguous identifier 'abc'}}
int aBc; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

// Only difference is the underscore
int b_b_; // expected-error {{Typographically ambiguous identifier 'b_b_'}} // expected-error {{Typographically ambiguous identifier 'b_b_'}}
int bb; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}} // expected-error {{Typographically ambiguous identifier 'bb'}}
int b___b; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int c0; // expected-error {{Typographically ambiguous identifier 'c0'}}
int cO; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int dI; // expected-error {{Typographically ambiguous identifier 'dI'}}
int d1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int el; // expected-error {{Typographically ambiguous identifier 'el'}}
int eI; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int fl; // expected-error {{Typographically ambiguous identifier 'fl'}}
int f1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int gS; // expected-error {{Typographically ambiguous identifier 'gS'}}
int g5; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int hZ; // expected-error {{Typographically ambiguous identifier 'hZ'}}
int h2; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int iB; // expected-error {{Typographically ambiguous identifier 'iB'}}
int i8; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int jrn; // expected-error {{Typographically ambiguous identifier 'jrn'}}
int jm; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

// Regression test: Typedefs of an anoymous type should not get reported.
typedef enum {
  ENUM1_ENTRY_ONE
} myEnum1;

typedef enum {
  ENUM2_ENTRY_ONE
} myEnum2;
