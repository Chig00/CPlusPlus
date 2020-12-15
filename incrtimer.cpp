#include <iostream>
#include <ctime>

int main() {
  std::cout << "Increments: ";
  int increments;
  std::cin >> increments;

  int time0 = clock();
  for (int i = 0; i < increments; i++) {}
  int time1 = clock();

  double time_taken = (double) (time1 - time0) / CLOCKS_PER_SEC;

  std::cout << "It took " << time_taken << " seconds to increment " << increments << " times." << std::endl;

  return 0;
}