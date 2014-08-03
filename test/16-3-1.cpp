// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 16-3-1 %s

// Some allowed defines
#define MAKE_STRING1(s) #s
#define MAKE_STRING2(s) "hello " #s
#define COMBINE(s1, s2) s1##s2
#define MAKE_NOTHING(x)

// Disallowed usages
#define TRIPPLE_CONCAT(s) s##s##s              // expected-error {{There shall be at most one occurrence of the # or ## operators in a single macro definition. (MISRA C++ 2008 rule 16-3-1)}}
#define DOUBLE_STRINGIFY(s1, s2) #s1 #s2       // expected-error {{There shall be at most one occurrence of the # or ## operators in a single macro definition. (MISRA C++ 2008 rule 16-3-1)}}
#define STRINGIFY_CONCAT1(s1, s2) #s1##s2      // expected-error {{There shall be at most one occurrence of the # or ## operators in a single macro definition. (MISRA C++ 2008 rule 16-3-1)}}
#define STRINGIFY_CONCAT2(s1, s2) s1##s2 #s1   // expected-error {{There shall be at most one occurrence of the # or ## operators in a single macro definition. (MISRA C++ 2008 rule 16-3-1)}}
#define STRINGIFY_MULTILINE(s1, s2) s1##s2 #s1 // expected-error {{There shall be at most one occurrence of the # or ## operators in a single macro definition. (MISRA C++ 2008 rule 16-3-1)}}
