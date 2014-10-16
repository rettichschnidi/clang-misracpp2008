// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-13-5 %s

char    narrowChars[]   = "Hello" " narrow chars."; // Compliant
wchar_t wideChars[]     = L"Hello" L" wide chars."; // Compliant
wchar_t mixedChars[]    = "Hello" L" narrow and mixed chars.";  // expected-error {{Narrow and wide string literals shall not be concatenated. (MISRA C++ 2008 rule 2-13-5)}}
