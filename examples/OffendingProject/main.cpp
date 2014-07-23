#include <iostream>
#include <stdlib.h>

#define __DATE__ "TODAY"

int getSquare(int i) { return i * i; }

int main(int argc, char **argv) {
  int i;
  if (argc == 2) {
    i = atoi(argv[1]);
    std::cout << "Square of " << i << " is " << getSquare(i) << '\n';
  } else {
    std::cout << "Usage: " << argv[0] << " <number>\n";
  }
  return 0;
}
