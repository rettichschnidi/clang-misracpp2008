// RUN: %clang -fshort-enums -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-13-3 %s
// expected-no-diagnostics

enum SignedShortEnum {
  ENUM_SIGNED_ENTRY_ONE = 10, // Compliant
  ENUM_SIGNED_ENTRY_TWO = -20 // Compliant
};
