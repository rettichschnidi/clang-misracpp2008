// RUN: clang -cc1 -fsyntax-only -verify -load %llvmshlibdir/misracpp2008.so -plugin misra.cpp.2008 -plugin-arg-misra.cpp.2008 10-3-2 %s
class A
{
public:
  virtual void virtualMethod();
  virtual void pureMethod() =0;
};

class B : public A
{
public:
  void virtualMethod();         // expected-error {{Each overriding virtual function shall be declared with the virtual keyword.}}
  virtual void pureMethod();
};

class C : public B
{
public:
  virtual void pureMethod() =0; // Non-compliant, but non-detected as rule 10-3-3 is not enabled
};
