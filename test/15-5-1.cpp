// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 15-5-1 %s

#include <stdexcept>

class A {
public:
  ~A() {
    throw std::runtime_error(""); // expected-error {{A class destructor shall not exit with an exception. (MISRA C++ 2008 rule 15-5-1)}}
  }
};

class B {
public:
  ~B() {
    throw std::runtime_error(""); // expected-error {{A class destructor shall not exit with an exception. (MISRA C++ 2008 rule 15-5-1)}}
  }
};

class C {
public:
  ~C();
};

C::~C() {
  try {
    throw std::runtime_error("");
  } catch (const std::exception &ex) { // Compliant
  }
};

class D {
  ~D() noexcept;
};

D::~D() noexcept {
  throw std::runtime_error(""); // expected-error {{A class destructor shall not exit with an exception. (MISRA C++ 2008 rule 15-5-1)}}
}

class MoreComplicated {
public:
  ~MoreComplicated() {
    if (test()) {
      fun();
    }
    if (test()) {
      if (test()) {
        fun();
        throw std::domain_error(""); // expected-error {{A class destructor shall not exit with an exception. (MISRA C++ 2008 rule 15-5-1)}}
      }
    }
  }

  void fun() {
    for (int i = 0; i < 10; ++i) {
    }
  }

  bool test() {
    return true;
  }
};

void fun() {
  A a;
}
