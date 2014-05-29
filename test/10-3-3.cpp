// RUN: %clang -cc1 -fsyntax-only -verify -load %llvmshlibdir/misracpp2008.so -plugin misra.cpp.2008 -plugin-arg-misra.cpp.2008 10-3-3 %s
class BasePure
{
public:
  virtual void badMethod() =0;
  virtual void goodMethod() =0;
};

class DerivedNonPure : public BasePure
{
public:
  virtual void badMethod(); 
  virtual void goodMethod() =0;
};

class DerivedPureAgain : public DerivedNonPure
{
public:
  virtual void badMethod() =0;  // expected-error {{A virtual function shall only be overridden by a pure virtual function if it is itself declared as pure virtual.}}
  virtual void goodMethod() =0; // Compliant - Was also pure in class DerivedNonPure
};
