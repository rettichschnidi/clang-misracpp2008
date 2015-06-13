// RUN: %clang -fsyntax-only -std=c++11 -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 4-5-2 %s

#include <cstdint>
#include <vector>

enum Color { RED,
             GREEN,
             BLUE,
             COLOUR_COUNT };

void compliant(Color color, Color *colorPointer) {
  // Check operator[]
  float allAlpha[COLOUR_COUNT] = {0.1F, 0.2F, 0.3F};
  float alpha = allAlpha[color]; // Compliant
  std::vector<int> v = {1, 2, 3};
  int val = v[color];

  // Check assignement operator
  Color colorCopy = color; // Compliant

  // Check Equality operators
  if (RED == color) { // Compliant
  }
  if (RED != color) { // Compliant
  }
  // Check unary & operator
  if (&color > colorPointer) { // Compliant
  }
  if (sizeof(color) > 1) { // Compliant
  }

  //Check relational operators
  if (color < GREEN) { // Compliant
  }
  if (color <= GREEN) { // Compliant
  }
  if (color > GREEN) { // Compliant
  }
  if (color >= GREEN) { // Compliant
  }

  // TOOD: Should we have tests for conditional operators as well?!
}

void violations(Color color) {
  // Some Binary operators
  if (RED & color) { // expected-error {{Expressions with type enum shall not be used as operands to built-in operators other than the subscript operator [ ] , the assignment operator = , the equality operators == and != , the unary & operator, and the relational operators < , <= , > , >= . (MISRA C++ 2008 rule 4-5-2)}}
  }
  if ((RED + GREEN) == color) { // expected-error {{Expressions with type enum shall not be used as operands to built-in operators other than the subscript operator [ ] , the assignment operator = , the equality operators == and != , the unary & operator, and the relational operators < , <= , > , >= . (MISRA C++ 2008 rule 4-5-2)}}
  }

  // Some unary operators
  if (RED & color) { // expected-error {{Expressions with type enum shall not be used as operands to built-in operators other than the subscript operator [ ] , the assignment operator = , the equality operators == and != , the unary & operator, and the relational operators < , <= , > , >= . (MISRA C++ 2008 rule 4-5-2)}}
  }
  if (!color) { // expected-error {{Expressions with type enum shall not be used as operands to built-in operators other than the subscript operator [ ] , the assignment operator = , the equality operators == and != , the unary & operator, and the relational operators < , <= , > , >= . (MISRA C++ 2008 rule 4-5-2)}}
  }
  if (-color) { // expected-error {{Expressions with type enum shall not be used as operands to built-in operators other than the subscript operator [ ] , the assignment operator = , the equality operators == and != , the unary & operator, and the relational operators < , <= , > , >= . (MISRA C++ 2008 rule 4-5-2)}}
  }
}
