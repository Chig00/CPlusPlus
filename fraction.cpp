#include <iostream>
#include <array>
#include <limits>
#include "fraction.hpp"

/**
 * A program to showcase the features of the Fraction class.
 */
int main() {
	// Constructing fractions may throw exceptions.
	try {
		// An array of fractions is declared.
		std::array<Fraction, 2> fractions;
		
		// The first fraction is initialised.
		std::cout << "\nFirst fraction (num denom): ";
		std::cin >> fractions[0];
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		// The second fraction is initialised.
		std::cout << "Second fraction (num denom): ";
		std::cin >> fractions[1];
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		// The sum of the two fractions is displayed.
		std::cout
			<< std::endl
			<< fractions[0] // Summand
			<< " + "
			<< fractions[1] // Summand
			<< " = "
			<< (fractions[0] + fractions[1]) // Sum
			<< std::endl
		;
		
		// The sum of the two fractions is displayed in mixed form.
		std::cout
			<< fractions[0].to_mixed() // Summand
			<< " + "
			<< fractions[1].to_mixed() // Summand
			<< " = "
			<< (fractions[0] + fractions[1]).to_mixed() // Sum
			<< std::endl
		;
		
		// The difference between the two fractions is displayed.
		std::cout
			<< std::endl
			<< fractions[0] // Minuend
			<< " - "
			<< fractions[1] // Subtrahend
			<< " = "
			<< (fractions[0] - fractions[1]) // Difference
			<< std::endl
		;
		
		// The difference between the two fractions is displayed in mixed form.
		std::cout
			<< fractions[0].to_mixed() // Minuend
			<< " - "
			<< fractions[1].to_mixed() // Subtrahend
			<< " = "
			<< (fractions[0] - fractions[1]).to_mixed() // Difference
			<< std::endl
		;
		
		// The product of the two fractions is displayed.
		std::cout
			<< std::endl
			<< fractions[0] // Factor
			<< " * "
			<< fractions[1] // Factor
			<< " = "
			<< (fractions[0] * fractions[1]) // Product
			<< std::endl
		;
		
		// The product of the two fractions is displayed in mixed form.
		std::cout
			<< fractions[0].to_mixed() // Factor
			<< " * "
			<< fractions[1].to_mixed() // Factor
			<< " = "
			<< (fractions[0] * fractions[1]).to_mixed() // Product
			<< std::endl
		;
		
		// The quotient of the two fractions is displayed.
		std::cout
			<< std::endl
			<< fractions[0] // Dividend
			<< " / "
			<< fractions[1] // Divisor
			<< " = "
			<< (fractions[0] / fractions[1]) // Quotient
			<< std::endl
		;
		
		// The quotient of the two fractions is displayed in mixed form.
		std::cout
			<< fractions[0].to_mixed() // Dividend
			<< " / "
			<< fractions[1].to_mixed() // Divisor
			<< " = "
			<< (fractions[0] / fractions[1]).to_mixed() // Quotient
			<< std::endl
		;
	}
	
	catch (const std::exception& exception) {
		std::cout << std::endl << exception.what() << std::endl;
	}
	
	return 0;
}