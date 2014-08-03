// RUN: %clang -cc1 -fsyntax-only -verify -load %llvmshlibdir/misracpp2008.so -plugin misra.cpp.2008 -plugin-arg-misra.cpp.2008 -10-3-2 %s
class A {
public:
  virtual void badMethod();
  virtual void goodMethod();
};

class B1 : public A {
public:
  void badMethod();          // expected-warning {{Each overriding virtual function shall be declared with the virtual keyword.}}
  virtual void goodMethod(); // Compliant - Explicitly declared virtual
};
