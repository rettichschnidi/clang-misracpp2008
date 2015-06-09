// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 16-3-2 %s

// Disallowed usages
#define CONCAT(s) HELLO##s                 // expected-error {{The # and ## operators should not be used. (MISRA C++ 2008 rule 16-3-2)}}
#define STRINGIFY(s) #s                    // expected-error {{The # and ## operators should not be used. (MISRA C++ 2008 rule 16-3-2)}}
#define STRINGIFY_MULTILINE(s) "HELLO " #s // expected-error {{The # and ## operators should not be used. (MISRA C++ 2008 rule 16-3-2)}}
