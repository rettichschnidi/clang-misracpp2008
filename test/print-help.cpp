// RUN: %clang -cc1 -fsyntax-only -load %llvmshlibdir/misracpp2008.so -plugin misra.cpp.2008 -plugin-arg-misra.cpp.2008 --help %s 2>&1 | %llvmtoolsdir/FileCheck %s

// CHECK: Available plugin parameters:
// CHECK-NEXT: [--help] - show this text
// CHECK-NEXT: [--exclude-path=PATH] - do not check files matching PATH
// CHECK-NEXT: [all|-all|--all] - report all rule violations as error/warning/remark
// CHECK-NEXT: [RULE|-RULE|--RULE] - report rule RULE violations as error/warning/remark
