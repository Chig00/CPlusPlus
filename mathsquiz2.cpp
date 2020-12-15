#include <iostream>
#include <limits>
#include <random>
#include <ctime>

const int MODE_COUNT = 4;

int main() {
	std::mt19937 generator(time(NULL));
	
	while (true) {
		int question_count;
		int sum_min;
		int sum_max;
		int product_min;
		int product_max;
		double time_max;
		
		std::cout << "Number of question sets: ";
		std::cin >> question_count;
		question_count *= MODE_COUNT;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "Summation range: ";
		std::cin >> sum_min >> sum_max;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "Product range: ";
		std::cin >> product_min >> product_max;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "Time limit: ";
		std::cin >> time_max;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::uniform_int_distribution<int> distribution(sum_min, sum_max);
		std::uniform_int_distribution<int> distribution2(product_min, product_max);
		char again = 'y';
		
		std::cout << '\n';
		
		while (again == 'y' || again == 'Y') {
			int score = 0;
			
			for (int i = 0; i < question_count; i++) {
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
						y = y ? y : 1;
						z = distribution2(generator);
						x = y * z;
						operation = '/';
				}
				
				std::cout << x << " " << operation << " " << y << " = ";
				int start = clock();
				int answer;
				std::cin >> answer;
				int end = clock();
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				
				double time = (double) (end - start) / CLOCKS_PER_SEC;
				
				if (answer == z) {
					if (time > time_max) {
						std::cout << "Too slow...\nScore: " << score << '/' << i + 1 << '\n';
					}
					
					else {
						score++;
						std::cout << "Correct!\nScore: " << score << '/' << i + 1 << '\n';
					}
				}
				
				else {
					std::cout << "Incorrect...\nCorrect answer: " << z << '\n'
						<< "Score: " << score << '/' << i + 1 << '\n';
				}
				
				std::cout << '\n';
			}
			
			std::cout << "Final score: " << score << '/' << question_count << " ("
				<< 100 * score / question_count << "%)\nTry again (y/n)? ";
			std::cin >> again;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			std::cout << '\n';
		}
	}
	
	return 0;
}