#include <iostream>
#include <ctime>
#include <cstdio>

int main() {
  std::cout << "How many times should C++ be printed? ";
  int times;
  std::cin >> times;

  int time0 = clock();

  for (int i = 0; i < times; i++) {
    std::cout << "C++" << std::endl;
  }

  int time1 = clock();

  for (int i = 0; i < times; i++) {
    printf("C++\n");
  }

  int time2 = clock();

  double time_taken1 = (double) (time1 - time0) / CLOCKS_PER_SEC;
  double time_taken2 = (double) (time2 - time1) / CLOCKS_PER_SEC;

  std::cout << "It took " << time_taken1 << " seconds to print C++ " << times << " times with std::cout and std::endl." << std::endl;
  std::cout << "It took " << time_taken2 << " seconds to print C++ " << times << " times with printf() and \\n." << std::endl;

  return 0;
}