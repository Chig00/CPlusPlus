#include "rpsarena.hpp"

constexpr int ROUNDS = 100;
constexpr bool VERBOSE = true;

int main() noexcept {
	std::array<std::unique_ptr<RPSBot>, 2> bots{
		std::make_unique<SmartBot>(),
		std::make_unique<HumanBot>()
	};
	
	competition(
		bots,
		ROUNDS,
		VERBOSE
	);
	
	return 0;
}