// RUN: %clang -fsyntax-only -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-2-3 %s

void f() {
  ;                // Compliant
  ;// Too close comment - expected-error {{Before preprocessing, a null statement shall only occur on a line by itself; it may be followed by a comment, provided that the first character following the null statement is a white‐space character. (MISRA C++ 2008 rule 6-2-3)}}
  /* blablabla */; // expected-error {{Before preprocessing, a null statement shall only occur on a line by itself; it may be followed by a comment, provided that the first character following the null statement is a white‐space character. (MISRA C++ 2008 rule 6-2-3)}}
}
