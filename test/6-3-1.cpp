// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-3-1 %s

volatile int cond;

void compliant() {
  for (int i = 0; i < 100; ++i) {
  }

  do {
  } while (cond);

  while (cond) {
  }
}

void violations() {
  for (int i = 0; i < 100; ++i)
    ; // expected-error {{The statement forming the body of a switch, while, do ... while or for statement shall be a compound statement. (MISRA C++ 2008 rule 6-3-1)}}

  do
    ; // expected-error {{The statement forming the body of a switch, while, do ... while or for statement shall be a compound statement. (MISRA C++ 2008 rule 6-3-1)}}
  while (cond);

  while (cond)
    ; // expected-error {{The statement forming the body of a switch, while, do ... while or for statement shall be a compound statement. (MISRA C++ 2008 rule 6-3-1)}}

  while (cond) { // this again is valid
    cond++;
  }
}
