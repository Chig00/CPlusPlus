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
	std::string command = "g++ -o " + file_name + ".exe " + file_name + extension;
	system(command.c_str());
	return 0;
}