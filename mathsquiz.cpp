#include <iostream>
#include <limits>
#include <random>
#include <ctime>

const int SUM_MIN = 0;
const int SUM_MAX = 50;
const int PRODUCT_MIN = 1;
const int PRODUCT_MAX = 12;
const int QUESTION_COUNT = 20;
const int MODE_COUNT = 4;

int main() {
	std::mt19937 generator(time(NULL));
	std::uniform_int_distribution<int> distribution(SUM_MIN, SUM_MAX);
	std::uniform_int_distribution<int> distribution2(PRODUCT_MIN, PRODUCT_MAX);
	char again = 'y';
	
	while (again == 'y' || again == 'Y') {
		int score = 0;
		
		for (int i = 0; i < QUESTION_COUNT; i++) {
			std::cout << "Question " << i + 1 << ":\n";
			
			int x;
			int y;
			int z;
			char operation;
			
			switch (i % MODE_COUNT) {
				case 0:
					x = distribution(generator);
					y = distribution(generator);
					z = x + y;
					operation = '+';
					break;
				case 1:
					y = distribution(generator);
					z = distribution(generator);
					x = y + z;
					operation = '-';
					break;
				case 2:
					x = distribution2(generator);
					y = distribution2(generator);
					z = x * y;
					operation = '*';
					break;
				case 3:
					y = distribution2(generator);
					z = distribution2(generator);
					x = y * z;
					operation = '/';
			}
			
			int answer;
			std::cout << x << " " << operation << " " << y << " = ";
			std::cin >> answer;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			if (answer == z) {
				score++;
				std::cout << "Correct!\n" << "Score: " << score << '/' << i + 1 << '\n';
			}
			
			else {
				std::cout << "Incorrect...\n" << "Correct answer: " << z << '\n'
					<< "Score: " << score << '/' << i + 1 << '\n';
			}
			
			std::cout << '\n';
		}
		
		std::cout << "Final score: " << score << '/' << QUESTION_COUNT << '\n'
			<< 100 * score / QUESTION_COUNT << "%\n" << "Try again (y/n)? ";
		std::cin >> again;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	return 0;
}