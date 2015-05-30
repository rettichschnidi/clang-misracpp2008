// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008.so -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 4-5-1 %s

int funcWithBools(bool paramA, bool paramB) {
  if (paramA & paramB) // expected-error {{Expressions with type bool shall not be used as operands to built-in operators other than the assignment operator = , the logical operators && , || , ! , the equality operators == and != , the unary & operator, and the conditional operator. (MISRA C++ 2008 rule 4-5-1)}}
    ;
  if (paramA < paramB) // expected-error {{Expressions with type bool shall not be used as operands to built-in operators other than the assignment operator = , the logical operators && , || , ! , the equality operators == and != , the unary & operator, and the conditional operator. (MISRA C++ 2008 rule 4-5-1)}}
    ;
  if (~paramA) // expected-error {{Expressions with type bool shall not be used as operands to built-in operators other than the assignment operator = , the logical operators && , || , ! , the equality operators == and != , the unary & operator, and the conditional operator. (MISRA C++ 2008 rule 4-5-1)}}
    ;
  if (paramA ^ paramB) // expected-error {{Expressions with type bool shall not be used as operands to built-in operators other than the assignment operator = , the logical operators && , || , ! , the equality operators == and != , the unary & operator, and the conditional operator. (MISRA C++ 2008 rule 4-5-1)}}
    ;
  if (paramA == false)
    ;
  if (paramA == paramB)
    ;
  if (paramA != paramB)
    ;
  if (paramA && paramB)
    ;
  if (!paramA)
    ;

  int retVal;
  retVal = paramA ? 3 : 7;
  return retVal;
}

int funcWithInteger(unsigned int paramA, unsigned int paramB) {
  if (paramA & paramB)
    ;
  if (paramA < paramB)
    ;
  if (~paramA)
    ;
  if (paramA ^ paramB)
    ;
  if (paramA == false)
    ;
  if (paramA == paramB)
    ;
  if (paramA != paramB)
    ;
  if (paramA && paramB)
    ;
  if (!paramA)
    ;

  int retVal;
  retVal = paramA ? 3 : 7;
  return retVal;
}
