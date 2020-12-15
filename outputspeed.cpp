#include <cstdio>
#include <iostream>
#include <ctime>

#define PRINTS 1000

double get_time() {
	return (double) clock() / CLOCKS_PER_SEC;
}

int main() {
	double time_points[5];
	time_points[0] = get_time();
	for (int i = 0; i < PRINTS; i++) {
		puts("C++\n");
	}
	time_points[1] = get_time();
	for (int i = 0; i < PRINTS; i++) {
		printf("C++\n");
	}
	time_points[2] = get_time();
	for (int i = 0; i < PRINTS; i++) {
		std::cout << "C++\n";
	}
	time_points[3] = get_time();
	for (int i = 0; i < PRINTS; i++) {
		std::cout << "C++" << std::endl;
	}
	time_points[4] = get_time();
	
	printf("puts() took %f seconds to print %d times.\n", time_points[1] - time_points[0], PRINTS);
	printf("printf() took %f seconds to print %d times.\n", time_points[2] - time_points[1], PRINTS);
	printf("std::cout took %f seconds to print %d times.\n", time_points[3] - time_points[2], PRINTS);
	printf("std::cout with std::endl took %f seconds to print %d times.\n", time_points[4] - time_points[3], PRINTS);
	
	return 0;
}