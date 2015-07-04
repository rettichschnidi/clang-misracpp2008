// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Wno-shift-count-negative -Wno-shift-count-overflow -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 5-8-1 %s

#pragma pack(push, 1)
struct BitFieldStruct {
  unsigned int a : 10;
  unsigned int b : 4;
};
#pragma pack(pop)

static_assert(sizeof(BitFieldStruct) == 2U, "");

void sub8bitIntegers() {
  BitFieldStruct bfs;

  bfs.a >>= 10; // Compliant
  bfs.a >>= 11; // expected-error {{The right hand operand of a shift operator shall lie between zero and one less than the width in bits of the underlying type of the left hand operand. (MISRA C++ 2008 rule 5-8-1)}}
}
