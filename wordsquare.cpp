#include <iostream>
#include <string>

int main() {
  std::cout << "Word: ";
  std::string word;
  std::cin >> word;
  int size = word.size();

  for (int i = 0; i < size; i++) {
    if (i == 0) {
      std::cout << word;
    }

    else if (i == size - 1) {
      for (int j = size - 1; j > -1; j--) {
        std::cout << word[j];
      }
    }

    else {
      std::cout << word[i];

      for (int j = 0; j < size - 2; j++) {
        std::cout << ' ';
      }

      std::cout << word[size - i - 1];
    }

    std::cout << std::endl;
  }

  return 0;
}