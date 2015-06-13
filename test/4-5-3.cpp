// RUN: %clang -fsyntax-only -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 4-5-3 %s

void IsDigit(char ch, int i) {
  bool isDigit = (ch >= '0' && ch <= '9'); // Compliant by exception
  bool isAlpha = (ch >= 'a' && ch <= 'z'); // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}} // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  int charToInt = ch - '0';                // Compliant by exception
  int failCharToInt = ch - '1';            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  char intToChar = '0' + i;                // Compliant by exception
  char failIntToChar = 'A' + i;            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}

  char c = ch; // Compliant
  bool b = 'b' == ch; // Compliant
  bool notC = 'c' != ch; // Compliant
  char *d = &ch; // Compliant

  ch++; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ch--; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ++ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  --ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  int e = 0xAA & ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
}

void IsDigit(wchar_t ch, int i) {
  bool isDigit = (ch >= '0' && ch <= '9'); // Compliant by exception
  bool isAlpha = (ch >= 'a' && ch <= 'z'); // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}} // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  int charToInt = ch - '0';                // Compliant by exception
  int failCharToInt = ch - '1';            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
  char intToChar = '0' + i;                // Compliant by exception
  char failIntToChar = 'A' + i;            // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}

  wchar_t c = ch; // Compliant
  wchar_t b = 'b' == ch; // Compliant
  wchar_t notC = 'c' != ch; // Compliant
  wchar_t *d = &ch; // Compliant

  ch++; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ch--; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  ++ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  --ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}}
  int e = 0xAA & ch; // expected-error {{Expressions with type (plain) char and wchar_t shall not be used as operands to built-in operators other than the assignment operator = , the equality operators == and != , and the unary & operator. (MISRA C++ 2008 rule 4-5-3)}}
}
