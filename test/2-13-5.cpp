// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-13-5 %s

const char    narrowChars[] = "NarrowChars";
const wchar_t wideChars[] = L"WideChars";

const char    narrowCharsConcat[] = "NarrowChars" "MoreNarrowChars";
const wchar_t wideCharsConcat[] = L"WideChars" L"MoreWideChars";
const wchar_t mixedCharsConcat[] = "NarrowChars" L"WideChars"; // expected-error {{Narrow and wide string literals shall not be concatenated. (MISRA C++ 2008 rule 2-13-5)}}
const wchar_t mixedCharsConcatReverse[] = L"WideChars" "NarrowChars"; // expected-error {{Narrow and wide string literals shall not be concatenated. (MISRA C++ 2008 rule 2-13-5)}}
