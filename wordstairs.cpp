#include <iostream>
#include <string>

int main() {
  std::cout << "Word: ";
  std::string word;
  std::cin >> word;
  int size = word.size();

  for (int i = 1; i <= size; i++) {
    for (int j = 0; j < size - i; j++) {
      std::cout << ' ';
    }

    for (int j = 0; j < i; j++) {
      std::cout << word[j];
    }

    std::cout << std::endl;
  }

  return 0;
}