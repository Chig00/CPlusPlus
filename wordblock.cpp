#include <iostream>
#include <string>

int main() {
  std::cout << "Word: ";
  std::string word;
  std::cin >> word;
  int size = word.size();

  for (int i = 0; i < size; i++) {
    for (int j = i; j < size; j++) {
      std::cout << word[j];
    }
    for (int j = 0; j < i; j++) {
      std::cout << word[j];
    }

    std::cout << std::endl;
  }

  return 0;
}