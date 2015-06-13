// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 3-9-2 %s

#include <cstdint>
#include <cstddef>

signed char nonCompliantSignedChar;       // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
unsigned char nonCompliantUnsignedChar;   // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
signed int nonCompliantSignedInt;         // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
unsigned int nonCompliantUnsignedInt;     // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
signed short nonCompliantSignedShort;     // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
unsigned short nonCompliantUnsignedShort; // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
signed long nonCompliantSignedLong;       // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
unsigned long nonCompliantUnsignedLong;   // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
float nonCompliantFloat;                  // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
double nonCompliantDouble;                // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}
long double nonCompliantLongDouble;       // expected-error {{typedefs that indicate size and signedness should be used in place of the basic numerical types. (MISRA C++ 2008 rule 3-9-2)}}

typedef char char_t;
typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;
namespace mynamespace {
typedef char char_t;
}

// A bunch of compliant definitions
char_t compliantChar_t;
mynamespace::char_t compliantNsChar_t;
uint8_t compliantUint8_t;
uint16_t compliantUint16_t;
uint32_t compliantUint32_t;
uint64_t compliantUint64_t;
float32_t compliantFloat32;
float64_t compliantFloat64;
float128_t compliantFloat128;
bool compliantBool;
size_t compliantSize_t;
const size_t compliantConstSize_t = 1;

enum Enum {
  ENUM_ENTRY_A,
  ENUM_ENTRY_B
};

Enum e = ENUM_ENTRY_A;
