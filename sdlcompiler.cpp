#include <iostream>
#include <string>
#include <cstdlib>

int main() {
	std::cout << "C++ file name (excluding the extension): ";
	std::string file_name;
	std::cin >> file_name;
	std::cout << "C++ file extension (including the dot): ";
	std::string extension;
	std::cin >> extension;
	std::string command = "g++ " + file_name + extension + " -l mingw32 -l SDL2main -l SDL2 -o "
	                      + file_name + ".exe";
	system(command.c_str());
	return 0;
}