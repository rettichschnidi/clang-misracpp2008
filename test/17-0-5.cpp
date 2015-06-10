// RUN: %clang -fsyntax-only -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 17-0-5 %s
#include <setjmp.h>

jmp_buf buf;

void setup() {
  setjmp(buf); // expected-error {{The setjmp macro and the longjmp function shall not be used. (MISRA C++ 2008 rule 17-0-5)}}
}

void jump() {
  longjmp(buf, 1); // expected-error {{The setjmp macro and the longjmp function shall not be used. (MISRA C++ 2008 rule 17-0-5)}}
}
