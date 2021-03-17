#include <iostream> // IO
#include <fstream> // File reading
#include <string> // String manipulation
#include <random> // Shuffling
#include <ctime> // RNG seeding

// Data location
const char* const DATA = "data.txt";

/* A class to manage the quiz
   Loads and shuffles the questions and then presents them
 */
class Quiz {
	public:
		/* Loads the quiz questions and answers, obtains the number of questions to be asked,
		   and shuffles the questions
		 */
		Quiz(std::fstream* data, int question_count) {
			// The questions and answers are allocatd memory
			questions = new std::string[question_count];
			answers = new std::string[question_count];
			
			// The questions and answers are loaded
			for (int i = 0; i < question_count; i++) {
				std::getline(*data, questions[i]);
				std::getline(*data, answers[i]);
			}
			
			// The file is closed
			data->close();
			
			// The number of questions to be asked is obtained from user input
			std::cout << "Number of questions to be asked: ";
			std::cin >> count;
			std::cin.clear();
			std::cin.ignore(9999, '\n');
			
			// The count is fixed if it exceeds the question count
			count = count > question_count ? question_count : count;
			
			// Random Number Generator
			std::mt19937 generator(time(NULL));
			
			// The questions are shuffled (Fisher-Yates)
			for (int i = 0; i < count; i++) {
				// The swap index is generated
				std::uniform_int_distribution<int> distribution(i, question_count - 1);
				int index = distribution(generator);
				
				// The swaps are performed
				std::string temp = questions[i];
				questions[i] = questions[index];
				questions[index] = temp;
				temp = answers[i];
				answers[i] = answers[index];
				answers[index] = temp;
			}
		}
		
		/* Frees the memory allocated to the questions and answers
		 */
		~Quiz() {
			delete[] questions;
			delete[] answers;
		}
		
		/* Asks the questions, shows the corrections if incorrect, and calculates a score
		 */
		void quiz() {
			int score = 0;
			
			std::cout
				<< "\nThe following sentences have errors.\n"
				<< "Enter the correct version of the sentences.\n\n"
			;
			
			for (int i = 0; i < count; i++) {
				std::cout << questions[i] << '\n';
				std::string answer;
				std::getline(std::cin, answer);
				
				std::cout << '\n';
				
				if (answer == answers[i]) {
					std::cout << "Correct!\nScore: " << ++score << '/' << i + 1 << '\n';
				}
				
				else {
					std::cout
						<< "Incorrect...\nAnswer:\n" << answers[i] << "\nScore: "
						<< score << '/' << i + 1 << '\n'
					;
				}
				
				std::cout << '\n';
			}
			
			std::cout
				<< "Final score: " << score << '/' << count
				<< " (" << 100 * score / count << "%)\n"
			;
		}
	
	private:
		std::string* questions; // The questions
		std::string* answers; // The answers
		int count; // The number of questions to be asked
};
	

int main() {
	std::fstream data(DATA);
	int question_count;
	data >> question_count;
	data.clear();
	data.ignore(9999, '\n');
	Quiz quiz(&data, question_count);
	quiz.quiz();
}