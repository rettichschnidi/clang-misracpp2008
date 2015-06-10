// RUN: %clang -fsyntax-only -Wno-empty-body -ferror-limit=0 -Xclang -verify -Xclang -load -Xclang %llvmshlibdir/misracpp2008%pluginext -Xclang -plugin -Xclang misra.cpp.2008 -Xclang -plugin-arg-misra.cpp.2008 -Xclang 6-4-1 %s

void compliant(int x, int y, int z) {
  if (x) {
  }

  if (x) {
  } else if (y) {
  }

  if (x) {
  } else if (y) {
  } else {
  }
}

void violations(int x, int y, int z) {
  if (x)
    ; // expected-error {{An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. (MISRA C++ 2008 rule 6-4-1)}}

  if (x)
    y = 1; // expected-error {{An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. (MISRA C++ 2008 rule 6-4-1)}}

  if (x) {
  } else
    y = 1; // expected-error {{An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. (MISRA C++ 2008 rule 6-4-1)}}

  if (x) {
  } else if (y) {
  } else
    z = 1; // expected-error {{An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. (MISRA C++ 2008 rule 6-4-1)}}
}
