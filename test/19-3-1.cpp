// RUN: %clang -fsyntax-only -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 19-3-1 %s
#include <cerrno>
#include <cmath>
#include <iostream>
#include <cstring>

int main() {
    errno = 0; // expected-error {{The error indicator errno shall not be used. (MISRA C++ 2008 rule 19-3-1)}}
    double not_a_number = std::log(-1.0);

    if( errno == EDOM ) { // expected-error {{The error indicator errno shall not be used.}}
        std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';  // expected-error {{The error indicator errno shall not be used. (MISRA C++ 2008 rule 19-3-1)}}
    }
}
