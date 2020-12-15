#include <iostream>
#include <limits>
#include <array>
#include <random>
#include <ctime>

constexpr bool MANUAL = false;
constexpr int TRIALS = 100000;
constexpr int LEVEL = 3;

/**
 * A class that defines the Rock, Paper, Scissors bot.
 * The bot aims to learn the habits of its opponent to
 *   win in rock, paper, scissors more often.
 */
class RPSBot {
	public:
		/**
		 * Initialises the scores and the data to zero.
		 */
		RPSBot() noexcept:
			scores(),
			data(),
			generator(time(nullptr)),
			distribution(0, 1)
		{}
		
		/**
		 * Displays the scores using standard output.
		 */
		void display_scores() const noexcept {
			std::cout
				<< "\nScores: "
				<< scores[0]
				<< " - "
				<< scores[1]
				<< std::endl
			;
		}
		
		/**
		 * Plays a round of rock, paper, scicssors
		 *   using the user's given choice.
		 * The results of the round are displayed using standard output.
		 * The scores are updated according to the results.
		 */
		void play(int choice) noexcept {
			// The user's choice is displayed.
			std::cout
				<< "\nYou chose "
				<< string(choice)
				<< "!\n"
			;
			
			// The bot makes its choice.
			int counter = get_choice();
			
			// The bot's choice is displayed.
			std::cout
				<< "\nThe computer chose "
				<< string(counter)
				<< "!\n"
			;
			
			// The results are calculated and displayed.
			int result = (3 + choice - counter) % 3;
			
			if (result == 1) {
				std::cout << "\nYou win!\n";
				scores[0]++;
			}
			
			else if (result == 2) {
				std::cout << "\nYou lost...\n";
				scores[1]++;
			}
			
			else {
				std::cout << "\nIt's a tie.\n";
			}
			
			// The data is updated after the round.
			update(choice, counter);
		}
		
	private:
		/**
		 * Returns the integer choice in string form.
		 * 0 -> Rock
		 * 1 -> Paper
		 * 2 -> Scissors
		 */
		std::string string(int choice) const noexcept {
			switch (choice) {
				case 0:
					return "rock";
					
				case 1:
					return "paper";
				
				case 2:
					return "scissors";
			}
			
			return "";
		}
		
		/**
		 * Updates the computer's databases.
		 */
		void update(int choice, int counter) noexcept {
			// Data is not recorded on the first round.
			if (last_choice >= 0 && last_counter >= 0) {
				data[last_choice][last_counter][(choice + 1) % 3]++;
			}
			
			// The choice combination itself is stored
			//   for reference in the next round.
			last_choice = choice;
			last_counter = counter;
		}
		
		/**
		 * Returns the computer's choice.
		 */
		int get_choice() noexcept {
			// The choice meant to counter the user.
			int counter;
			
			// If a round has been played before, the optimal choice is found.
			if (last_choice >= 0 && last_counter >= 0) {
				// The total number of rounds played with the
				//   combination of previous choices is calculated.
				int total =
					data[last_choice][last_counter][0]
					+ data[last_choice][last_counter][1]
					+ data[last_choice][last_counter][2]
				;
			
				// If this specific last choice combination has been
				//   played before, the bot tried to counter the user.
				if (total) {
					counter = total * distribution(generator);
						
					for (int i = 0; i < 3; i++) {
						if (counter < data[last_choice][last_counter][i]) {
							counter = i;
							break;
						}
						
						else {
							counter -= data[last_choice][last_counter][i];
						}
					}
				}
				
				// Else, a completely random choice is made.
				else {
					counter = 3 * distribution(generator);
				}
			}
			
			// Else, a completely random choice is made.
			else {
				counter = 3 * distribution(generator);
			}
			
			return counter;
		}
		
		std::array<int, 2> scores;                     // The scores of the user and bot.
		std::mt19937 generator;                        // The RNG.
		std::uniform_real_distribution<> distribution; // The RNG distribution.
		std::array<
			std::array<
				std::array<
					int,
					3
				>,
				3
			>,
			3
		> data;                                        // The bot's data stores.
		int last_choice = -1;                          // The user's last choice.
		int last_counter = -1;                         // The bot's last choice.
};

/**
 * Tests the Rock Paper Scissors bot against a human or another bot.
 */
int main() {
	RPSBot bot;
	std::array<unsigned long, LEVEL> variables{};
	
	for (int i = 0; i < TRIALS; i++) {
		bot.display_scores();
		
		std::cout << "\nRock (0), paper (1), scissors (2), or quit (-1)? ";
		int choice;
		
		if (MANUAL) {
			std::cin >> choice;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		else {
			choice = variables[0] % 3;
			
			for (int j = LEVEL - 1; j >= 0; j--) {
				if (j == LEVEL - 1) {
					variables[j]++;
				}
				
				else {
					variables[j] += variables[j + 1];
				}
			}
		}
		
		if (0 <= choice && choice <= 2) {
			bot.play(choice);
		}
		
		else if (choice == -1) {
			break;
		}
		
		else {
			std::cout << "\nInvalid input.\n";
		}
	}
	
	return 0;
}