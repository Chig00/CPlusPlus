#include <iostream>
#include <cmath>

int main() {
	double x;
	double y;
	char op;
	double result;
	bool full_loop = false;
	char quit;
	
	while (true) {
		if (full_loop) {
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else {
			full_loop = true;
		}
		
		std::cout << "x, operation, y: ";
		std::cin >> x >> op >> y;
	
		if (op == '+') {
			result = x + y;
		}
		else if (op == '-') {
			result = x - y;
		}
		else if (op == '*') {
			result = x * y;
		}
		else if (op == '/') {
			result = x / y;
		}
		else if (op == '^') {
			result = pow(x, y);
		}
		else {
			std::cin.clear();
			std::cin.ignore(999, '\n');
			
			std::cout << "Quit? (y/n) ";
			std::cin >> quit;
			
			if (quit == 'y') {
				break;
			}
			else {
				continue;
			}
		}
	
		std::cout << x << ' ' << op << ' ' << y << " = " << result << std::endl;
	}
	
	return 0;
}