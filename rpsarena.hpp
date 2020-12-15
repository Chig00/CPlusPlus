#include <iostream>
#include <string>
#include <limits>
#include <array>
#include <memory>
#include <random>
#include <ctime>

// The number of choices available.
constexpr int CHOICES = 3;

/**
 * An abstract base class that defines the basic requirements
 *   for an object to function as a Rock Paper Scissors bot.
 * A bot must be able to choose a number between 0 and 2
 *   (inclusively) that represents rock, paper, or scissors.
 * A bot can optionally choose to update its data with the
 *   results of the round.
 */
class RPSBot {
	public:
		/**
		 * Returns the bot's choice as an integer.
		 * 0 -> Rock
		 * 1 -> Paper
		 * 2 -> Scissors
		 */
		virtual int choose() noexcept = 0;
		
		/**
		 * Optionally updates the bot's data.
		 */
		virtual void update(int, int) noexcept {}
};

/**
 * A bot that only returns a single choice.
 */
class MonoBot: public RPSBot {
	public:
		/**
		 * Constructs a bot that only returns the given choice.
		 */
		MonoBot(int c) noexcept {
			choice = c;
		}
		
		/**
		 * Returns the given choice.
		 */
		int choose() noexcept {
			return choice;
		}
		
	private:
		int choice;
};

/**
 * A bot that makes its choices in a predefined pattern.
 * The complexity of the pattern can be defined.
 */
template <int COMPLEXITY = 1>
class PatternBot: public RPSBot {
	public:
		/**
		 * Initilialises the pattern maker.
		 */
		PatternBot(unsigned long initial = 0) noexcept {
			for (int i = 0; i < COMPLEXITY; i++) {
				pattern[i] = initial;
			}
		}
		
		/**
		 * Updates the pattern and returns the choice.
		 */
		int choose() noexcept {
			for (int i = COMPLEXITY - 1; i >= 0; i--) {
				if (i == COMPLEXITY - 1) {
					pattern[i]++;
				}
				
				else {
					pattern[i] += pattern[i + 1];
				}
			}
			
			return pattern[0] % CHOICES;
		}
		
	private:
		std::array<unsigned long, COMPLEXITY> pattern;
};

/**
 * A bot that learns the probability of the opponent
 *   making a certain choice and uses that knowledge
 *   to make better choices.
 */
class ChanceBot: public RPSBot {
	public:
		/**
		 * Seeds the RNG with the time.
		 * Sets the distribution to return results between 0 and 1.
		 * Zeroes the data.
		 */
		ChanceBot() noexcept:
			generator(time(NULL)),
			distribution(0, 1),
			data{}
		{}
		
		/**
		 * Returns a choice that aims to counter the opponent's
		 *   most likely next choice.
		 */
		int choose() noexcept {
			// The total number of rounds played with the
			//   combination of previous choices is calculated.
			int total = 0;
			
			for (int i = 0; i < CHOICES; i++) {
				total += data[i];
			}
			
			// The bot's choice.
			int choice;
		
			// If a round has been played, the bot
			//   tries to counter the opponent.
			if (total) {
				choice = total * distribution(generator);
					
				for (int i = 0; i < CHOICES; i++) {
					if (choice < data[i]) {
						choice = i;
						break;
					}
					
					else {
						choice -= data[i];
					}
				}
			}
			
			// Else, a completely random choice is made.
			else {
				choice = 3 * distribution(generator);
			}
			
			return choice;
		}
		
		/**
		 * The bot becomes more likely to choose an option
		 *   that counters the opponent's last choice.
		 */
		void update(int choice, int opposition) noexcept {
			data[(opposition + 1) % 3]++;
		}
	
	private:
		std::mt19937 generator;                        // The RNG.
		std::uniform_real_distribution<> distribution; // The RNG distribution.
		std::array<int, CHOICES> data;                 // The bot's data stores.
};

/**
 * An upgraded chance bot, that also
 *   considers the context of a choice.
 * This bot notices patterns and uses
 *   context for better predictions.
 */
class SmartBot: public RPSBot {
	public:
		/**
		 * Seeds the RNG with the time.
		 * Sets the distribution to return results between 0 and 1.
		 * Zeroes the data.
		 */
		SmartBot() noexcept:
			generator(time(NULL)),
			distribution(0, 1),
			data{}
		{}
		
		/**
		 * Returns a choice that aims to counter the opponent's
		 *   most likely next choice.
		 */
		int choose() noexcept {
			// The choice meant to counter the user.
			int choice;
			
			// If a round has been played before, a good choice may be found.
			if (last_choice >= 0 && last_opposition >= 0) {
				// The total number of rounds played with the
				//   combination of previous choices is calculated.
				int total =
					data[last_choice][last_opposition][0]
					+ data[last_choice][last_opposition][1]
					+ data[last_choice][last_opposition][2]
				;
			
				// If this specific last choice combination has been
				//   played before, the bot tries to counter the opponent.
				if (total) {
					choice = total * distribution(generator);
						
					for (int i = 0; i < 3; i++) {
						if (choice < data[last_choice][last_opposition][i]) {
							choice = i;
							break;
						}
						
						else {
							choice -= data[last_choice][last_opposition][i];
						}
					}
				}
				
				// Else, a completely random choice is made.
				else {
					choice = 3 * distribution(generator);
				}
			}
			
			// Else, a completely random choice is made.
			else {
				choice = 3 * distribution(generator);
			}
			
			return choice;
		}
		
		/**
		 * The bot becomes more likely to choose an option
		 *   that counters the opponent's last choice.
		 */
		void update(int choice, int opposition) noexcept {
			// Data is not recorded on the first round.
			if (last_choice >= 0 && last_opposition >= 0) {
				data[last_choice][last_opposition][(opposition + 1) % 3]++;
			}
			
			// The choice combination itself is stored
			//   for reference in the next round.
			last_choice = choice;
			last_opposition = opposition;
		}
	
	protected:
		std::array<
			std::array<
				std::array<
					int,
					CHOICES
				>,
				CHOICES
			>,
			CHOICES
		> data;                                        // The bot's data stores.
		int last_choice = -1;                          // The bot's last choice.
		int last_opposition = -1;                      // The opponent's last choice.
	
	private:
		std::mt19937 generator;                        // The RNG.
		std::uniform_real_distribution<> distribution; // The RNG distribution.
};

/**
 * An upgraded smart bot that prunes old data.
 * This helps if the opponent changes its approach,
 *   but hinders the bot's performance if the opponent does not.
 */
template<int MAX_DATA = 1000>
class PruneBot: public SmartBot {
	public:
		/**
		 * The bot becomes more likely to choose an option
		 *   that counters the opponent's last choice.
		 */
		void update(int choice, int opposition) noexcept {
			// If the data is full, the oldest entry is removed.
			if (data_count == MAX_DATA) {
				std::array<int, CHOICES> index;
				
				// The index is caluclated.
				for (int i = 0; i < CHOICES; i++) {
					index[i] = indices[0] % CHOICES;
					indices[0] /= CHOICES;
				}
				
				// The index is decremented.
				data[index[0]][index[1]][index[2]]--;
				
				// The index is removed to make space for the next one.
				for (int i = 0; i < MAX_DATA - 1; i++) {
					indices[i] = indices[i + 1];
				}
				
				data_count--;
			}
			
			// Data is not recorded on the first round.
			if (last_choice >= 0 && last_opposition >= 0) {
				data[last_choice][last_opposition][(opposition + 1) % 3]++;
				
				// The index of the data is stored.
				indices[data_count] =
					last_choice
					+ CHOICES * last_opposition
					+ CHOICES * CHOICES * ((opposition + 1) % 3)
				;
				
				data_count++;
			}
			
			// The choice combination itself is stored
			//   for reference in the next round.
			last_choice = choice;
			last_opposition = opposition;
		}
		
	private:
		int data_count = 0;
		std::array<int, MAX_DATA> indices; // The positions where the data were stored.
};

/**
 * A human controlled bot that inherits from RPSBot to use its interface.
 */
class HumanBot: public RPSBot {
	/**
	 * Allows the human to choose an option.
	 */
	int choose() noexcept {
		// Loop to get valid input.
		while (true) {
			// The choice is prompted for.
			std::string choice;
			std::cout << "\nRock (r), Paper (p), or Scissors (s)? ";
			std::getline(std::cin, choice);
			
			// The first character is checked.
			switch (choice[0]) {
				case 'r':
				case 'R':
					return 0;
				
				case 'p':
				case 'P':
					return 1;
				
				case 's':
				case 'S':
					return 2;
			}
			
			// The entire string is checked.
			if (choice == "rock" || choice == "Rock" || choice == "ROCK") {
				return 0;
			}
			
			else if (choice == "paper" || choice == "Paper" || choice == "PAPER") {
				return 1;
			}
			
			else if (choice == "scissors" || choice == "Scissors" || choice == "SCISSORS") {
				return 2;
			}
			
			// Invalid input.
			else {
				std::cout << "\nInvalid input.\n";
			}
		}
	}
};

/**
 * Returns the integer choice in string form.
 * 0 -> Rock
 * 1 -> Paper
 * 2 -> Scissors
 */
std::string string(int choice) noexcept {
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
 * Hosts a single round between two RPSBot objects.
 * The index of the winner is returned.
 * If the round was a tie, -1 is returned.
 */
int round(
	std::array<std::unique_ptr<RPSBot>, 2>& bots,
	bool verbose = false
) noexcept {
	std::array<int, 2> choices{bots[0]->choose(), bots[1]->choose()};
	
	// The bots are updated.
	for (int i = 0; i < 2; i++) {
		bots[i]->update(choices[i], choices[1 - i]);
	}
	
	// The result is calculated.
	int result = (CHOICES + choices[0] - choices[1]) % CHOICES - 1;
	
	if (result < -1) {
		std::cout << "\n!\n";
	}
	
	// The result is optionally displayed.
	if (verbose) {
		std::cout << std::endl;
		
		for (int i = 0; i < 2; i++) {
			std::cout
				<< "Bot "
				<< i
				<< " chose "
				<< string(choices[i])
				<< "!\n"
			;
		}
		
		// There was a winner.
		if (result >= 0) {
			std::cout << "Bot " << result << " won!\n";
		}
		
		// It was a tie.
		else {
			std::cout << "It's a tie!\n";
		}
	}
	
	return result;
}

/**
 * Hosts a competition between two RPSBot objects.
 * A competition involves playing a chosen number of rounds of
 *   rock, paper, scissors and counting the number of wins for
 *   each bot.
 * The total score and number of wins are displayed.
 * The results of each round can optionally be displayed.
 */
void competition(
	std::array<std::unique_ptr<RPSBot>, 2>& bots,
	int count = 1,
	bool verbose = false
) noexcept {
	std::array<int, 2> scores{};
	
	for (int i = 0; i < count; i++) {
		int index = round(bots, verbose);
		
		if (index >= 0) {
			scores[index]++;
		}
	}
	
	std::cout << std::endl;
	
	for (int i = 0; i < 2; i++) {
		std::cout
			<< "Bot "
			<< i
			<< " victory: "
			<< 100 * scores[i] / count
			<< "%\n"
		;
	}
}