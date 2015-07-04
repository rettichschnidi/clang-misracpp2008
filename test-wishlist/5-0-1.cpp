// RUN: %clang -fsyntax-only -Wunsequenced -Werror -Xclang -verify %s

int f(int &i);
int g(int &i);
void funcCallOrdering(int v) {
  int x = f(v) + g(v); // Non-compliant
}

void volatileAccess(volatile int &i, volatile int &j) {
  int r1 = i + j; // Non-compliant

  int r2 = i;
  r2 += j; // Compliant
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int macrousageWithSideeffects(int &i, int &j) {
  return MAX(i++, j); // Non-compliant
}
