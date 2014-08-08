// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-10-1 %s

// Only difference is caseness
int abc;
int aBc; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

// Only difference is the underscore
int b_b_;
int bb; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
int b___b; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int c0;
int cO; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int dI;
int d1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int el;
int eI; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int fl;
int f1; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int gS;
int g5; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int hZ;
int h2; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int iB;
int i8; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}

int jrn;
int jm; // expected-error {{Different identifiers shall be typographically unambiguous. (MISRA C++ 2008 rule 2-10-1)}}
