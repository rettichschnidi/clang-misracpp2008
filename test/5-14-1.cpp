// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 5-14-1 %s

volatile int volatileInteger; // Reading a volatile variable falls into the category "has sideeffect".

/// In the MISRA C++:2008 (and C++ in general) world, this function should not be rated as having a
/// side effect.
/// Clang however threads every call to a function (CallExprClass) as side effect.
/// \todo Add logic to recognize this function as having no side-effects.
int noSideEffectsFunction(int valA, int valB) {
    return valA + valB;
}

int sideEffectsFunction() {
    volatileInteger = 10;
    return volatileInteger;
}

void volatileTest(int v) {
    if(v == 10 && volatileInteger == 10) { // expected-error {{The right hand operand of a logical && or || operator shall not contain side effects.}}
    }

    if(v == 10 || volatileInteger == 10) { // expected-error {{The right hand operand of a logical && or || operator shall not contain side effects.}}
    }

    if(volatileInteger < 0 || volatileInteger > 10) { // expected-error {{The right hand operand of a logical && or || operator shall not contain side effects.}}
    }

    // This should generate two errors
    if((volatileInteger < 0 || volatileInteger > 10) && sideEffectsFunction()) { // expected-error {{The right hand operand of a logical && or || operator shall not contain side effects.}} expected-error {{The right hand operand of a logical && or || operator shall not contain side effects.}}
    }
}

void functionCallTest(int v) {
    if(v == 10 && sideEffectsFunction() == 8) { // expected-error {{The right hand operand of a logical && or || operator shall not contain side effects.}}
    }
}
