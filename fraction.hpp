#include <string>
#include <sstream>
#include <cstdlib>
#include <exception>

/**
 * A class to represent real rational fractions.
 */
class Fraction {
	public:
		/**
		 * Constructs a fraction using the given parameters.
		 * The fraction is simplified to its simplest form.
		 * The fraction may be imaginary.
		 * The fraction can be a multiple of a power of pi or e.
		 */
		Fraction(
			int num = 0,
			int denom = 1
		) {
			set(num, denom);
		}
		
		/**
		 * Sets the fraction's numerator and denominator.
		 * Converts the fraction to its simplest form.
		 */
		void set(int num, int denom) {
			if (!denom) {
				throw std::invalid_argument("Undefined Fraction Error.");
			}
			
			if (!num) {
				denom = 1;
			}
			
			numerator = num;
			denominator = denom;
			
			if (denominator < 0) {
				numerator *= -1;
				denominator *= -1;
			}
			
			for (int i = 2; i <= abs(numerator) && i <= denominator; i++) {
				if (!(numerator % i) && !(denominator % i)) {
					numerator /= i;
					denominator /= i;
					i--;
				}
			}
		}
		
		/**
		 * Returns the result of adding the given fraction with this one.
		 */
		Fraction operator+(const Fraction& fraction) const noexcept {
			Fraction new_fraction(*this);
			new_fraction += fraction;
			
			return new_fraction;
		}
		
		/**
		 * Adds the given fraction to this one.
		 */
		Fraction& operator+=(const Fraction& fraction) noexcept {
			set(
				numerator * fraction.denominator
				+ fraction.numerator * denominator,
				denominator * fraction.denominator
			);
			
			return *this;
		}
		
		/**
		 * Returns the result of subtracting the given fraction from this one.
		 */
		Fraction operator-(const Fraction& fraction) const noexcept {
			Fraction new_fraction(*this);
			new_fraction -= fraction;
			
			return new_fraction;
		}
		
		/**
		 * Subtracts the given fraction from this one.
		 */
		Fraction& operator-=(const Fraction& fraction) noexcept {
			set(
				numerator * fraction.denominator
				- fraction.numerator * denominator,
				denominator * fraction.denominator
			);
			
			return *this;
		}
		
		/**
		 * Returns the result of multiplying the given fraction with this one.
		 */
		Fraction operator*(const Fraction& fraction) const noexcept {
			Fraction new_fraction(*this);
			new_fraction *= fraction;
			
			return new_fraction;
		}
		
		/**
		 * Multiplies the given fraction with this one.
		 */
		Fraction& operator*=(const Fraction& fraction) noexcept {
			set(
				numerator * fraction.numerator,
				denominator * fraction.denominator
			);
			
			return *this;
		}
		
		/**
		 * Returns the result of dividing this fraction by the given one.
		 */
		Fraction operator/(const Fraction& fraction) const {
			Fraction new_fraction(*this);
			new_fraction /= fraction;
			
			return new_fraction;
		}
		
		/**
		 * Divides this fraction by the given one.
		 */
		Fraction& operator/=(const Fraction& fraction) {
			set(
				numerator * fraction.denominator,
				denominator * fraction.numerator
			);
			
			return *this;
		}
		
		/**
		 * Returns the fraction in string form.
		 */
		std::string to_string() const noexcept {
			std::stringstream stream;
			stream << numerator;
			
			if (denominator != 1) {
				stream << '/' << denominator;
			}
			
			return stream.str();
		}
		
		/**
		 * Returns the fraction in string form.
		 * The fraction is put in the form of a mixed number if applicable.
		 */
		std::string to_mixed() const noexcept {
			std::stringstream stream;
			
			if (numerator) {
				int whole = numerator / denominator;
				int remainder = abs(numerator) % denominator;
				
				if (whole) {
					stream << whole << ' ';
				}
				
				else if (numerator < 0) {
					stream << '-';
				}
				
				if (remainder) {
					stream << remainder;
				}
				
				if (denominator != 1) {
					stream << '/' << denominator;
				}
			}
			
			else {
				stream << 0;
			}
			
			return stream.str();
		}
		
	private:
		int numerator;   // The value of the numerator.
		int denominator; // The value of the denominator.
};

/**
 * Allows the fraction's value to be outputted.
 */
std::ostream& operator<<(std::ostream& ostream, const Fraction& fraction) noexcept {
	return ostream << fraction.to_string();
}

/**
 * Allows the fraction's value to be inputted.
 */
std::istream& operator>>(std::istream& istream, Fraction& fraction) {
	int numerator;
	int denominator;
	istream >> numerator >> denominator;
	fraction.set(numerator, denominator);
	
	return istream;
}