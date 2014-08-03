// RUN: %clang -cc1 -fsyntax-only -verify -load %llvmshlibdir/misracpp2008.so -plugin misra.cpp.2008 -plugin-arg-misra.cpp.2008 10-3-2 %s
class A
{
public:
  virtual void badMethod();
  virtual void goodMethod();
  virtual ~A();
};

class B1 : public A
{
public:
  void badMethod();          // expected-error {{Each overriding virtual function shall be declared with the virtual keyword. (MISRA C++ 2008 rule 10-3-2)}}
  virtual void goodMethod(); // Compliant - Explicitly declared virtual
  virtual ~B1();
};

class B2 : public A
{
public:
  void badMethod();          // expected-error {{Each overriding virtual function shall be declared with the virtual keyword. (MISRA C++ 2008 rule 10-3-2)}}
  virtual void goodMethod(); // Compliant - Explicitly declared virtual
  ~B2();                     // expected-error {{Each overriding virtual function shall be declared with the virtual keyword. (MISRA C++ 2008 rule 10-3-2)}}
};

B2::~B2() { } // No virtual specifier required here

class B3 : public A
{
    // ~B3();               // Compliant - implicit destructor is OK, even when virtual
};
