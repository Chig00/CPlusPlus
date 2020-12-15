#include <iostream>
#include "datastructures.hpp"

int main() {
	int values[] = {0, 1, 2, 3, 4};
	DoublyLinkedList<int>* list = new DoublyLinkedList<int>(values, 5);
	
	for (int i = 0; i < 5; i++) {
		std::cout << list->iterate() << " ";
	}
	
	std::cout << "\n";
	
	list->prepend(-1);
	
	for (int i = 0; i < 6; i++) {
		std::cout << list->iterate() << " ";
	}
	
	std::cout << "\n";
	
	list->insert(5, 2);
	
	for (int i = 0; i < 7; i++) {
		std::cout << list->iterate() << " ";
	}
	
	std::cout << "\n";
	
	list->insert(6, 5);
	
	for (int i = 0; i < 8; i++) {
		std::cout << list->iterate() << " ";
	}
	
	std::cout << "\n";
	
	list->remove(2);
	list->remove(4);
	list->remove(0);
	
	for (int i = 0; i < 5; i++) {
		std::cout << list->iterate() << " ";
	}
	
	std::cout << "\n";
	
	delete list;
	
	return 0;
}