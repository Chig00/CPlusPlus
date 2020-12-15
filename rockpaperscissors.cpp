#include <iostream>
#include <string>
#include <random>
#include <ctime>

int main() {
	std::mt19937 generator(time(NULL));
	std::uniform_int_distribution<int> distribution(0, 2);
	int score = 0;
	char choice;
	int choice_int;
	int comp_choice;
	std::string word;
	bool full_loop = false;
	
	while (true) {
		if (full_loop) {
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else {
			full_loop = true;
		}
		
		std::cout << "Rock (r), paper (p), or scissors (s)? ";
		std::cin >> choice;
		
		if (choice == 'r') {
			choice_int = 0;
		}
		else if (choice == 'p') {
			choice_int = 1;
		}
		else if (choice == 's') {
			choice_int = 2;
		}
		else if (choice == 'q') {
			break;
		}
		else {
			std::cerr << "Please use r, p, or s." << std::endl;
			continue;
		}
		
		comp_choice = distribution(generator);
		if (comp_choice == 0) {
			word = "rock";
		}
		else if (comp_choice == 1) {
			word = "paper";
		}
		else if (comp_choice == 2) {
			word = "scissors";
		}
		std::cout << "The computer chose " << word << '!' << std::endl;
		
		if (choice_int - comp_choice == 0) {
			std::cout << "It's a tie!" << std::endl;
		}
		else if (choice_int - comp_choice == 1 || choice_int - comp_choice == -2) {
			std::cout << "You win!" << std::endl;
			score++;
		}
		else if (choice_int - comp_choice == -1 || choice_int - comp_choice == 2) {
			std::cout << "You lose!" << std::endl;
			score--;
		}
		
		std::cout << "Your score is " << score << '!' << std::endl;
	}
	
	return 0;
}