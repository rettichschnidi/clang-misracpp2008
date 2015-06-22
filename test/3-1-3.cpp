// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-1-3 %s

int arrayExplicitNumberOfElements[10];
int arrayExplicitlyInitialized[] = {1, 2, 3};

extern int externArrayExplicitNumberOfElements[10];
extern int externArrayUnknownSize[]; // expected-error {{When an array is declared, its size shall either be stated explicitly or defined implicitly by initialization. (MISRA C++ 2008 rule 3-1-3)}}

// Regression test: non-array declarations must not trigger false-positives
int nonArray;
