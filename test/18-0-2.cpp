// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-0-2 %s
#include <cstdlib>
void useAtof() {
    float f = atof("3.3"); // expected-error {{The library functions atof, atoi and atol from library <cstdlib> shall not be used. (MISRA C++ 2008 rule 18-0-2)}}
}

void useAtoi() {
    int i = atoi("123"); // expected-error {{The library functions atof, atoi and atol from library <cstdlib> shall not be used. (MISRA C++ 2008 rule 18-0-2)}}
}

void useAtol() {
    long i = atol("1234556790"); // expected-error {{The library functions atof, atoi and atol from library <cstdlib> shall not be used. (MISRA C++ 2008 rule 18-0-2)}}
}
