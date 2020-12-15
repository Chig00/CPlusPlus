#include <iostream>
#include <string>
#include <random>
#include <ctime>

/* common: a-m
 * uncommon: n-t
 * rare: u-w
 * epic: x&y
 * legendary: z
 * Each item is 10x rarer than an item in the previous rarity
 */

class Inventory {
	public:
		Inventory() {
			items = "abcdefghijklmnopqrstuvwxyz";
			
			for (int i = 0; i < 26; i++) {
				counts[i] = 0;
				
				if (i < 13) {
					subs[i] = 10000;
				}
				else if (i < 20) {
					subs[i] = 1000;
				}
				else if (i < 23) {
					subs[i] = 100;
				}
				else if (i < 25) {
					subs[i] = 10;
				}
				else if (i == 25) {
					subs[i] = 1;
				}
			}
		}
		
		void display() {
			for (int i = 0; i < 26; i++) {
				std::cout << items[i] << ": " << counts[i] << std::endl;
			}
		}
		
		void open_packs(int number) {
			for (int i = 0; i < number; i++) {
				open_pack();
			}
		}
		
		void collect_all() {
			for (int i = 0;; i++) {
				open_pack();
				
				if (full_collection()) {
					std::cout << "It took you " << i << " pack openings to get all of the items." << std::endl;
					break;
				}
			}
		}
		
	private:
		std::string items;
		int counts[26];
		int subs[26];
		
		void open_pack() {
			static std::mt19937 generator(time(NULL));
			std::uniform_int_distribution<int> distribution(1, 1 + 2 * 10 + 3 * 100 + 7 * 1000 + 13 * 10000);
			int number = distribution(generator);
			
			for (int i = 25; i > -1; i--) {
				number -= subs[i];
				if (number <= 0) {
					counts[i]++;
					break;
				}
			}
		}
		
		bool full_collection() {
			for (int i = 0; i < 26; i ++) {
				if (counts[i] == 0) {
					return false;
				}
			}
			
			return true;
		}
};

void reset_input() {
	std::cin.clear();
	std::cin.ignore(999, '\n');
}

int main() {
	Inventory inventory;
	char option;
	int number;
	bool looped = false;
	
	while (true) {
		if (looped) {
			reset_input();
		}
		else {
			looped = true;
		}
		
		std::cout << "What do you want to do? Open packs (o), display inventory (d), or quit (q)? ";
		std::cin >> option;
		
		if (option == 'o') {
			std::cout << "How many packs should be opened? (-1 to complete collection) ";
			reset_input();
			std::cin >> number;
			if (number == -1) {
				inventory.collect_all();
			}
			else {
				inventory.open_packs(number);
			}
		}
		else if (option == 'd') {
			inventory.display();
		}
		else if (option == 'q') {
			break;
		}
		else {
			std::cerr << "Please use correct input.";
		}
	}
	
	return 0;
}