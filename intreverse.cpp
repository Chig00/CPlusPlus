#include <iostream> // std::cout, std::cin
#include <limits> // std::numeric_limits::max()
#include <cmath> // pow()

// The integer's digit count is calculated by comparing it to sequentially greater powers of 10
int digit_calc(int integer) {
	for (int i = 1;; i++) {
		if (integer < pow(10, i)) {
			return i;
		}
	}
}

// An integer inputted is reversed using numerical functions
int main() {
	// An integer is obtained from stdin
	std::cout << "Integer: ";
	int integer;
	std::cin >> integer;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	// The number of digits the integer has is calculated
	int digits = digit_calc(integer);
	// The reversed number is initialised at zero for incrementation
	int reversed = 0;
	
	for (int i = 0; i < digits; i++) {
		// The integer's current unit digit is found and stored
		int unit = integer - integer / 10 * 10;
		// The unit is added to the end of the reversed number
		reversed *= 10;
		reversed += unit;
		// The integer is shifted down a digit
		integer /= 10;
	}
	
	// The reversed integer is displayed
	std::cout << reversed << '\n';
}