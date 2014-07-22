// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 5-18-1 %s


int a, b; // expect-error {{The comma operator shall not be used.}}

// Auxiliary function
int function(int a, int b) {
    return a + b;
}

int violatingFunctionCall() {
    function( (1, 10), 50);  // expect-error {{The comma operator shall not be used.}}
}
