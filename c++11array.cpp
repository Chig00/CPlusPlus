#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <ctime>

bool sorter(int x, int y) {
	return x < y;
}

int main() {
	std::array<int, 10> ints;
	
	std::mt19937 gen (time(NULL));
	std::uniform_int_distribution<int> dist (1, 100);
	
	for (int i = 0; i < 10; i++) {
		ints[i] = dist(gen);
	}
	
	for (int i = 0; i < 10; i++) {
		std::cout << ints[i] << ' ';
	}
	
	std::cout << '\n';
	
	std::shuffle(ints.begin(), ints.end(), gen);
	
	for (int i = 0; i < 10; i++) {
		std::cout << ints[i] << ' ';
	}
	
	std::cout << '\n';
	
	std::sort(ints.begin(), ints.end(), sorter);
	
	for (int i = 0; i < 10; i++) {
		std::cout << ints[i] << ' ';
	}
	
	std::cout << '\n';
}