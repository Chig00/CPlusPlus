#include <iostream>
#include <random>
#include <ctime>

#define LOW_VALUE 1
#define HIGH_VALUE 100
#define TEST_LENGTH 10
#define SCORE_MULTIPLIER 100

int main() {
	int marks = 0;
	int x;
	int y;
	int z;
	int answer;
	char xy_operator;
	
	std::mt19937 generator(time(NULL));
	std::uniform_int_distribution<int> distribution(LOW_VALUE, HIGH_VALUE);
	std::uniform_int_distribution<int> distribution2(0, 1);
	
	int times[2];
	times[0] = clock();
	for (int i = 0; i < TEST_LENGTH; i++) {
		x = distribution(generator);
		y = distribution(generator);
		
		if (distribution2(generator)) {
			z = x + y;
			xy_operator = '+';
		}
		else {
			z = x - y;
			xy_operator = '-';
		}
		
		std::cout << x << ' ' << xy_operator << ' ' << y << " = ";
		if (i != 0) {
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		std::cin >> answer;
		
		if (answer == z) {
			marks++;
			std::cout << "Correct!" << std::endl;
		}
		else {
			std::cout << "Incorrect..." << std::endl
			          << "The correct answer is " << z << '.' << std::endl;
		}
	}
	times[1] = clock();
	
	double time_taken = (double) (times[1] - times[0]) / CLOCKS_PER_SEC;
	double score = SCORE_MULTIPLIER * marks / time_taken;
	
	std::cout << "Your score is: " << score << '!' << std::endl;
	
	return 0;
}