// RUN: %clang -fsyntax-only -ferror-limit=0 -Xclang -verify -Xclang  -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 12-8-2 %s

class B1 {
public:
  B1();
  virtual void f() = 0;
  B1 &operator=(B1 const &rhs); // expected-error {{The copy assignment operator shall be declared protected or private in an abstract class. (MISRA C++ 2008 rule 12-8-2)}}
};

class D1 : public B1 {
public:
  virtual void f() {}
  D1 &operator=(D1 const &rhs);

private:
  int member;
};

class B2 {
public:
  B2();
  virtual void f() = 0;

private:
  B2 &operator=(B2 const &rhs); // Compliant
};
