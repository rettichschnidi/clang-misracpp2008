// RUN: %clang -fsyntax-only -std=c++11 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang all -Xclang -plugin-arg-misra.cpp.2008 -Xclang --exclude-path=exclude-path/excluded-file.cpp %s

// expected-no-diagnostics
#include <assert.h> // Violates rule 18-0-1 but no report should be issued
