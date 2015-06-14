// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 4-5-3 %s

#include <cstdint>

typedef unsigned char char_t;

void plainCharT(char_t ch, int i) {
  bool isDigit = (ch >= '0' && ch <= '9'); // Compliant by exception
  bool isAlpha = (ch >= 'a' && ch <= 'z'); // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}} // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  int charToInt = ch - '0';                // Compliant by exception
  int failCharToInt = ch - '1';            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  char_t intToChar = '0' + i;              // Compliant by exception
  char_t failIntToChar = 'A' + i;          // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}

  char_t c = ch;         // Compliant
  bool b = 'b' == ch;    // Compliant
  bool notC = 'c' != ch; // Compliant
  char_t *d = &ch;       // Compliant

  ch++;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ch--;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ++ch;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  --ch;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  int e = 0xAA & ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
}

void plainChar(char ch, int i) {
  bool isDigit = (ch >= '0' && ch <= '9'); // Compliant by exception
  bool isAlpha = (ch >= 'a' && ch <= 'z'); // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}} // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  int charToInt = ch - '0';                // Compliant by exception
  int failCharToInt = ch - '1';            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  char intToChar = '0' + i;                // Compliant by exception
  char failIntToChar = 'A' + i;            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}

  char c = ch;           // Compliant
  bool b = 'b' == ch;    // Compliant
  bool notC = 'c' != ch; // Compliant
  char *d = &ch;         // Compliant

  ch++;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ch--;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ++ch;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  --ch;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  int e = 0xAA & ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
}

void plainWideChar(wchar_t ch, int i) {
  bool isDigit = (ch >= '0' && ch <= '9'); // Compliant by exception
  bool isAlpha = (ch >= 'a' && ch <= 'z'); // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}} // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  int charToInt = ch - '0';                // Compliant by exception
  int failCharToInt = ch - '1';            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  char intToChar = '0' + i;                // Compliant by exception
  char failIntToChar = 'A' + i;            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}

  wchar_t c = ch;           // Compliant
  wchar_t b = 'b' == ch;    // Compliant
  wchar_t notC = 'c' != ch; // Compliant
  wchar_t *d = &ch;         // Compliant

  ch++;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ch--;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ++ch;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  --ch;              // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  int e = 0xAA & ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
}

// Everything is allowed for uint8_t
void nonPlainCharUint8(uint8_t ch, int i) {
  uint8_t uint8Value = ch - 1;

  uint8_t c = ch;
  bool b = 0x66 == ch;
  bool notC = 0x67 != ch;
  uint8_t *d = &ch;

  ch++;
  ch--;
  ++ch;
  --ch;
  int e = 0xAA & ch;
}
