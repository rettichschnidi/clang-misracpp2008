// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang all -Xclang -plugin-arg-misra.cpp.2008 -Xclang --exclude-path=exclude-path/excluded-file.cpp %s

#include <assert.h> // expected-error {{The C library shall not be used.}}
