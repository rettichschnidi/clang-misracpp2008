// RUN: %clang -fsyntax-only -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-10-2 %s

int a; // expected-note {{Previous occurence of identifier 'a'}}

void fnA(int a) { // expected-error {{Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope. (MISRA C++ 2008 rule 2-10-2)}}
}

int b; // expected-note {{Previous occurence of identifier 'b'}}
extern "C" {
void fnB() {
  char b; // expected-error {{Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope. (MISRA C++ 2008 rule 2-10-2)}}
}
}

int c; // expected-note {{Previous occurence of identifier 'c'}}
void fnB2() {
  char c; // expected-error {{Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope. (MISRA C++ 2008 rule 2-10-2)}}
}

int d; // expected-note {{Previous occurence of identifier 'd'}}
int e; // expected-note {{Previous occurence of identifier 'e'}}
class MyClass {
  int d;                // expected-error {{Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope. (MISRA C++ 2008 rule 2-10-2)}}
  void myMethod(int e); // expected-error {{Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope. (MISRA C++ 2008 rule 2-10-2)}}
  void someMethod();    // expected-note {{Previous occurence of identifier 'someMethod'}}
  void operator++() {}
  class MyInnerClass {
    void someMethod(); // expected-error {{Identifiers declared in an inner scope shall not hide an identifier declared in an outer scope. (MISRA C++ 2008 rule 2-10-2)}}
    void operator++() {}
  };
};

extern "C" {
void functionDeclarationInBlock(void);
extern int variableDeclarationInBlock;
}
void functionDeclarationInBlock(void);
int variableDeclarationInBlock = 10;
