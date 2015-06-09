// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 2-13-3 %s

unsigned int a = 1;  // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}
unsigned int b = 2u; // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}
unsigned int c = 3U; // Compliant

int d = 4;  // Compliant
int e = 5U; // Compliant

unsigned int fn1(unsigned int u) {
  return u + 0xFF; // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}
}
unsigned int fn2(unsigned int u) {
  return u + 0xFFU; // Compliant
}
unsigned int fn3(unsigned int u) {
  return u + 255U; // Compliant
}
unsigned int trickyFunction(int) {
  return 1; // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}
}
int trickyFunction(unsigned int) {
  return 2;
}
int trickyFunctionResult = trickyFunction(0x80000000); // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}

unsigned int g = (unsigned int)1;
unsigned int h = static_cast<unsigned int>(1);
unsigned int i = (unsigned int)1U;
unsigned int j = static_cast<unsigned int>(1U);

unsigned char k = 1; // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}
unsigned long l = 1; // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}

enum UnsignedEnum {
    ENUM_UNSIGNED_ENTRY_ONE = 10, // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}
    ENUM_UNSIGNED_ENTRY_TWO = 20  // expected-error {{A "U " suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. (MISRA C++ 2008 rule 2-13-3)}}
};

enum SignedEnum {
    ENUM_SIGNED_ENTRY_ONE =  10, // Compliant
    ENUM_SIGNED_ENTRY_TWO = -20  // Compliant
};

int multiDimensionalArray[2][3][4];
static_assert( 4U == sizeof(multiDimensionalArray[0U][0U])/sizeof(multiDimensionalArray[0U][0U][0U]), "");
static_assert( 4U == sizeof(multiDimensionalArray[0][0])/sizeof(multiDimensionalArray[0][0][0]), "");
