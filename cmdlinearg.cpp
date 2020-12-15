#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Your arguments are:\n";
	
	for (int i = 1; i < argc; i++) {
		std::cout << " - " << argv[i] << "\n";
	}
}