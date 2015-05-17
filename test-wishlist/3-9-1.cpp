// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-9-1 %s

typedef unsigned long int HugeInt;
typedef float float32;

       HugeInt myHugeInt; // expected-error {{Canonical declaration.}}
extern HugeInt myHugeInt;
extern unsigned long int myHugeInt;  // expected-error {{The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations. (MISRA C++ 2008 rule 3-9-1)}}

HugeInt getHugeInt(float32 p); // expected-error {{Canonical declaration.}}
unsigned long int getHugeInt(float32 p); // expected-error {{The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations. (MISRA C++ 2008 rule 3-9-1)}}
HugeInt getHugeInt(float p); // expected-error {{The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations. (MISRA C++ 2008 rule 3-9-1)}}
HugeInt getHugeInt(float32 myFloat); // Compliant - Only the types have to match, not the names of the arguments

struct CppClass {
  typedef char BYTE;
  static char s_char;
  static BYTE compliantReturnTypeSpelling();
  BYTE nonCompliantReturnTypeSpelling();
  int nonCompliantReturnTypeQualifier();
  void compliantReturnTypeSpelling(int a, BYTE b);
  void nonCompliantCharIsNotByte(BYTE a);
  void nonCompliantIntIsNotSignedInt(signed int intWithSigned);
};
char CppClass::s_char = 'C';
CppClass::BYTE CppClass::compliantReturnTypeSpelling() { return 'a'; } // Compliant
char CppClass::nonCompliantReturnTypeSpelling() { return 'a'; } // expected-error {{The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations. (MISRA C++ 2008 rule 3-9-1)}}
signed int CppClass::nonCompliantReturnTypeQualifier() { return 'a'; } // expected-error {{The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations. (MISRA C++ 2008 rule 3-9-1)}}

void CppClass::compliantReturnTypeSpelling(int a, CppClass::BYTE b) {}
void CppClass::nonCompliantCharIsNotByte(char a) {} // expected-error {{The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations. (MISRA C++ 2008 rule 3-9-1)}}
void CppClass::nonCompliantIntIsNotSignedInt(int intWithoutSigned) {} // expected-error {{The types used for an object, a function return type, or a function parameter shall be token-for-token identical in all declarations and re-declarations. (MISRA C++ 2008 rule 3-9-1)}}
