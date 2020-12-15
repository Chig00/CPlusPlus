#include <iostream>

#define STAIR 'X'
#define EMPTY ' '

void build (int size) {
  for (int i=1; i<=size; i++) {
    for (int j=size; j>i; j--) {
      std::cout << EMPTY;
    }
    for (int j=0; j<i; j++) {
      std::cout << STAIR;
    }
    std::cout << std::endl;
  }
}

int main() {
  int size;
  std::cout << "Staircase size? ";
  std::cin >> size;
  build(size);
}