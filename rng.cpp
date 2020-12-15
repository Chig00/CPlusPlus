#include <iostream>
#include <random>
#include <string>

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::string type;
  double lb;
  double ub;
  int number;

  while (true) {
    std::cout << "Integer (i) or decimal (d) random number? (Quit with q) ";
    std::cin >> type;

    if (type == "q") {
      break;
    }

    std::cout << "Lower bound of values desired: ";
    std::cin >> lb;
    std::cout << "Upper bound of values desired: ";
    std::cin >> ub;
    std::cout << "Number of values desired: ";
    std::cin >> number;

    if (type == "i") {
      std::uniform_int_distribution<int> dist((int) lb, (int) ub);
      for (int i=0; i<number; i++) {
        std::cout << dist(gen) << std::endl;
      }
    }

    else if (type == "d") {
      std::uniform_real_distribution<double> dist(lb, ub);
      for (int i=0; i<number; i++) {
        std::cout << dist(gen) << std::endl;
      }
    }
  }

  return 0;
}
