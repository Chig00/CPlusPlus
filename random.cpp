#include <iostream>
#include <random>
#include <ctime>

int main() {
  std::mt19937 generator(time(NULL));
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (int i=0; i<100; i++) {
    std::cout << distribution(generator) << std::endl;
  }
  return 0;
}