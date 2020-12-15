#include <iostream>
#include <array>
#include <limits>
#include <algorithm>
#include <string>
#include <ctime>
#include <random>

const int WARRIOR_COUNT = 14;
const double MIN_MULTI = 0.8;
const double MAX_MULTI = 1.2;

struct Warrior {
	void set(int code, int t) {
		charge = 0;
		alive = true;
		team = t + 1;
		
		switch (code) {
			case 0:
				name = "Midi";
				title = "Bane Of The Blood Star";
				hp = 1000;
				atk = 100;
				spd = 100;
				cost = 3;
				atk_name = "Haemlik's Blade";
				spcl_name = "Cursed Combo";
				spcl_desc = "Attack with 4x power";
				break;
				
			case 1:
				name = "Lenna";
				title = "Star Slayer";
				hp = 750;
				atk = 110;
				spd = 110;
				cost = 5;
				atk_name = "Cosmic Blade";
				spcl_name = "Astral Slash";
				spcl_desc = "Attack with 6x power";
				break;
				
			case 2:
				name = "Hoshi";
				title = "Child Of The Blood Star";
				hp = 800;
				atk = 125;
				spd = 125;
				cost = 4;
				atk_name = "Star Slice";
				spcl_name = "Star Storm";
				spcl_desc = "Attack all opponents with 1.5x power";
				break;
				
			case 3:
				name = "Gozi";
				title = "The Ascended";
				hp = 1025;
				atk = 95;
				spd = 160;
				cost = 3;
				atk_name = "Star Beam";
				spcl_name = "Fell Star";
				spcl_desc = "Attack all opponents and reduce their power by 10%";
				break;
				
			case 4:
				name = "Eizo";
				title = "The Fallen";
				hp = 1000;
				atk = 90;
				spd = 90;
				cost = 3;
				atk_name = "Star Pulse";
				spcl_name = "Ascension Star";
				spcl_desc = "Attack after doubling power and speed";
				break;
				
			case 5:
				name = "Rex";
				title = "Conqueror Of Midvar";
				hp = 1250;
				atk = 75;
				spd = 25;
				cost = 5;
				atk_name = "King's Sword";
				spcl_name = "Kings' Shield";
				spcl_desc = "Shield the team for 20% of each warrior's max HP";
				break;
				
			case 6:
				name = "Nixus";
				title = "The Conqueror's General";
				hp = 1350;
				atk = 95;
				spd = 15;
				cost = 3;
				atk_name = "Alondale";
				spcl_name = "Nightfall";
				spcl_desc = "Attack with extra power equal to the half of the target's lost HP";
				break;
				
			case 7:
				name = "Anne";
				title = "The Shadow Assassin";
				hp = 750;
				atk = 75;
				spd = 150;
				cost = 1;
				atk_name = "Needler";
				spcl_name = "Poison Dart";
				spcl_desc = "Attack with extra power equal to the 15% of the target's max HP";
				break;
				
			case 8:
				name = "Maria";
				title = "The Conqueror's Mage";
				hp = 600;
				atk = 200;
				spd = 85;
				cost = 2;
				atk_name = "Ethereal Flare";
				spcl_name = "Ethereal Incineration";
				spcl_desc = "Attack with 2x power";
				break;
				
			case 9:
				name = "Pyro";
				title = "The Red Giant";
				hp = 900;
				atk = 150;
				spd = 65;
				cost = 5;
				atk_name = "Solar Flare";
				spcl_name = "Solar Incineration";
				spcl_desc = "Attack all opponents with 1.5x power";
				break;
				
			case 10:
				name = "Nimbus";
				title = "Heir To The Sky";
				hp = 600;
				atk = 150;
				spd = 150;
				cost = 2;
				atk_name = "Twister";
				spcl_name = "Hurricane";
				spcl_desc = "Attack all opponents";
				break;
				
			case 11:
				name = "Aeolus";
				title = "Lord Of The Sky";
				hp = 1150;
				atk = 95;
				spd = 105;
				cost = 1;
				atk_name = "Divine Wind";
				spcl_name = "Tailwind Strike";
				spcl_desc = "Attack and double the team's speed";
				break;
				
			case 12:
				name = "Genshi";
				title = "The Shadow Of Jinshi";
				hp = 950;
				atk = 95;
				spd = 200;
				cost = 3;
				atk_name = "Shuriken Storm";
				spcl_name = "Night's Haze";
				spcl_desc = "Attack with triple power";
				break;
				
			case 13:
				name = "Gura";
				title = "The Golem Of Legend";
				hp = 2000;
				atk = 125;
				spd = 25;
				cost = 3;
				atk_name = "Hammer Smash";
				spcl_name = "Hammer Quake";
				spcl_desc = "Attack with 50% extra power";
				break;
		}
		
		max_hp = hp;
	}
	
	void turn(std::array<Warrior, 6>& warriors) {
		bool attacked = false;
		
		while (!attacked) {
			std::cout << "\nIt is " << name << "'s turn player " << team << "!\n";
			
			if (charge == cost) {
				std::cout << "Special is ready!\n";
			}
			
			std::cout << "Attack (1), Special(2), or Check Stats(3): ";
			int option;
			std::cin >> option;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << '\n';
			
			switch (option) {
				case 1:
					if (attack(warriors)) {
						attacked = true;
					}
					
					break;
					
				case 2:
					if (special(warriors)) {
						attacked = true;
					}
					
					break;
					
				case 3:
					check(warriors);
					break;
					
				default:
					std::cout << "Invalid input\n";
			}
		}
	}
	
	bool attack(std::array<Warrior, 6>& warriors) {
		for (int i = 0, j = 1; i < 6 && j < 4; i++) {
			if (warriors[i].team != team && warriors[i].alive) {
				std::cout << warriors[i].name << " (" << j << ")\n";
				j++;
			}
		}
		
		std::cout << "Target: ";
		int target;
		std::cin >> target;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		bool valid = false;
		
		for (int i = 0, j = 1; i < 6 && j < 4; i++) {
			if (warriors[i].team != team && warriors[i].alive) {
				if (target == j) {
					valid = true;
					target = i;
					break;
				}
				
				j++;
			}
		}
		
		if (!valid) {
			std::cout << "Invalid target\n";
			return false;
		}
		
		int dmg = atk * dist(gen);
		charge++;
		warriors[target].hp -= dmg;
		warriors[target].charge++;
		
		std::cout << name << " attacked " << warriors[target].name << " with " << atk_name << " and dealt " << dmg << " damage!\n";
	}
	
	bool special(std::array<Warrior, 6>& warriors) {
		std::cout << '\n' << spcl_name << '\n'
		          << spcl_desc << "\n\n";
				  
		if (charge != cost) {
			std::cout << "Insufficient charge\n";
			return false;
		}
		
		if (name == "Midi") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = 4 * atk * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
				
		else if (name == "Lenna") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = 6 * atk * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
				
		else if (name == "Hoshi") {
			std::cout << name << " used " << spcl_name << "!\n";
			
			for (int i = 0; i < 6; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					int dmg = 1.5 * atk * dist(gen);
					warriors[i].hp -= dmg;
					warriors[i].charge++;
					
					std::cout << warriors[i].name << " took " << dmg << " damage!\n";
				}
			}
		}
				
		else if (name == "Gozi") {
			std::cout << name << " used " << spcl_name << "!\n";
			
			for (int i = 0; i < 6; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					int dmg = 0.5 * atk * dist(gen);
					warriors[i].hp -= dmg;
					warriors[i].charge++;
					int drop = 0.2 * warriors[i].atk * dist(gen);
					warriors[i].atk -= drop;
					
					std::cout << warriors[i].name << " took " << dmg << " damage!\n"
							  << warriors[i].name << "'s power was reduced by " << drop << "!\n";
				}
			}
		}
				
		else if (name == "Eizo") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int atk_boost = atk * dist(gen);
			int spd_boost = spd * dist(gen);
			
			atk += atk_boost;
			spd += spd_boost;
			
			std::cout << name << " used " << spcl_name << "!\n"
					  << "Attack increased by " << atk_boost << '\n'
					  << "Speed increased by " << spd_boost << '\n';
						
			int dmg = atk * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
				
		else if (name ==  "Rex") {
			std::cout << name << " used " << spcl_name << "!\n";
			
			for (int i = 0; i < 6; i++) {
				if (warriors[i].team == team && warriors[i].alive) {
					int shield = 0.2 * warriors[i].max_hp * dist(gen);
					warriors[i].hp += shield;
					warriors[i].max_hp += shield;
					
					std::cout << warriors[i].name << " was shielded for " << shield << " shield!\n";
				}
			}
		}
				
		else if (name == "Nixus") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = (atk + warriors[target].max_hp - warriors[target].hp) * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
				
		else if (name == "Anne") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = (atk + warriors[target].max_hp * 0.15) * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
				
		else if (name == "Maria") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = 2 * atk * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
				
		else if (name == "Pyro") {
			std::cout << name << " used " << spcl_name << "!\n";
			
			for (int i = 0; i < 6; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					int dmg = 1.5 * atk * dist(gen);
					warriors[i].hp -= dmg;
					warriors[i].charge++;
					
					std::cout << warriors[i].name << " took " << dmg << " damage!\n";
				}
			}
		}
				
		else if (name == "Nimbus") {
			std::cout << name << " used " << spcl_name << "!\n";
			
			for (int i = 0; i < 6; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					int dmg = atk * dist(gen);
					warriors[i].hp -= dmg;
					warriors[i].charge++;
					
					std::cout << warriors[i].name << " took " << dmg << " damage!\n";
				}
			}
		}
				
		else if (name == "Aeolus") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = atk * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
			
			for (int i = 0; i < 6; i++) {
				if (warriors[i].team == team && warriors[i].alive) {
					int boost = warriors[i].spd * dist(gen);
					warriors[i].spd += boost;
					
					std::cout << warriors[i].name << "'s speed was boosted by " << boost << "!\n";
				}
			}
		}
				
		else if (name == "Genshi") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = 3 * atk * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
				
		else if (name == "Gura") {
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					std::cout << warriors[i].name << " (" << j << ")\n";
					j++;
				}
			}
			
			std::cout << "Target: ";
			int target;
			std::cin >> target;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			bool valid = false;
			
			for (int i = 0, j = 1; i < 6 && j < 4; i++) {
				if (warriors[i].team != team && warriors[i].alive) {
					if (target == j) {
						valid = true;
						target = i;
						break;
					}
					
					j++;
				}
			}
			
			if (!valid) {
				std::cout << "Invalid target\n";
				return false;
			}
			
			int dmg = 1.5 * atk * dist(gen);
			charge++;
			warriors[target].hp -= dmg;
			warriors[target].charge++;
			
			std::cout << name << " attacked " << warriors[target].name << " with " << spcl_name << " and dealt " << dmg << " damage!\n";
		}
		
		charge = 0;
		return true;
	}
	
	static void check(std::array<Warrior, 6> warriors) {
		for (int i = 0; i < 6; i++) {
			std::cout << "\nTeam: " << warriors[i].team << '\n'
			          << warriors[i].name << '\n'
					  << warriors[i].title << '\n'
					  << "HP: " << warriors[i].hp << " / " << warriors[i].max_hp << '\n'
					  << "Charge: " << warriors[i].charge << " / " << warriors[i].cost << '\n'
					  << "Power: " << warriors[i].atk << '\n'
					  << "Speed: " << warriors[i].spd << '\n'
					  << "Attack: " << warriors[i].atk_name << '\n'
					  << "Special: " << warriors[i].spcl_name << '\n'
					  << "         " << warriors[i].spcl_desc << '\n';
		}
	}
	
	static std::mt19937 gen;
	static std::uniform_real_distribution<double> dist;
	
	std::string name;
	std::string title;
	int max_hp;
	int hp;
	int atk;
	int spd;
	int charge;
	int cost;
	std::string atk_name;
	std::string spcl_name;
	std::string spcl_desc;
	bool alive;
	int team;
};

std::mt19937 Warrior::gen = std::mt19937 (time(NULL));
std::uniform_real_distribution<double> Warrior::dist = std::uniform_real_distribution<double> (MIN_MULTI, MAX_MULTI);

void summon(std::array<Warrior, 6>& warriors) {
	std::uniform_int_distribution<int> dist (0, WARRIOR_COUNT - 1);
	std::array<int, WARRIOR_COUNT> codes;
	
	for (int i = 0; i < WARRIOR_COUNT; i++) {
		codes[i] = i;
	}
	
	std::shuffle(codes.begin(), codes.end(), Warrior::gen);
	
	for (int i = 0; i < 6; i++) {
		warriors[i].set(codes[i], i % 2);
	}
	
	std::cout << "Player 1 summoned " << warriors[0].name << ", " << warriors[2].name << ", and " << warriors[4].name << "!\n"
	          << "Player 2 summoned " << warriors[1].name << ", " << warriors[3].name << ", and " << warriors[5].name << "!\n";
}

bool sorter(Warrior x, Warrior y) {
	return x.spd > y.spd;
}

void order(std::array<Warrior, 6>& warriors) {
	std::shuffle(warriors.begin(), warriors.end(), Warrior::gen);
	std::sort(warriors.begin(), warriors.end(), sorter);
}

int status(std::array<Warrior, 6>& warriors) {
	for (int i = 0; i < 6; i++) {
		if (warriors[i].hp <= 0 && warriors[i].alive) {
			std::cout << warriors[i].name << " has been defeated!\n";
			warriors[i].hp = 0;
			warriors[i].charge = 0;
			warriors[i].alive = false;
		}
		
		else if (warriors[i].hp > warriors[i].max_hp) {
			warriors[i].hp = warriors[i].max_hp;
		}
		
		if (warriors[i].charge > warriors[i].cost) {
			warriors[i].charge = warriors[i].cost;
		}
	}
	
	int one = 3;
	int two = 3;
	
	for (int i = 0; i < 6; i++) {
		if (!warriors[i].alive) {
			if (warriors[i].team == 1) {
				one--;
			}
			
			else {
				two--;
			}
		}
	}
	
	if (!one) {
		return 2;
	}
	
	else if (!two) {
		return 1;
	}
	
	return 0;
}

int main() {
	std::cout << "GoZi: Reborn! by Chigozie Agomo\n\n";
	std::array<Warrior, 6> warriors;
	
	while (true) {
		summon(warriors);
		
		int winner = 0;
		
		while (!winner) {
			order(warriors);
			
			for (int i = 0; i < 6; i++) {
				if (warriors[i].alive) {
					warriors[i].turn(warriors);
				}
				
				winner = status(warriors);
				
				if (winner) {
					break;
				}
			}
		}
		
		std::cout << "\nPlayer " << winner << " wins!\n\n";
	}
}