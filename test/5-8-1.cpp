// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Wno-shift-count-negative -Wno-shift-count-overflow -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 5-8-1 %s

#include <cstdint>
#include <iostream>

#define SHIFT_2 2
#define SHIFT_8 8
#define SHIFT_NEG -1

void leftShiftFunction() {
  uint8_t u8 = 1;
  uint16_t u16;
  const uint8_t shiftNum = 10;

  u8 = (uint8_t)(u8 << 0);              // Compliant - 0 is the lower bound
  u8 = (uint8_t)(u8 << 7);              // Compliant - 7 is the upper bound
  u8 = (uint8_t)(u8 << 8);              // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 << (4 + 3));        // Compliant - 7
  u8 = (uint8_t)(u8 << (4 + 4));        // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 << -1);             // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 << shiftNum);       // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u16 = (uint16_t)((uint16_t)u8 << 15); // Compliant - 15 is the upper bound for a 16 bit value
  u16 = (uint16_t)((uint16_t)u8 << 16); // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}

  // Using macros
  u8 = (uint8_t)(u8 << SHIFT_2);   // Compliant - the macro value is 2
  u8 = (uint8_t)(u8 << SHIFT_8);   // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 << SHIFT_NEG); // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
}

void rightShiftFunction() {
  uint8_t u8 = 1;
  uint16_t u16;
  const uint8_t shiftNum = 10;

  u8 = (uint8_t)(u8 >> 0);              // Compliant - 0 is the lower bound
  u8 = (uint8_t)(u8 >> 7);              // Compliant - 7 is the upper bound
  u8 = (uint8_t)(u8 >> 8);              // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 >> (4 + 3));        // Compliant - 7
  u8 = (uint8_t)(u8 >> (4 + 4));        // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 >> -1);             // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 >> shiftNum);       // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u16 = (uint16_t)((uint16_t)u8 >> 15); // Compliant - 15 is the upper bound for a 16 bit value
  u16 = (uint16_t)((uint16_t)u8 >> 16); // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}

  // Using macros
  u8 = (uint8_t)(u8 >> SHIFT_2);   // Compliant - the macro value is 2
  u8 = (uint8_t)(u8 >> SHIFT_8);   // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 = (uint8_t)(u8 >> SHIFT_NEG); // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
}

void leftShiftAssignFunction() {
  uint8_t u8 = 1;
  const uint8_t shiftNum = 10;

  u8 <<= 0;        // Compliant - 0 is the lower bound$
  u8 <<= 7;        // Compliant - 7 is the upper bound
  u8 <<= 8;        // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 <<= shiftNum; // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 <<= -1;       // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}

  // Using macros
  u8 <<= SHIFT_2;   // Compliant - the macro value is 2
  u8 <<= SHIFT_8;   // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 <<= SHIFT_NEG; // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
}

void rightShiftAssignFunction() {
  uint8_t u8 = 1;
  const uint8_t shiftNum = 10;

  u8 >>= 0;        // Compliant - 0 is the lower bound
  u8 >>= 7;        // Compliant - 7 is the upper bound
  u8 >>= 8;        // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 >>= shiftNum; // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 >>= -1;       // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}

  // Using macros
  u8 >>= SHIFT_2;   // Compliant - the macro value is 2
  u8 >>= SHIFT_8;   // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
  u8 >>= SHIFT_NEG; // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
}

void outputStream() {
  std::cout << "Hello World!" << std::endl; // This is not integer shifting!
}
