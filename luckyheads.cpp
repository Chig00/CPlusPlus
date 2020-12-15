#include <iostream>
#include <random>
#include <ctime>

int main () {
  std::cout << "Heads in a row: ";
  int heads;
  std::cin >> heads;
  std::mt19937 generator (time (NULL));
  std::uniform_int_distribution<int> distribution (0, 1);
  int count = 1;
  for (int i = 0; i < heads; i++) {
    if (distribution (generator)) {
      i = -1;
      count++;
    }
  }
  std::cout << "It took " << count << " attempts to get " << heads << " heads." << std::endl;
  return 0;
}