// RUN: %clang -fsyntax-only -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-9-2,19-3-1 %s

// CHECK: Active checks: 19-3-1, 3-9-2
