#include "server.hpp"

void inflate(std::string& choice) {
	if (choice == "r") {
		choice = "rock";
	}

	else if (choice == "p") {
		choice = "paper";
	}

	else {
		choice = "scissors";
	}
}

int main() {
	// The server's messenger is initialised
	ServerMessenger messenger;

	// Waits for the client to send the ok signal
	while (messenger.read() != "ok");

	// Game variables are initialised
	int score = 0;
	int enemy = 0;
	int status;
	std::string choice;
	std::string opponent;

	while (true) {
		// The choice is cleared
		choice = "";

		// Loop to get a valid choice
		while (choice != "r" && choice != "p" && choice != "s") {
			std::cout << "Rock (r), paper (p), or scissors (s)? ";
			std::getline(std::cin, choice);
		}

		// The choice is sent to the client
		messenger.send(choice);
		// The client's choice is waited for
		opponent = messenger.read();

		// If both players chose the same thing, then it is a tie
		if (choice == opponent) {
			status = 0;
		}

		// If the player chose rock
		else if (choice == "r") {
			// If the opponent chose paper, the player loses
			if (opponent == "p") {
				status = -1;
			}

			// If the opponent chose scissors, the player wins
			else {
				status = 1;
			}
		}

		// If the player chose paper
		else if (choice == "p") {
			// If the opponent chose scissors, the player loses
			if (opponent == "s") {
				status = -1;
			}

			//If the opponent chose rock, the player wins
			else {
				status = 1;
			}
		}
#
		// If the player chose scissors
		else {
			// If the opponent chose rock, the player loses
			if (opponent == "r") {
				status = -1;
			}

			// If the opponent chose paper, the player wins
			else {
				status = 1;
			}
		}

		// The shorthands are expanded to their full names
		inflate(choice);
		inflate(opponent);

		// The choices of both players are displayed
		std::cout << "\nYou chose " << choice << "!\nYour opponent chose " << opponent << "!\n\n";

		// The status is used to determine who gets awarded the point
		switch (status) {
			case 1:
				std::cout << "You win!\n\n";
				score++;
				break;

			case -1:
				std::cout << "You lose...\n\n";
				enemy++;
				break;

			default:
				std::cout << "It was a tie.\n\n";
		}

		// The scores are dsplayed
		std::cout << score << " - " << enemy << "\n\n";
	}
}