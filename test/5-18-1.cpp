// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Wno-unused-value -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 5-18-1 %s

#include <iostream> // Comma operator gets used in here A LOT but it should still not trigger an error

int a, t, c;
bool retValue = true;

// Auxiliary function
int f(int x, int y, int z) {
    return x + y + z;
}

int violatingFunctionCall() {
    return f(a, (t=3, t+2), c); // expected-error {{The comma operator shall not be used.}}
}

void violatingForLoop() {
    for(a = 0, c = a + 10; a < c; a++) { // expected-error {{The comma operator shall not be used.}}
    }
}

int violatingReturn() {
    return (retValue = false, 5); // expected-error {{The comma operator shall not be used.}}
}

void violatingAssignement(int i) {
    if(i == 10) a = 10, c = 10; // expected-error {{The comma operator shall not be used.}}
}
