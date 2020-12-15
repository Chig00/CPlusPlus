#include <iostream>
#include <random>

#define MIN 0
#define MAX 100

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(MIN, MAX);

  int number = dist(gen);
  int score = 0;
  int new_number;
  char guess;

  std::cout << "The first number is " << number << "!" << std::endl;

  while (true) {
    std::cout << "Higher (h) or lower (l)? ";
    std::cin >> guess;

    while (true) {
      new_number = dist(gen);
      if (new_number != number) {
        break;
      }
    }

    std::cout << "The new number is " << new_number << std::endl;

    if (((guess == 'h') && (new_number > number)) || ((guess == 'l') && (new_number < number))) {
      std::cout << "You were correct!" << std::endl;
      std::cout << "Your score is now " << ++score << "!" << std::endl;
    }

    else {
      break;
    }

    number = new_number;
  }

  std::cout << "You were incorrect..." << std::endl;
  std::cout << "Your final score is " << score << "." << std::endl;

  return 0;
}
