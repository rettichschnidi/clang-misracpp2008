// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 18-0-3 %s
#include <cstdlib>
void useAbort() {
  abort(); // expected-error {{The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. (MISRA C++ 2008 rule 18-0-3)}}
}

void useExit() {
  exit(EXIT_FAILURE); // expected-error {{The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. (MISRA C++ 2008 rule 18-0-3)}}
}

void useGetenv() {
  getenv("HOME"); // expected-error {{The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. (MISRA C++ 2008 rule 18-0-3)}}
}

void useSystem() {
  system("cat /proc/cpuinfo"); // expected-error {{The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. (MISRA C++ 2008 rule 18-0-3)}}
}
