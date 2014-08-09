// RUN: %clang -fsyntax-only -std=c++11 -Werror -Xclang -verify %s

char newline = '\n';
char hTab = '\n';
char vTab = '\v';
char backspace = '\b';
char carriageReturn = '\r';
char formFeed = '\f';
char alert = '\a';
char backslash = '\\';
char questionmark = '\?';
char singleQuote = '\'';
char doubleQuote = '\"';
char octalEscape = '\101'; // 'A'
char hexEscape = '\x41';   // 'A'

void fn() {
  char a[2] = "\k"; // expected-error {{unknown escape sequence '\k'}}
  char b[2] = "\b"; // Compliant
}
