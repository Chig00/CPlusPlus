#include <iostream>
#include <random>
#include <ctime>

#define BOARD_SIZE 9
#define MAX_HINT (BOARD_SIZE + (BOARD_SIZE % 2)) / 2

/* The Picross Board
   Contains the pattern to be found, the player's pattern, and the hints
 */
class Board {
	public:
		/* Initialises the RNG and produces a grid with hints
		 */
		Board() {
			// RNG initialised
			generator = new std::mt19937(time(NULL));
			distribution = new std::uniform_int_distribution<int>(0, 1);
			
			// Target board and player board initialised
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < BOARD_SIZE; j++) {
					target[i][j] = (*distribution)(*generator);
					board[i][j] = 0;
				}
			}
			
			//Row and column hints set to zero
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < MAX_HINT; j++) {
					rows[i][j] = 0;
					columns[i][j] = 0;
				}
			}
			
			// Row hints initialised
			for (int i = 0; i < BOARD_SIZE; i++) {
				int position = MAX_HINT - 1;
				
				for (int j = BOARD_SIZE - 1; j > -1; j--) {
					if (target[i][j]) {
						rows[i][position]++;
					}
					
					else if (rows[i][position]) {
						position--;
					}
				}
			}
			
			// Column hints initialised
			for (int i = 0; i < BOARD_SIZE; i++) {
				int position = MAX_HINT - 1;
				
				for (int j = BOARD_SIZE - 1; j > -1; j--) {
					if (target[j][i]) {
						columns[i][position]++;
					}
					
					else if (columns[i][position]) {
						position--;
					}
				}
			}
		}
		
		/* Prints the target board to display (including hints)
		 */
		void print_target() {
			std::cout << '\n';
			
			// Column hints are printed first
			for (int i = 0; i < MAX_HINT; i++) {
				for (int j = 0; j < MAX_HINT; j++) {
					std::cout << "  ";
				}
				
				std::cout << ' ';
				
				for (int j = 0; j < BOARD_SIZE; j++) {
					if (columns[j][i]) {
						std::cout << columns[j][i] << ' ';
					}
					
					else {
						std::cout << "  ";
					}
				}
				
				std::cout << '\n';
			}
			
			std::cout << '\n';
			
			// Row hints and the target board are then printed
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < MAX_HINT; j++) {
					if (rows[i][j]) {
						std::cout << rows[i][j] << ' ';
					}
					
					else {
						std::cout << "  ";
					}
				}
				
				std::cout << ' ';
				
				for (int j = 0; j < BOARD_SIZE; j++) {
					std::cout << (target[i][j] ? 'O' : ' ') << ' ';
				}
				
				std::cout << ' ' << i << '\n';
			}
			
			std::cout << '\n';
			
			for (int i = 0; i < MAX_HINT; i++) {
				std::cout << "  ";
			}
			
			std::cout << ' ';
			
			for (int i = 0; i < BOARD_SIZE; i++) {
				std::cout << i << ' ';
			}
			
			std::cout << "\n\n";
		}
		
		/* Prints the player's board to display (including hints)
		 */
		void print_board() {
			std::cout << '\n';
			
			// Column hints are printed first
			for (int i = 0; i < MAX_HINT; i++) {
				for (int j = 0; j < MAX_HINT; j++) {
					std::cout << "  ";
				}
				
				std::cout << ' ';
				
				for (int j = 0; j < BOARD_SIZE; j++) {
					if (columns[j][i]) {
						std::cout << columns[j][i] << ' ';
					}
					
					else {
						std::cout << "  ";
					}
				}
				
				std::cout << '\n';
			}
			
			std::cout << '\n';
			
			// Row hints and the target board are then printed
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < MAX_HINT; j++) {
					if (rows[i][j]) {
						std::cout << rows[i][j] << ' ';
					}
					
					else {
						std::cout << "  ";
					}
				}
				
				std::cout << ' ';
				
				for (int j = 0; j < BOARD_SIZE; j++) {
					std::cout << (board[i][j] ? (board[i][j] > 0 ? 'O' : 'X') : ' ') << ' ';
				}
				
				std::cout << ' ' << i << '\n';
			}
			
			std::cout << '\n';
			
			for (int i = 0; i < MAX_HINT; i++) {
				std::cout << "  ";
			}
			
			std::cout << ' ';
			
			for (int i = 0; i < BOARD_SIZE; i++) {
				std::cout << i << ' ';
			}
			
			std::cout << "\n\n";
		}
		
		/* Returns true if the player's board matches the target
		 */
		bool solved() {
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0 ; j < BOARD_SIZE; j++) {
					if (target[i][j]) {
						if (board[i][j] != 1) {
							return false;
						}
					}
					
					else {
						if (board[i][j] == 1) {
							return false;
						}
					}
				}
			}
			
			return true;
		}
		
		/* Fills in the board
		   Duplicate commands erase the square
		 */
		void fill(int command, int i, int j) {
			board[j][i] = board[j][i] == command ? 0 : command;
		}
			
	private:
		int target[BOARD_SIZE][BOARD_SIZE]; // The pattern to be found
		int board[BOARD_SIZE][BOARD_SIZE]; // The player's pattern
		int rows[BOARD_SIZE][MAX_HINT]; // The row hints
		int columns[BOARD_SIZE][MAX_HINT]; // The column hints
		std::mt19937* generator; // RNG
		std::uniform_int_distribution<int>* distribution; // Uniform distribution
};

/* Creates a board and starts a game
 */
int main() {
	// Introductory message
	std::cout << "Picross by Chigozie Agomo\nUse O or o to fill a square\n"
		<< "Use X or x to mark a square\nEnter the coordinates after the command\n"
		<< "Examples:\nO 7 3\nX 3 4\no 2 8\nx 6 2\n";
		
	// Board initialisation
	Board board;
	
	int start = clock();
	
	// Game continues until the board is solved
	while (!board.solved()) {
		board.print_board(); // The board's current state is displayed
		
		char mark;
		int i;
		int j;
		
		// The next command is gotten
		std::cout << "Command and coordinates: ";
		std::cin >> mark >> i >> j;
		
		// Input is checked
		if (!std::cin.good()) {
			std::cin.clear();
			std::cout << "Invalid input\n";
		}
		
		// The player can quit with q
		else if (mark == 'q' || mark == 'Q') {
			break;
		}
		
		else if (i < 0 || i >= BOARD_SIZE || j < 0 || j >= BOARD_SIZE) {
			std::cout << "Invalid input\n";
		}
		
		else if (mark != 'O' && mark != 'o' && mark != 'X' && mark != 'x') {
			std::cout << "Invalid input\n";
		}
		
		// If the input is okay, it is used
		else {
			board.fill(
				mark == 'O' || mark == 'o' ? 1 : (mark == 'X' || mark == 'x' ? -1 : 0), i, j
			);
		}
		
		std::cin.ignore(9999, '\n');
	}
	
	int finish = clock();
	
	// When the player quits or finishes, the final solution is displayed along
	//   with the time taken
	board.print_target();
	std::cout << "Time: " << (double) (finish - start) / CLOCKS_PER_SEC << "s\n";
	
	return 0;
}