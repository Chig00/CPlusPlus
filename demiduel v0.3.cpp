#include <iostream>
#include <random>
#include "sdlandnet.hpp"

#define DEBUG false

// Constants
//{
// System Constants
//{
// The current version of the program.
constexpr int VERSION[] = {0, 3, 0, 0};

// The title of the game in string form.
constexpr const char* TITLE_STRING = "Demi Duel";

// Window dimensions.
#if DEBUG == false
constexpr int WINDOW_WIDTH = 0;
constexpr int WINDOW_HEIGHT = 0;
#else
constexpr int WINDOW_WIDTH = 700;
constexpr int WINDOW_HEIGHT = 400;
#endif


// The game's keybindings.
//{
constexpr int QUIT_KEY = Events::ESCAPE;
constexpr int BACK_KEY = QUIT_KEY;
constexpr int SUBMIT_KEY = Events::ENTER;
constexpr int NEXT_KEY = SUBMIT_KEY;
constexpr int DELETE_KEY = Events::BACKSPACE;
//}

// The number of letters, numbers, and punctuation marks used as sprites.
//{
constexpr int LETTERS = System::LETTERS;
constexpr int NUMBERS = System::NUMBERS;
constexpr int PUNCTUATION = 12;
//}

// The number of renderer sources.
constexpr int RENDERER_COUNT = 2 * LETTERS + NUMBERS + PUNCTUATION;

// The directory and extension of renderer sources.
constexpr const char* SOURCE_DIRECTORY = "data/";
constexpr const char* SOURCE_EXTENSION = ".bmp";

// The source of the punctuation.
//{
constexpr const char* FULL_STOP_SOURCE = "data/fullstop.bmp";
constexpr const char* COMMA_SOURCE = "data/comma.bmp";
constexpr const char* COLON_SOURCE = "data/colon.bmp";
constexpr const char* SLASH_SOURCE = "data/slash.bmp";
constexpr const char* EXCLAMATION_SOURCE = "data/exclamation.bmp";
constexpr const char* QUESTION_SOURCE = "data/question.bmp";
constexpr const char* SEMICOLON_SOURCE = "data/semicolon.bmp";
constexpr const char* LEFT_BRACKET_SOURCE = "data/leftbracket.bmp";
constexpr const char* RIGHT_BRACKET_SOURCE = "data/rightbracket.bmp";
constexpr const char* APOSTROPHE_SOURCE = "data/apostrophe.bmp";
constexpr const char* PLUS_SOURCE = "data/plus.bmp";
constexpr const char* MINUS_SOURCE = "data/minus.bmp";
//}

// The string that indicates that the player quit.
constexpr const char* TERMINATOR_STRING = "/quit";
 
// The number of cards to be displayed per page.
constexpr int PAGE_COUNT = 5;

// The number of players in a game.
constexpr int PLAYERS = 2;

// The initial state of messenger strings.
constexpr const char* EMPTY_MESSAGE = "";

// The string of the error thrown when attempting to
//   remove cards from an empty card store.
constexpr const char* EMPTY_CARD_STORE = "Removal from an empty card store.";

// Constants to index the players.
constexpr int PLAYER = 0;
constexpr int OPPONENT = 1;

// A constant that defines the user not making a choice.
constexpr int NO_CHOICE = -1;

// The message to indicate a move.
constexpr const char* PLAY_MESSAGE = "play";
constexpr const char* ABILITY_MESSAGE = "ability";
constexpr const char* RETREAT_MESSAGE = "retreat";
constexpr const char* ATTACK_MESSAGE = "attack";

// Constants to define a game condition.
constexpr int NO_END = -1;
constexpr int TIE = 2;

// Constants to define the outcomes of a coin flip.
constexpr bool HEADS = true;
constexpr bool TAILS = false;
//}

// Game Constants
//{
// Count Constants
//{
constexpr int DECK_SIZE = 40;
constexpr int CARD_TYPES = 3;
constexpr int BENCH_INDEX = 1;
constexpr int HAND_SIZE = 8;
constexpr int LIFE_SIZE = 4;
constexpr int TURN_DRAW = 1;
constexpr int MAX_FIGHTER_COPIES = 1;
constexpr int MAX_SUPPORTER_COPIES = MAX_FIGHTER_COPIES;
constexpr int MAX_ENERGY_COPIES = 4;

// Ensures that the game can begin after the bonus draws.
constexpr int MAX_BONUS = DECK_SIZE - HAND_SIZE - LIFE_SIZE - 1;
//}

// Master Copy Counts
//{
constexpr int FIGHTER_COUNT = 9;
constexpr int SUPPORTER_COUNT = 6;
constexpr int ENERGY_COUNT = 6;
constexpr int CARD_COUNT = FIGHTER_COUNT + SUPPORTER_COUNT + ENERGY_COUNT;
//}

// Card Attribute Constants
//{
// Element
//{
constexpr const char* FIRE_ELEMENT = "Fire";
constexpr const char* AIR_ELEMENT = "Air";
constexpr const char* WATER_ELEMENT = "Water";
constexpr const char* EARTH_ELEMENT = "Earth";
constexpr const char* NO_ELEMENT = "Null";
//}

// Card Types
//{
constexpr const char* FIGHTER_TYPE = "Fighter";
constexpr const char* SUPPORTER_TYPE = "Supporter";
constexpr const char* ENERGY_TYPE = "Energy";
constexpr const char* ABILITY_TYPE = "Ability";
constexpr const char* ATTACK_TYPE = "Attack";
//}

// Miscellaneous
//{
constexpr const char* NO_EFFECTS = "";
constexpr const char* FIGHTER_DESCRIPTION = "";
constexpr const char* FIGHTER_EFFECTS = NO_EFFECTS;
constexpr const char* NO_OLD_RANK = "";
constexpr int PASSIVE_USES = 0;
constexpr int INFINITE_USES = 0;
constexpr const char* BASIC_ENERGY_DESCRIPTION =
	"Provides 1000 energy for fighters of this element."
;
constexpr const char* BASIC_ENERGY_EFFECTS = NO_EFFECTS;
constexpr int BASIC_ENERGY_VALUE = 1000;
constexpr const char* PLAYER_EFFECTS = NO_EFFECTS;
//}
//}

// Effect Constants
//{
// The characters used in effect parsing.
//{
constexpr char EFFECT_TERMINATOR = '\n';
constexpr char EFFECT_SEPARATOR = ' ';
//}

// The constant strings for the effects.
//{
constexpr const char* RANK_UP_EFFECT = "rank_up";
constexpr const char* CONVERSION_EFFECT = "conversion";
constexpr const char* POWER_EFFECT = "power";
constexpr const char* SWITCH_IN_EFFECT = "switch_in";
constexpr const char* FLIP_EFFECT = "flip";
constexpr const char* HEADS_EFFECT = "heads";
constexpr const char* INVINCIBLE_EFFECT = "invincible";
constexpr const char* TAILS_EFFECT = "tails";
constexpr const char* BACKPEDAL_EFFECT = "backpedal";
constexpr const char* DISCARD_EFFECT = "discard";
constexpr const char* UNIVERSAL_EFFECT = "all";
constexpr const char* DRAW_EFFECT = "draw";
constexpr const char* PREPARATION_EFFECT = "prep";
constexpr const char* SHUFFLE_EFFECT = "shuffle";
constexpr const char* END_DRAW_EFFECT = "end_draw";
constexpr const char* SNIPE_EFFECT = "snipe";
constexpr const char* SEARCH_EFFECT = "search";
constexpr const char* MILL_EFFECT = "mill";
constexpr const char* HEAL_EFFECT = "heal";
constexpr const char* TRASH_EFFECT = "trash";
constexpr const char* AGILITY_EFFECT = "agility";
constexpr const char* AGILITY_AURA_EFFECT = "agility_aura";
constexpr const char* FREEDOM_EFFECT = "freedom";
//}

// The constants for the rank conversion effect explanation.
//{
#define RANK_CONVERSION_CONDITION (        \
	(effect = effect_search(RANK_UP_EFFECT)) \
	&& (*effect)[1] == CONVERSION_EFFECT   \
)
constexpr const char* RANK_CONVERSION_REPRESENTATION = "Rank Conversion";
constexpr const char* RANK_CONVERSION_VALUE = "";
constexpr const char* RANK_CONVERSION_EXPLANATION =
	"When this fighter ranks up, the attached energy "
	"is converted to the element of the new rank."
;
//}

// The constants for the power effect explanation.
//{
#define POWER_CONDITION effect_count(POWER_EFFECT)
constexpr const char* POWER_REPRESENTATION = "Power";
#define POWER_VALUE std::to_string(effect_count(POWER_EFFECT))
#define POWER_EXPLANATION (     \
	"Attacks deal "             \
	+ effect_value              \
	+ " more damage this turn." \
)
//}

// The constants for the preparation explanation.
//{
#define PREPARATION_CONDITION effect_search(PREPARATION_EFFECT)
constexpr const char* PREPARATION_REPRESENTATION = "Preparation";
constexpr const char* PREPARATION_VALUE = "";
constexpr const char* PREPARATION_EXPLANATION =
	"If you go first, you can't attack on your first turn."
;
//}

// The constants for the end draw explanation.
//{
#define END_DRAW_CONDITION effect_count(END_DRAW_EFFECT)
constexpr const char* END_DRAW_REPRESENTATION = "End Draw";
#define END_DRAW_VALUE std::to_string(effect_count(END_DRAW_EFFECT))
#define END_DRAW_EXPLANATION (          \
	"This player draws "                \
	+ effect_value                      \
	+ " cards at the end of this turn." \
)
//}

// The constants for the fighter agility explanation.
//{
#define AGILITY_CONDITION effect_count(AGILITY_EFFECT)
constexpr const char* AGILITY_REPRESENTATION = "Agility";
#define AGILITY_VALUE std::to_string(effect_count(AGILITY_EFFECT))
#define AGILITY_EXPLANATION (                                      \
	"This fighter's retreat cost is "                                      \
	+ std::string(std::stoi(effect_value) < 0 ? "increased" : "decreased") \
	+ " by "                                                               \
	+ std::to_string(abs(std::stoi(effect_value)))                         \
	+ "."                                                                  \
)
//}

// The constants for the agility aura explanation.
//{
#define AGILITY_AURA_CONDITION fighter_effect_count(AGILITY_AURA_EFFECT)
constexpr const char* AGILITY_AURA_REPRESENTATION = "Agility Aura";
#define AGILITY_AURA_VALUE std::to_string(fighter_effect_count(AGILITY_AURA_EFFECT))
#define AGILITY_AURA_EXPLANATION (                      \
	"This player's fighters retreat for "               \
	+ std::to_string(abs(std::stoi(effect_value)))      \
	+ (std::stoi(effect_value) < 0 ? " more" : " less") \
	+ " energy!"                                        \
)
//}

// The constants for the freedom explanation.
//{
#define FREEDOM_CONDITION fighter_effect_search(FREEDOM_EFFECT)
constexpr const char* FREEDOM_REPRESENTATION = "Freedom";
constexpr const char* FREEDOM_VALUE = "";
constexpr const char* FREEDOM_EXPLANATION =
	"This player's fighters can retreat as often as the player wishes."
;
//}

// The total number of explainable effects.
constexpr int EXPLANATION_COUNT = 5;

// All of the explainable effect conditions.
//{
#define EFFECT_CONDITIONS(X) (                            \
	X == 0 ? static_cast<bool>(RANK_CONVERSION_CONDITION) \
	: X == 1 ? static_cast<bool>(POWER_CONDITION)         \
	: X == 2 ? static_cast<bool>(PREPARATION_CONDITION)   \
	: X == 3 ? static_cast<bool>(END_DRAW_CONDITION)      \
	: static_cast<bool>(AGILITY_CONDITION)                \
)
//}

// All of the explainable effect representations.
constexpr const char* EFFECT_REPRESENTATIONS[EXPLANATION_COUNT] = {
	RANK_CONVERSION_REPRESENTATION,
	POWER_REPRESENTATION,
	PREPARATION_REPRESENTATION,
	END_DRAW_REPRESENTATION,
	AGILITY_REPRESENTATION
};

// All of the explainable effect values.
//{
#define EFFECT_VALUES(X) (         \
	X == 0 ? RANK_CONVERSION_VALUE \
	: X == 1 ? POWER_VALUE         \
	: X == 2 ? PREPARATION_VALUE   \
	: X == 3 ? END_DRAW_VALUE      \
	: AGILITY_VALUE                \
)
//}

// All of the explainable effect expanations.
//{
#define EFFECT_EXPLANATIONS(X) (         \
	X == 0 ? RANK_CONVERSION_EXPLANATION \
	: X == 1 ? POWER_EXPLANATION         \
	: X == 2 ? PREPARATION_EXPLANATION   \
	: X == 3 ? END_DRAW_EXPLANATION      \
	: AGILITY_EXPLANATION                \
)
//}

// The total number of player-specific explainable effects.
constexpr int PLAYER_EXPLANATION_COUNT = 2;

// All of the player-specific explainable effect conditions.
//{
#define PLAYER_EFFECT_CONDITIONS(X) (                  \
	X == 0 ? static_cast<bool>(AGILITY_AURA_CONDITION) \
	: static_cast<bool>(FREEDOM_CONDITION)             \
)
//}

// All of the player-specific explainable effect representations.
constexpr const char* PLAYER_EFFECT_REPRESENTATIONS[PLAYER_EXPLANATION_COUNT] = {
	AGILITY_AURA_REPRESENTATION,
	FREEDOM_REPRESENTATION
};

// All of the player-specific explainable effect values.
//{
#define PLAYER_EFFECT_VALUES(X) (      \
	X == 0 ? AGILITY_AURA_VALUE \
	: FREEDOM_VALUE             \
)
//}

// All of the player-specific explainable effect expanations.
//{
#define PLAYER_EFFECT_EXPLANATIONS(X) ( \
	X == 0 ? AGILITY_AURA_EXPLANATION   \
	: FREEDOM_EXPLANATION               \
)
//}
//}
//}

// Video Constants
//{
// Main and Connection Menus Constants
//{
// The position and dimensions of the title.
constexpr double TITLE_X = 0.5;
constexpr double TITLE_Y = 0.2;
constexpr double TITLE_WIDTH = 0.075;
constexpr double TITLE_HEIGHT = 2 * TITLE_WIDTH;
constexpr double TITLE_SEPARATION = TITLE_WIDTH / 20;

// The constants for the credits sprite.
#define CREDITS_STRING (     \
	"2020 Chigozie Agomo\nv" \
	+ version_string         \
)
constexpr double CREDITS_X = 0.25;
constexpr double CREDITS_Y = 0.925;
constexpr double CREDITS_WIDTH = 0.025;
constexpr double CREDITS_HEIGHT = 2 * CREDITS_WIDTH;
constexpr double CREDITS_MAX_WIDTH = 0;
constexpr double CREDITS_SEPARATION_X = CREDITS_WIDTH / 10;
constexpr double CREDITS_SEPARATION_Y = 5 * CREDITS_SEPARATION_X;
constexpr Renderer::Justification CREDITS_JUSTIFICATION = Renderer::LEFT_JUSTIFY;

// The constants for the quit buton.
constexpr const char* QUIT_STRING = "Quit";
constexpr double QUIT_X = 0.875;
constexpr double QUIT_X_ALT = 1 - QUIT_X;
constexpr double QUIT_Y = 0.925;
constexpr double QUIT_WIDTH = 0.05;
constexpr double QUIT_HEIGHT = 2 * QUIT_WIDTH;
constexpr double QUIT_SEPARATION = QUIT_WIDTH / 20;

// The constants for the play button.
constexpr const char* PLAY_STRING = "Play";
constexpr double PLAY_X = TITLE_X;
constexpr double PLAY_Y = 0.7;
constexpr double PLAY_WIDTH = QUIT_WIDTH;
constexpr double PLAY_HEIGHT = 2 * PLAY_WIDTH;
constexpr double PLAY_SEPARATION = PLAY_WIDTH / 20;

// The constants for the server button.
constexpr const char* SERVER_STRING = "Server";
constexpr double SERVER_X = TITLE_X;
constexpr double SERVER_Y = 0.3;
constexpr double SERVER_WIDTH = PLAY_WIDTH;
constexpr double SERVER_HEIGHT = 2 * SERVER_WIDTH;
constexpr double SERVER_SEPARATION = SERVER_WIDTH / 20;

// The constants for the client button.
constexpr const char* CLIENT_STRING = "Client";
constexpr double CLIENT_X = SERVER_X;
constexpr double CLIENT_Y = 1 - SERVER_Y;
constexpr double CLIENT_WIDTH = SERVER_WIDTH;
constexpr double CLIENT_HEIGHT = SERVER_HEIGHT;
constexpr double CLIENT_SEPARATION = SERVER_SEPARATION;

// The constants for the back button.
constexpr const char* BACK_STRING = "Back";
constexpr double BACK_X = 1 - QUIT_X;
constexpr double BACK_Y = QUIT_Y;
constexpr double BACK_WIDTH = QUIT_WIDTH;
constexpr double BACK_HEIGHT = QUIT_HEIGHT;
constexpr double BACK_SEPARATION = QUIT_SEPARATION;

// The constants for the next button.
constexpr const char* NEXT_STRING = "Next";
constexpr double NEXT_X = 1 - BACK_X;
constexpr double NEXT_Y = BACK_Y;
constexpr double NEXT_WIDTH = BACK_WIDTH;
constexpr double NEXT_HEIGHT = BACK_HEIGHT;
constexpr double NEXT_SEPARATION = BACK_SEPARATION;

// The constants for the address sprite.
constexpr const char* ADDRESS_STRING = "Address";
constexpr double ADDRESS_X = SERVER_X;
constexpr double ADDRESS_Y = SERVER_Y;
constexpr double ADDRESS_SHIFT = 0.5 - SERVER_Y;
constexpr double ADDRESS_WIDTH = SERVER_WIDTH;
constexpr double ADDRESS_HEIGHT = SERVER_HEIGHT;
constexpr double ADDRESS_SEPARATION = SERVER_SEPARATION;

// The constants for the port sprite.
constexpr const char* PORT_STRING = "Port";
constexpr double PORT_X = ADDRESS_X;
constexpr double PORT_Y = ADDRESS_Y;
constexpr double PORT_SHIFT = ADDRESS_SHIFT;
constexpr double PORT_WIDTH = ADDRESS_WIDTH;
constexpr double PORT_HEIGHT = ADDRESS_HEIGHT;
constexpr double PORT_SEPARATION = ADDRESS_SEPARATION;

// The constants for the wait sprite.
constexpr const char* WAIT_STRING = "Waiting for\nthe opponent...";
constexpr double WAIT_X = 0.5;
constexpr double WAIT_Y = 0.5;
constexpr double WAIT_WIDTH = PORT_WIDTH;
constexpr double WAIT_HEIGHT = PORT_HEIGHT;
constexpr double WAIT_MAX_WIDTH = 0;
constexpr double WAIT_SEPARATION_X = PORT_SEPARATION;
constexpr double WAIT_SEPARATION_Y = 50 * WAIT_SEPARATION_X;
constexpr Renderer::Justification WAIT_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// The constants for the no server sprite.
constexpr const char* NO_SERVER_STRING = "The host could\nnot be resolved.";
constexpr double NO_SERVER_X = WAIT_X;
constexpr double NO_SERVER_Y = WAIT_Y;
constexpr double NO_SERVER_WIDTH = WAIT_WIDTH;
constexpr double NO_SERVER_HEIGHT = WAIT_HEIGHT;
constexpr double NO_SERVER_MAX_WIDTH = WAIT_MAX_WIDTH;
constexpr double NO_SERVER_SEPARATION_X = WAIT_SEPARATION_X;
constexpr double NO_SERVER_SEPARATION_Y = WAIT_SEPARATION_Y;
constexpr Renderer::Justification NO_SERVER_JUSTIFICATION = WAIT_JUSTIFICATION;
//}

// Deck Builder Constants
//{
// The constants for the deck builder sprite.
constexpr const char* BUILDER_STRING = "Build your deck!";
constexpr double BUILDER_X = 0.5;
constexpr double BUILDER_Y = 0.1;
constexpr double BUILDER_WIDTH = PORT_WIDTH;
constexpr double BUILDER_HEIGHT = PORT_HEIGHT;
constexpr double BUILDER_SEPARATION = PORT_SEPARATION;

// The constants for the fighter button.
constexpr const char* FIGHTER_STRING = "Fighter";
constexpr double FIGHTER_X = BUILDER_X;
constexpr double FIGHTER_Y = BUILDER_Y + 0.3;
constexpr double FIGHTER_WIDTH = 0.75 * BUILDER_WIDTH;
constexpr double FIGHTER_HEIGHT = 2 * FIGHTER_WIDTH;
constexpr double FIGHTER_SEPARATION = FIGHTER_WIDTH / 20;

// The constants for the supporter button.
constexpr const char* SUPPORTER_STRING = "Supporter";
constexpr double SUPPORTER_X = FIGHTER_X;
constexpr double SUPPORTER_Y = FIGHTER_Y + 0.125;
constexpr double SUPPORTER_WIDTH = FIGHTER_WIDTH;
constexpr double SUPPORTER_HEIGHT = FIGHTER_HEIGHT;
constexpr double SUPPORTER_SEPARATION = FIGHTER_SEPARATION;

// The constants for the energy button.
constexpr const char* ENERGY_STRING = "Energy";
constexpr double ENERGY_X = SUPPORTER_X;
constexpr double ENERGY_Y = SUPPORTER_Y + 0.125;
constexpr double ENERGY_WIDTH = SUPPORTER_WIDTH;
constexpr double ENERGY_HEIGHT = SUPPORTER_HEIGHT;
constexpr double ENERGY_SEPARATION = SUPPORTER_SEPARATION;

// The constants for the generator button.
constexpr const char* GENERATOR_STRING = "Deck Generator";
constexpr double GENERATOR_X = ENERGY_X;
constexpr double GENERATOR_Y = ENERGY_Y + 0.125;
constexpr double GENERATOR_WIDTH = ENERGY_WIDTH;
constexpr double GENERATOR_HEIGHT = ENERGY_HEIGHT;
constexpr double GENERATOR_SEPARATION = ENERGY_SEPARATION;

// The constants for the done button.
constexpr const char* DONE_STRING = "Done";
constexpr double DONE_X = QUIT_X;
constexpr double DONE_Y = QUIT_Y;
constexpr double DONE_WIDTH = QUIT_WIDTH;
constexpr double DONE_HEIGHT = QUIT_HEIGHT;
constexpr double DONE_SEPARATION = QUIT_SEPARATION;

// The constants for the deck capacity sprite.
#define CAPACITY_STRING (        \
	"Cards "                     \
	+ std::to_string(card_count) \
	+ '/'                        \
	+ std::to_string(DECK_SIZE)  \
)
constexpr double CAPACITY_X = BUILDER_X;
constexpr double CAPACITY_Y = BUILDER_Y + 0.175;
constexpr double CAPACITY_WIDTH = FIGHTER_WIDTH;
constexpr double CAPACITY_HEIGHT = FIGHTER_HEIGHT;
constexpr double CAPACITY_SEPARATION = FIGHTER_SEPARATION;

// The constants for the incompatible sprite.
constexpr const char* INCOMPATIBLE_STRING = "The versions of the program are incompatible...";
constexpr double INCOMPATIBLE_X = 0.5;
constexpr double INCOMPATIBLE_Y = 0.5;
constexpr double INCOMPATIBLE_WIDTH = NO_SERVER_WIDTH;
constexpr double INCOMPATIBLE_HEIGHT = NO_SERVER_HEIGHT;
constexpr double INCOMPATIBLE_MAX_WIDTH = 20 * INCOMPATIBLE_WIDTH;
constexpr double INCOMPATIBLE_SEPARATION_X = NO_SERVER_SEPARATION_X;
constexpr double INCOMPATIBLE_SEPARATION_Y = NO_SERVER_SEPARATION_Y;
constexpr Renderer::Justification INCOMPATIBLE_JUSTIFICATION = NO_SERVER_JUSTIFICATION;

// The constants for the card sprites.
#define CARD_STRING (card.to_string())
constexpr double CARD_X = 0.5;
constexpr double CARD_Y = 0.5;
constexpr double CARD_WIDTH = INCOMPATIBLE_WIDTH / 3;
constexpr double CARD_HEIGHT = 2 * CARD_WIDTH;
constexpr double CARD_MAX_WIDTH = 0.5;
constexpr double CARD_SEPARATION_X = CARD_WIDTH / 20;
constexpr double CARD_SEPARATION_Y = CARD_HEIGHT / 8;
constexpr Renderer::Justification CARD_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// The constants for the left arrow button.
constexpr const char* LEFT_SOURCE = "data/left.bmp";
constexpr double LEFT_X = 0.1;
constexpr double LEFT_Y = 0.5;
constexpr double LEFT_WIDTH = 0.05;
constexpr double LEFT_HEIGHT = 0.1;

// The constants for the right arrow button.
constexpr const char* RIGHT_SOURCE = "data/right.bmp";
constexpr double RIGHT_X = 1 - LEFT_X;
constexpr double RIGHT_Y = LEFT_Y;
constexpr double RIGHT_WIDTH = LEFT_WIDTH;
constexpr double RIGHT_HEIGHT = LEFT_HEIGHT;

// The constants for the card page.
constexpr double PAGE_NAME_X = 0.375;
constexpr double PAGE_VALUE_X = 0.725;
constexpr double PAGE_Y = 0.4;
constexpr double PAGE_Y_SHIFT = 0.075;
constexpr double PAGE_WIDTH = INCOMPATIBLE_WIDTH / 2;
constexpr double PAGE_HEIGHT = INCOMPATIBLE_HEIGHT / 2;
constexpr double PAGE_SEPARATION = PAGE_WIDTH / 20;

// The constants for the minus buttons.
constexpr double MINUS_X = PAGE_VALUE_X - 0.1;
constexpr double MINUS_Y = PAGE_Y;
constexpr double MINUS_Y_SHIFT = PAGE_Y_SHIFT;
constexpr double MINUS_WIDTH = 0.75 * PAGE_HEIGHT;
constexpr double MINUS_HEIGHT = MINUS_WIDTH;

// The constants for the plus buttons.
constexpr double PLUS_X = 2 * PAGE_VALUE_X - MINUS_X;
constexpr double PLUS_Y = MINUS_Y;
constexpr double PLUS_Y_SHIFT = MINUS_Y_SHIFT;
constexpr double PLUS_WIDTH = MINUS_WIDTH;
constexpr double PLUS_HEIGHT = MINUS_HEIGHT;

// The constants for the generate button.
constexpr const char* GENERATE_STRING = "Generate";
constexpr double GENERATE_X = PAGE_VALUE_X;
constexpr double GENERATE_Y = PAGE_Y;
constexpr double GENERATE_Y_SHIFT = PAGE_Y_SHIFT;
constexpr double GENERATE_WIDTH = PAGE_WIDTH;
constexpr double GENERATE_HEIGHT = PAGE_HEIGHT;
constexpr double GENERATE_SEPARATION = PAGE_SEPARATION;

// The constants for the description button.
#define DESCRIPTION_STRING (ALL_DECK_CODES[page * PAGE_COUNT + i]->get_description())
constexpr double DESCRIPTION_X = CARD_X;
constexpr double DESCRIPTION_Y = CARD_Y;
constexpr double DESCRIPTION_WIDTH = CARD_WIDTH;
constexpr double DESCRIPTION_HEIGHT = CARD_HEIGHT;
constexpr double DESCRIPTION_MAX_WIDTH = CARD_MAX_WIDTH;
constexpr double DESCRIPTION_SEPARATION_X = CARD_SEPARATION_X;
constexpr double DESCRIPTION_SEPARATION_Y = CARD_SEPARATION_Y;
constexpr Renderer::Justification DESCRIPTION_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// The constants for the deck error sprite.
#define INVALID_SIZE_STRING (         \
	"A deck must consist of exactly " \
	+ std::to_string(DECK_SIZE)       \
	+ " cards."                       \
)
constexpr const char* NO_BASICS_STRING =
	"A deck must have at least 1 fighter that doesn't rank up from another fighter."
;
constexpr double DECK_ERROR_X = INCOMPATIBLE_X;
constexpr double DECK_ERROR_Y = INCOMPATIBLE_Y;
constexpr double DECK_ERROR_WIDTH = 0.75 * INCOMPATIBLE_WIDTH;
constexpr double DECK_ERROR_HEIGHT = 2 * DECK_ERROR_WIDTH;
constexpr double DECK_ERROR_MAX_WIDTH = 0.75;
constexpr double DECK_ERROR_SEPARATION_X = DECK_ERROR_WIDTH / 20;
constexpr double DECK_ERROR_SEPARATION_Y = 0.4 * DECK_ERROR_HEIGHT;
constexpr Renderer::Justification DECK_ERROR_JUSTIFICATION = INCOMPATIBLE_JUSTIFICATION;
//}

// Main Game Setup Constants
//{
// Constants for the mulligan fail sprite.
#define MULLIGAN_FAIL_STRING (                         \
	std::string(opposing ? "Your opponent's" : "Your") \
	+ " hand has no playable fighters."                \
)
constexpr double MULLIGAN_FAIL_X = 0.5;
constexpr double MULLIGAN_FAIL_Y = 0.5;
constexpr double MULLIGAN_FAIL_WIDTH = DECK_ERROR_WIDTH;
constexpr double MULLIGAN_FAIL_HEIGHT = DECK_ERROR_HEIGHT;
constexpr double MULLIGAN_FAIL_MAX_WIDTH = DECK_ERROR_MAX_WIDTH;
constexpr double MULLIGAN_FAIL_SEPARATION_X = DECK_ERROR_SEPARATION_X;
constexpr double MULLIGAN_FAIL_SEPARATION_Y = DECK_ERROR_SEPARATION_Y;
constexpr Renderer::Justification MULLIGAN_FAIL_JUSTIFICATION = DECK_ERROR_JUSTIFICATION;

// Constants for the new mulligan sprite.
#define NEW_MULLIGAN_STRING (                       \
	std::string(opposing ? "Your opponent" : "You") \
	+ " will redraw "                               \
	+ (opposing ? "their" : "your")                 \
	+ " starting hand."                             \
)
constexpr double NEW_MULLIGAN_X = MULLIGAN_FAIL_X;
constexpr double NEW_MULLIGAN_Y = MULLIGAN_FAIL_Y;
constexpr double NEW_MULLIGAN_WIDTH = MULLIGAN_FAIL_WIDTH;
constexpr double NEW_MULLIGAN_HEIGHT = MULLIGAN_FAIL_HEIGHT;
constexpr double NEW_MULLIGAN_MAX_WIDTH = MULLIGAN_FAIL_MAX_WIDTH;
constexpr double NEW_MULLIGAN_SEPARATION_X = MULLIGAN_FAIL_SEPARATION_X;
constexpr double NEW_MULLIGAN_SEPARATION_Y = MULLIGAN_FAIL_SEPARATION_Y;
constexpr Renderer::Justification NEW_MULLIGAN_JUSTIFICATION = MULLIGAN_FAIL_JUSTIFICATION;

// Constants for the player ordering sprite.
#define ORDER_STRING ("You go " + std::string(turn ? "second" : "first") + ".")
constexpr double ORDER_X = NEW_MULLIGAN_X;
constexpr double ORDER_Y = NEW_MULLIGAN_Y;
constexpr double ORDER_WIDTH = NEW_MULLIGAN_WIDTH;
constexpr double ORDER_HEIGHT = NEW_MULLIGAN_HEIGHT;
constexpr double ORDER_MAX_WIDTH = NEW_MULLIGAN_MAX_WIDTH;
constexpr double ORDER_SEPARATION_X = NEW_MULLIGAN_SEPARATION_X;
constexpr double ORDER_SEPARATION_Y = NEW_MULLIGAN_SEPARATION_Y;
constexpr Renderer::Justification ORDER_JUSTIFICATION = NEW_MULLIGAN_JUSTIFICATION;

// Constants for the life cards announcement sprite.
#define LIFE_STRING (                               \
	std::string(opposing ? "Your opponent" : "You") \
	+ " set out "                                   \
	+ std::to_string(LIFE_SIZE)                          \
	+ " life cards."                                \
)
constexpr double LIFE_X = ORDER_X;
constexpr double LIFE_Y = ORDER_Y;
constexpr double LIFE_WIDTH = ORDER_WIDTH;
constexpr double LIFE_HEIGHT = ORDER_HEIGHT;
constexpr double LIFE_MAX_WIDTH = ORDER_MAX_WIDTH;
constexpr double LIFE_SEPARATION_X = ORDER_SEPARATION_X;
constexpr double LIFE_SEPARATION_Y = ORDER_SEPARATION_Y;
constexpr Renderer::Justification LIFE_JUSTIFICATION = ORDER_JUSTIFICATION;

// Constants for the bonus draw sprite.
#define BONUS_DRAW_STRING (        \
	"You may draw up to "          \
	+ std::to_string(difference)   \
	+ " extra card"                \
	+ (difference == 1 ? "" : "s") \
	+ "!"                          \
)
constexpr double BONUS_DRAW_X = LIFE_X;
constexpr double BONUS_DRAW_Y = LIFE_Y;
constexpr double BONUS_DRAW_WIDTH = LIFE_WIDTH;
constexpr double BONUS_DRAW_HEIGHT = LIFE_HEIGHT;
constexpr double BONUS_DRAW_MAX_WIDTH = LIFE_MAX_WIDTH;
constexpr double BONUS_DRAW_SEPARATION_X = LIFE_SEPARATION_X;
constexpr double BONUS_DRAW_SEPARATION_Y = LIFE_SEPARATION_Y;
constexpr Renderer::Justification BONUS_DRAW_JUSTIFICATION = LIFE_JUSTIFICATION;

// Constants for the opponent's bonus draw sprite.
#define NO_BONUS_DRAW_STRING (      \
	"Your opponent may draw up to " \
	+ std::to_string(-difference)   \
	+ " extra card"                 \
	+ (difference == -1 ? "" : "s") \
	+ "..."                         \
)
constexpr double NO_BONUS_DRAW_X = BONUS_DRAW_X;
constexpr double NO_BONUS_DRAW_Y = BONUS_DRAW_Y;
constexpr double NO_BONUS_DRAW_WIDTH = BONUS_DRAW_WIDTH;
constexpr double NO_BONUS_DRAW_HEIGHT = BONUS_DRAW_HEIGHT;
constexpr double NO_BONUS_DRAW_MAX_WIDTH = BONUS_DRAW_MAX_WIDTH;
constexpr double NO_BONUS_DRAW_SEPARATION_X = BONUS_DRAW_SEPARATION_X;
constexpr double NO_BONUS_DRAW_SEPARATION_Y = BONUS_DRAW_SEPARATION_Y;
constexpr Renderer::Justification NO_BONUS_DRAW_JUSTIFICATION = BONUS_DRAW_JUSTIFICATION;

// Constants for the opponent's draw sprite.
#define OPPONENT_DRAW_STRING (  \
	"Your opponent drew "       \
	+ std::to_string(draws)     \
	+ " card"                   \
	+ (draws == 1 ? "." : "s.") \
)
constexpr double OPPONENT_DRAW_X = NO_BONUS_DRAW_X;
constexpr double OPPONENT_DRAW_Y = NO_BONUS_DRAW_Y;
constexpr double OPPONENT_DRAW_WIDTH = NO_BONUS_DRAW_WIDTH;
constexpr double OPPONENT_DRAW_HEIGHT = NO_BONUS_DRAW_HEIGHT;
constexpr double OPPONENT_DRAW_MAX_WIDTH = NO_BONUS_DRAW_MAX_WIDTH;
constexpr double OPPONENT_DRAW_SEPARATION_X = NO_BONUS_DRAW_SEPARATION_X;
constexpr double OPPONENT_DRAW_SEPARATION_Y = NO_BONUS_DRAW_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_DRAW_JUSTIFICATION = NO_BONUS_DRAW_JUSTIFICATION;

// Constants for the bonus sprite.
#define BONUS_STRING (           \
	"Bonus Draw ("               \
	+ std::to_string(difference) \
	+ " max)"                    \
)
constexpr double BONUS_X = PORT_X;
constexpr double BONUS_Y = PORT_Y;
constexpr double BONUS_SHIFT = PORT_SHIFT;
constexpr double BONUS_WIDTH = PORT_WIDTH;
constexpr double BONUS_HEIGHT = PORT_HEIGHT;
constexpr double BONUS_SEPARATION = PORT_SEPARATION;

// Constants for the mulligan sprite.
#define MULLIGAN_STRING (                   \
	"Both players will draw "               \
	+ std::to_string(HAND_SIZE)             \
	+ " cards to form their starting hand." \
) 
constexpr double MULLIGAN_X = OPPONENT_DRAW_X;
constexpr double MULLIGAN_Y = OPPONENT_DRAW_Y;
constexpr double MULLIGAN_WIDTH = OPPONENT_DRAW_WIDTH;
constexpr double MULLIGAN_HEIGHT = OPPONENT_DRAW_HEIGHT;
constexpr double MULLIGAN_MAX_WIDTH = OPPONENT_DRAW_MAX_WIDTH;
constexpr double MULLIGAN_SEPARATION_X = OPPONENT_DRAW_SEPARATION_X;
constexpr double MULLIGAN_SEPARATION_Y = OPPONENT_DRAW_SEPARATION_Y;
constexpr Renderer::Justification MULLIGAN_JUSTIFICATION = OPPONENT_DRAW_JUSTIFICATION;

// Constants for the active fighter sprite.
constexpr const char* SET_ACTIVE_STRING =
	"Choose a basic fighter to be your active fighter!"
;
constexpr double SET_ACTIVE_X = MULLIGAN_X;
constexpr double SET_ACTIVE_Y = MULLIGAN_Y;
constexpr double SET_ACTIVE_WIDTH = MULLIGAN_WIDTH;
constexpr double SET_ACTIVE_HEIGHT = MULLIGAN_HEIGHT;
constexpr double SET_ACTIVE_MAX_WIDTH = MULLIGAN_MAX_WIDTH;
constexpr double SET_ACTIVE_SEPARATION_X = MULLIGAN_SEPARATION_X;
constexpr double SET_ACTIVE_SEPARATION_Y = MULLIGAN_SEPARATION_Y;
constexpr Renderer::Justification SET_ACTIVE_JUSTIFICATION = MULLIGAN_JUSTIFICATION;

// Constants for the basic fighter sprite.
constexpr const char* BASIC_FIGHTER_STRING = "Choose a basic fighter:";
constexpr double BASIC_FIGHTER_X = BUILDER_X;
constexpr double BASIC_FIGHTER_Y = BUILDER_Y;
constexpr double BASIC_FIGHTER_WIDTH = 0.75 * BUILDER_WIDTH;
constexpr double BASIC_FIGHTER_HEIGHT = 2 * BASIC_FIGHTER_WIDTH;
constexpr double BASIC_FIGHTER_SEPARATION = BASIC_FIGHTER_WIDTH / 20;

// The constants for the choice button.
constexpr const char* CHOICE_STRING = "Choose";
constexpr double CHOICE_X = GENERATE_X;
constexpr double CHOICE_Y = GENERATE_Y;
constexpr double CHOICE_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double CHOICE_WIDTH = GENERATE_WIDTH;
constexpr double CHOICE_HEIGHT = GENERATE_HEIGHT;
constexpr double CHOICE_SEPARATION = GENERATE_SEPARATION;

// The constants for the game sprite.
#define GAME_STRING (                                 \
	winner == TIE ? "It's a tie!" :                   \
	"You " + std::string(winner ? "lose..." : "win!") \
)
constexpr double GAME_X = 0.5;
constexpr double GAME_Y = 0.5;
constexpr double GAME_WIDTH = 0.875 * TITLE_WIDTH;
constexpr double GAME_HEIGHT = 2 * GAME_WIDTH;
constexpr double GAME_SEPARATION = GAME_WIDTH / 20;

// The constants for the store size sprite.
#define STORE_SIZE_STRING (    \
	"Contains "                \
	+ std::to_string(size())   \
	+ " card"                  \
	+ (size() == 1 ? "" : "s") \
	+ ":"                      \
)
constexpr double STORE_SIZE_X = BUILDER_X;
constexpr double STORE_SIZE_Y = BUILDER_Y;
constexpr double STORE_SIZE_WIDTH = 0.75 * BUILDER_WIDTH;
constexpr double STORE_SIZE_HEIGHT = 2 * STORE_SIZE_WIDTH;
constexpr double STORE_SIZE_SEPARATION = STORE_SIZE_WIDTH / 20;
//}

// Duel Board Constants
//{
// The player's Buttons
//{
// Constants for the player's deck button.
constexpr const char* YOUR_DECK_STRING = "Your\nDeck";
constexpr double YOUR_DECK_X = 0.85;
constexpr double YOUR_DECK_Y = 0.6;
constexpr double YOUR_DECK_WIDTH = 0.02;
constexpr double YOUR_DECK_HEIGHT = 2 * YOUR_DECK_WIDTH;
constexpr double YOUR_DECK_MAX_WIDTH = 0;
constexpr double YOUR_DECK_SEPARATION_X = YOUR_DECK_WIDTH / 20;
constexpr double YOUR_DECK_SEPARATION_Y = YOUR_DECK_HEIGHT / 5;
constexpr Renderer::Justification YOUR_DECK_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// Constants for the player's trash button.
constexpr const char* YOUR_TRASH_STRING = "Your\nTrash";
constexpr double YOUR_TRASH_X = YOUR_DECK_X;
constexpr double YOUR_TRASH_Y = YOUR_DECK_Y + 0.175;
constexpr double YOUR_TRASH_WIDTH = YOUR_DECK_WIDTH;
constexpr double YOUR_TRASH_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double YOUR_TRASH_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double YOUR_TRASH_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double YOUR_TRASH_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification YOUR_TRASH_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;

// Constants for the player's hand button.
constexpr const char* YOUR_HAND_STRING = "Your Hand";
constexpr double YOUR_HAND_X = 0.5;
constexpr double YOUR_HAND_Y = 0.95;
constexpr double YOUR_HAND_WIDTH = YOUR_DECK_WIDTH;
constexpr double YOUR_HAND_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double YOUR_HAND_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double YOUR_HAND_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double YOUR_HAND_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification YOUR_HAND_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;

// Constants for the player's life cards button.
constexpr const char* YOUR_LIFE_STRING = "Your\nLife\nCards";
constexpr double YOUR_LIFE_X = 1 - YOUR_DECK_X;
constexpr double YOUR_LIFE_Y = 0.7;
constexpr double YOUR_LIFE_WIDTH = YOUR_DECK_WIDTH;
constexpr double YOUR_LIFE_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double YOUR_LIFE_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double YOUR_LIFE_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double YOUR_LIFE_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification YOUR_LIFE_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;

// Constants for the player's active fighter button.
constexpr const char* YOUR_ACTIVE_STRING = "Your Active\nFighter";
constexpr double YOUR_ACTIVE_X = YOUR_HAND_X;
constexpr double YOUR_ACTIVE_Y = YOUR_DECK_Y;
constexpr double YOUR_ACTIVE_WIDTH = YOUR_DECK_WIDTH;
constexpr double YOUR_ACTIVE_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double YOUR_ACTIVE_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double YOUR_ACTIVE_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double YOUR_ACTIVE_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification YOUR_ACTIVE_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;

// Constants for the player's benched fighter button.
constexpr const char* YOUR_BENCH_STRING = "Your Benched\nFighters";
constexpr double YOUR_BENCH_X = YOUR_HAND_X;
constexpr double YOUR_BENCH_Y = YOUR_TRASH_Y;
constexpr double YOUR_BENCH_WIDTH = YOUR_DECK_WIDTH;
constexpr double YOUR_BENCH_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double YOUR_BENCH_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double YOUR_BENCH_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double YOUR_BENCH_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification YOUR_BENCH_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;

// Constants for the player's effects button.
constexpr const char* YOUR_EFFECTS_STRING = "Your\nEffects";
constexpr double YOUR_EFFECTS_X = QUIT_X_ALT;
constexpr double YOUR_EFFECTS_Y = QUIT_Y;
constexpr double YOUR_EFFECTS_WIDTH = YOUR_DECK_WIDTH;
constexpr double YOUR_EFFECTS_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double YOUR_EFFECTS_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double YOUR_EFFECTS_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double YOUR_EFFECTS_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification YOUR_EFFECTS_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;
//}

// The opponent's buttons
//{
// Constants for the opponent's deck button.
constexpr const char* OPPONENT_DECK_STRING = "Opponent's\nDeck";
constexpr double OPPONENT_DECK_X = YOUR_DECK_X;
constexpr double OPPONENT_DECK_Y = 1 - YOUR_DECK_Y;
constexpr double OPPONENT_DECK_WIDTH = YOUR_DECK_WIDTH;
constexpr double OPPONENT_DECK_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double OPPONENT_DECK_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double OPPONENT_DECK_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double OPPONENT_DECK_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_DECK_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;

// Constants for the opponent's trash button.
constexpr const char* OPPONENT_TRASH_STRING = "Opponent's\nTrash";
constexpr double OPPONENT_TRASH_X = OPPONENT_DECK_X;
constexpr double OPPONENT_TRASH_Y = 1 - YOUR_TRASH_Y;
constexpr double OPPONENT_TRASH_WIDTH = OPPONENT_DECK_WIDTH;
constexpr double OPPONENT_TRASH_HEIGHT = OPPONENT_DECK_HEIGHT;
constexpr double OPPONENT_TRASH_MAX_WIDTH = OPPONENT_DECK_MAX_WIDTH;
constexpr double OPPONENT_TRASH_SEPARATION_X = OPPONENT_DECK_SEPARATION_X;
constexpr double OPPONENT_TRASH_SEPARATION_Y = OPPONENT_DECK_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_TRASH_JUSTIFICATION = OPPONENT_DECK_JUSTIFICATION;

// Constants for the opponent's hand button.
constexpr const char* OPPONENT_HAND_STRING = "Opponent's Hand";
constexpr double OPPONENT_HAND_X = 0.5;
constexpr double OPPONENT_HAND_Y = 1 - YOUR_HAND_Y;
constexpr double OPPONENT_HAND_WIDTH = OPPONENT_DECK_WIDTH;
constexpr double OPPONENT_HAND_HEIGHT = OPPONENT_DECK_HEIGHT;
constexpr double OPPONENT_HAND_MAX_WIDTH = OPPONENT_DECK_MAX_WIDTH;
constexpr double OPPONENT_HAND_SEPARATION_X = OPPONENT_DECK_SEPARATION_X;
constexpr double OPPONENT_HAND_SEPARATION_Y = OPPONENT_DECK_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_HAND_JUSTIFICATION = OPPONENT_DECK_JUSTIFICATION;

// Constants for the opponent's life cards button.
constexpr const char* OPPONENT_LIFE_STRING = "Opponent's\nLife\nCards";
constexpr double OPPONENT_LIFE_X = 1 - OPPONENT_DECK_X;
constexpr double OPPONENT_LIFE_Y = 1 - YOUR_LIFE_Y;
constexpr double OPPONENT_LIFE_WIDTH = OPPONENT_DECK_WIDTH;
constexpr double OPPONENT_LIFE_HEIGHT = OPPONENT_DECK_HEIGHT;
constexpr double OPPONENT_LIFE_MAX_WIDTH = OPPONENT_DECK_MAX_WIDTH;
constexpr double OPPONENT_LIFE_SEPARATION_X = OPPONENT_DECK_SEPARATION_X;
constexpr double OPPONENT_LIFE_SEPARATION_Y = OPPONENT_DECK_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_LIFE_JUSTIFICATION = OPPONENT_DECK_JUSTIFICATION;

// Constants for the opponent's active fighter button.
constexpr const char* OPPONENT_ACTIVE_STRING = "Opponent's\nActive Fighter";
constexpr double OPPONENT_ACTIVE_X = OPPONENT_HAND_X;
constexpr double OPPONENT_ACTIVE_Y = OPPONENT_DECK_Y;
constexpr double OPPONENT_ACTIVE_WIDTH = OPPONENT_DECK_WIDTH;
constexpr double OPPONENT_ACTIVE_HEIGHT = OPPONENT_DECK_HEIGHT;
constexpr double OPPONENT_ACTIVE_MAX_WIDTH = OPPONENT_DECK_MAX_WIDTH;
constexpr double OPPONENT_ACTIVE_SEPARATION_X = OPPONENT_DECK_SEPARATION_X;
constexpr double OPPONENT_ACTIVE_SEPARATION_Y = OPPONENT_DECK_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_ACTIVE_JUSTIFICATION = OPPONENT_DECK_JUSTIFICATION;

// Constants for the opponent's benched fighter button.
constexpr const char* OPPONENT_BENCH_STRING = "Opponent's\nBenched Fighters";
constexpr double OPPONENT_BENCH_X = OPPONENT_HAND_X;
constexpr double OPPONENT_BENCH_Y = OPPONENT_TRASH_Y;
constexpr double OPPONENT_BENCH_WIDTH = OPPONENT_DECK_WIDTH;
constexpr double OPPONENT_BENCH_HEIGHT = OPPONENT_DECK_HEIGHT;
constexpr double OPPONENT_BENCH_MAX_WIDTH = OPPONENT_DECK_MAX_WIDTH;
constexpr double OPPONENT_BENCH_SEPARATION_X = OPPONENT_DECK_SEPARATION_X;
constexpr double OPPONENT_BENCH_SEPARATION_Y = OPPONENT_DECK_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_BENCH_JUSTIFICATION = OPPONENT_DECK_JUSTIFICATION;

// Constants for the opponent's effects button.
constexpr const char* OPPONENT_EFFECTS_STRING = "Opponent's\nEffects";
constexpr double OPPONENT_EFFECTS_X = QUIT_X_ALT;
constexpr double OPPONENT_EFFECTS_Y = 1 - QUIT_Y;
constexpr double OPPONENT_EFFECTS_WIDTH = YOUR_DECK_WIDTH;
constexpr double OPPONENT_EFFECTS_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double OPPONENT_EFFECTS_MAX_WIDTH = YOUR_DECK_MAX_WIDTH;
constexpr double OPPONENT_EFFECTS_SEPARATION_X = YOUR_DECK_SEPARATION_X;
constexpr double OPPONENT_EFFECTS_SEPARATION_Y = YOUR_DECK_SEPARATION_Y;
constexpr Renderer::Justification OPPONENT_EFFECTS_JUSTIFICATION = YOUR_DECK_JUSTIFICATION;
//}

// Other buttons
//{
// Constants for the void button.
constexpr const char* THE_VOID_STRING = "The Void";
constexpr double THE_VOID_X = YOUR_LIFE_X;
constexpr double THE_VOID_Y = 0.5;
constexpr double THE_VOID_WIDTH = YOUR_DECK_WIDTH;
constexpr double THE_VOID_HEIGHT = YOUR_DECK_HEIGHT;
constexpr double THE_VOID_SEPARATION = YOUR_DECK_SEPARATION_X;

	
// Constants for the end turn button.
constexpr const char* END_TURN_STRING = DONE_STRING;
constexpr double END_TURN_X = DONE_X;
constexpr double END_TURN_Y = DONE_Y;
constexpr double END_TURN_WIDTH = DONE_WIDTH;
constexpr double END_TURN_HEIGHT = DONE_HEIGHT;
constexpr double END_TURN_SEPARATION = DONE_SEPARATION;

// Constants for the concede button.
constexpr const char* CONCEDE_STRING = QUIT_STRING;
constexpr double CONCEDE_X = END_TURN_X;
constexpr double CONCEDE_Y = 1 - QUIT_Y;
constexpr double CONCEDE_WIDTH = QUIT_WIDTH;
constexpr double CONCEDE_HEIGHT = QUIT_HEIGHT;
constexpr double CONCEDE_SEPARATION = QUIT_SEPARATION;
//}
//}

// Duel Constants
//{
// Constants for the last drawn card sprite.
#define LAST_DRAWN_STRING ("You drew\n" + last_drawn->get_name())
constexpr double LAST_DRAWN_X = 0.5;
constexpr double LAST_DRAWN_Y = 0.5;
constexpr double LAST_DRAWN_WIDTH = 0.75 * TITLE_WIDTH;
constexpr double LAST_DRAWN_HEIGHT = 2 * LAST_DRAWN_WIDTH;
constexpr double LAST_DRAWN_MAX_WIDTH = 0;
constexpr double LAST_DRAWN_SEPARATION_X = LAST_DRAWN_WIDTH / 20;
constexpr double LAST_DRAWN_SEPARATION_Y = LAST_DRAWN_HEIGHT / 2;
constexpr Renderer::Justification LAST_DRAWN_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// Constants for the player's concede sprite.
constexpr const char* PLAYER_CONCEDE_STRING = "You conceded...";
constexpr double PLAYER_CONCEDE_X = 0.5;
constexpr double PLAYER_CONCEDE_Y = 0.5;
constexpr double PLAYER_CONCEDE_WIDTH = 0.5 * TITLE_WIDTH;
constexpr double PLAYER_CONCEDE_HEIGHT = 2 * PLAYER_CONCEDE_WIDTH;
constexpr double PLAYER_CONCEDE_MAX_WIDTH = 0;
constexpr double PLAYER_CONCEDE_SEPARATION_X = PLAYER_CONCEDE_WIDTH / 20;
constexpr double PLAYER_CONCEDE_SEPARATION_Y = PLAYER_CONCEDE_HEIGHT / 2;
constexpr Renderer::Justification PLAYER_CONCEDE_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// Constants for the opponent's concede sprite.
constexpr const char* OPPONENT_CONCEDE_STRING = "Your opponent\nconceded!";
constexpr double OPPONENT_CONCEDE_X = 0.5;
constexpr double OPPONENT_CONCEDE_Y = 0.5;
constexpr double OPPONENT_CONCEDE_WIDTH = 0.5 * TITLE_WIDTH;
constexpr double OPPONENT_CONCEDE_HEIGHT = 2 * OPPONENT_CONCEDE_WIDTH;
constexpr double OPPONENT_CONCEDE_MAX_WIDTH = 0;
constexpr double OPPONENT_CONCEDE_SEPARATION_X = OPPONENT_CONCEDE_WIDTH / 20;
constexpr double OPPONENT_CONCEDE_SEPARATION_Y = OPPONENT_CONCEDE_HEIGHT / 2;
constexpr Renderer::Justification OPPONENT_CONCEDE_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// Constants for the opponent's concede sprite.
#define VIEW_SIZE_STRING (     \
	"Contains "                \
	+ std::to_string(size())   \
	+ " card"                  \
	+ (size() == 1 ? "" : "s") \
	+ "."                      \
)
constexpr double VIEW_SIZE_X = 0.5;
constexpr double VIEW_SIZE_Y = 0.5;
constexpr double VIEW_SIZE_WIDTH = 0.75 * TITLE_WIDTH;
constexpr double VIEW_SIZE_HEIGHT = 2 * VIEW_SIZE_WIDTH;
constexpr double VIEW_SIZE_MAX_WIDTH = 0;
constexpr double VIEW_SIZE_SEPARATION_X = VIEW_SIZE_WIDTH / 20;
constexpr double VIEW_SIZE_SEPARATION_Y = VIEW_SIZE_HEIGHT / 2;
constexpr Renderer::Justification VIEW_SIZE_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// Constants for the fighter's energy button.
constexpr const char* FIGHTER_ENERGY_STRING = "Energy";
constexpr double FIGHTER_ENERGY_X = 0.125;
constexpr double FIGHTER_ENERGY_Y = 0.35;
constexpr double FIGHTER_ENERGY_WIDTH = 0.02;
constexpr double FIGHTER_ENERGY_HEIGHT = 2 * FIGHTER_ENERGY_WIDTH;
constexpr double FIGHTER_ENERGY_SEPARATION = FIGHTER_ENERGY_WIDTH / 20;

// Constants for the fighter's effects button.
constexpr const char* FIGHTER_EFFECTS_STRING = "Effects";
constexpr double FIGHTER_EFFECTS_X = FIGHTER_ENERGY_X;
constexpr double FIGHTER_EFFECTS_Y = 1 - FIGHTER_ENERGY_Y;
constexpr double FIGHTER_EFFECTS_WIDTH = FIGHTER_ENERGY_WIDTH;
constexpr double FIGHTER_EFFECTS_HEIGHT = 2 * FIGHTER_EFFECTS_WIDTH;
constexpr double FIGHTER_EFFECTS_SEPARATION = FIGHTER_EFFECTS_WIDTH / 20;

// The constants for the energy size sprite.
#define ENERGY_SIZE_STRING ("Contains " + std::to_string(energy.size()) + " cards:")
constexpr double ENERGY_SIZE_X = BUILDER_X;
constexpr double ENERGY_SIZE_Y = BUILDER_Y;
constexpr double ENERGY_SIZE_WIDTH = 0.75 * BUILDER_WIDTH;
constexpr double ENERGY_SIZE_HEIGHT = 2 * ENERGY_SIZE_WIDTH;
constexpr double ENERGY_SIZE_SEPARATION = ENERGY_SIZE_WIDTH / 20;

// Constants for the opponent's concede sprite.
#define DRAW_FAIL_STRING (                           \
	std::string(turn ? "Your opponenent's" : "Your") \
	+ " deck is empty, so "                          \
	+ (turn ? "they" : "you")                        \
	+ " can't draw at the start of "                 \
	+ (turn ? "their" : "your")                      \
	+ " turn"                                        \
	+ (turn ? "!" : "...")                           \
)
constexpr double DRAW_FAIL_X = 0.5;
constexpr double DRAW_FAIL_Y = 0.5;
constexpr double DRAW_FAIL_WIDTH = 0.5 * TITLE_WIDTH;
constexpr double DRAW_FAIL_HEIGHT = 2 * DRAW_FAIL_WIDTH;
constexpr double DRAW_FAIL_MAX_WIDTH = 0.75;
constexpr double DRAW_FAIL_SEPARATION_X = DRAW_FAIL_WIDTH / 20;
constexpr double DRAW_FAIL_SEPARATION_Y = DRAW_FAIL_HEIGHT / 2;
constexpr Renderer::Justification DRAW_FAIL_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// The constants for the play card button.
constexpr const char* PLAY_CARD_STRING = "Play";
constexpr double PLAY_CARD_X = GENERATE_X;
constexpr double PLAY_CARD_Y = GENERATE_Y;
constexpr double PLAY_CARD_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double PLAY_CARD_WIDTH = GENERATE_WIDTH;
constexpr double PLAY_CARD_HEIGHT = GENERATE_HEIGHT;
constexpr double PLAY_CARD_SEPARATION = GENERATE_SEPARATION;

// The constants for the attachment sprite.
#define ATTACHMENT_STRING (                          \
	"Your opponent is choosing a fighter to attach " \
	+ e.get_name()                                   \
	+ " to."                                         \
)
constexpr double ATTACHMENT_X = 0.5;
constexpr double ATTACHMENT_Y = 0.5;
constexpr double ATTACHMENT_WIDTH = 0.5 * TITLE_WIDTH;
constexpr double ATTACHMENT_HEIGHT = 2 * ATTACHMENT_WIDTH;
constexpr double ATTACHMENT_MAX_WIDTH = 0.75;
constexpr double ATTACHMENT_SEPARATION_X = ATTACHMENT_WIDTH / 20;
constexpr double ATTACHMENT_SEPARATION_Y = ATTACHMENT_HEIGHT / 5;
constexpr Renderer::Justification ATTACHMENT_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// The constants for the attach button.
constexpr const char* ATTACH_STRING = "Attach";
constexpr double ATTACH_X = GENERATE_X;
constexpr double ATTACH_Y = GENERATE_Y;
constexpr double ATTACH_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double ATTACH_WIDTH = GENERATE_WIDTH;
constexpr double ATTACH_HEIGHT = GENERATE_HEIGHT;
constexpr double ATTACH_SEPARATION = GENERATE_SEPARATION;

// The constants for the energy value sprites.
#define ENERGY_VALUE_STRING std::to_string(energy[i].get_value(element))
constexpr double ENERGY_VALUE_X = GENERATE_X;
constexpr double ENERGY_VALUE_Y = GENERATE_Y;
constexpr double ENERGY_VALUE_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double ENERGY_VALUE_WIDTH = GENERATE_WIDTH;
constexpr double ENERGY_VALUE_HEIGHT = GENERATE_HEIGHT;
constexpr double ENERGY_VALUE_SEPARATION = GENERATE_SEPARATION;

// The constants for the total energy value sprite.
#define TOTAL_ENERGY_STRING ( \
	"Total Energy: "          \
	+ std::to_string(total)   \
)
constexpr double TOTAL_ENERGY_X = 0.5;
constexpr double TOTAL_ENERGY_Y = 0.9;
constexpr double TOTAL_ENERGY_WIDTH = GENERATE_WIDTH;
constexpr double TOTAL_ENERGY_HEIGHT = GENERATE_HEIGHT;
constexpr double TOTAL_ENERGY_SEPARATION = GENERATE_SEPARATION;

// The constants for the rank up sprite.
#define RANK_UP_STRING (                                   \
	"Your opponent is choosing a fighter to rank up into " \
	+ f.get_name()                                         \
	+ "."                                                  \
)
constexpr double RANK_UP_X = 0.5;
constexpr double RANK_UP_Y = 0.5;
constexpr double RANK_UP_WIDTH = 0.5 * TITLE_WIDTH;
constexpr double RANK_UP_HEIGHT = 2 * RANK_UP_WIDTH;
constexpr double RANK_UP_MAX_WIDTH = 0.75;
constexpr double RANK_UP_SEPARATION_X = RANK_UP_WIDTH / 20;
constexpr double RANK_UP_SEPARATION_Y = RANK_UP_HEIGHT / 5;
constexpr Renderer::Justification RANK_UP_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;

// The constants for the attachment preview button.
#define ATTACH_PREVIEW_STRING e.get_name()
constexpr double ATTACH_PREVIEW_X = 0.5;
constexpr double ATTACH_PREVIEW_Y = 0.1;
constexpr double ATTACH_PREVIEW_WIDTH = GENERATE_WIDTH;
constexpr double ATTACH_PREVIEW_HEIGHT = GENERATE_HEIGHT;
constexpr double ATTACH_PREVIEW_SEPARATION = GENERATE_SEPARATION;

// The constants for the rank up buttons.
constexpr const char* RANK_STRING = "Rank up";
constexpr double RANK_X = GENERATE_X;
constexpr double RANK_Y = GENERATE_Y;
constexpr double RANK_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double RANK_WIDTH = GENERATE_WIDTH;
constexpr double RANK_HEIGHT = GENERATE_HEIGHT;
constexpr double RANK_SEPARATION = GENERATE_SEPARATION;

// The constants for the rank up preview button.
#define RANK_PREVIEW_STRING f.get_name()
constexpr double RANK_PREVIEW_X = 0.5;
constexpr double RANK_PREVIEW_Y = 0.1;
constexpr double RANK_PREVIEW_WIDTH = GENERATE_WIDTH;
constexpr double RANK_PREVIEW_HEIGHT = GENERATE_HEIGHT;
constexpr double RANK_PREVIEW_SEPARATION = GENERATE_SEPARATION;

// The constants for the effects value sprites.
#define EFFECT_VALUE_STRING effect_values[page * PAGE_COUNT + i]
constexpr double EFFECT_VALUE_X = GENERATE_X;
constexpr double EFFECT_VALUE_Y = GENERATE_Y;
constexpr double EFFECT_VALUE_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double EFFECT_VALUE_WIDTH = GENERATE_WIDTH;
constexpr double EFFECT_VALUE_HEIGHT = GENERATE_HEIGHT;
constexpr double EFFECT_VALUE_SEPARATION = GENERATE_SEPARATION;

// The constants for the bench size sprite.
#define BENCH_SIZE_STRING (             \
	std::to_string(fighters.size() - 1) \
	+ " benched fighters:"              \
)
constexpr double BENCH_SIZE_X = 0.5;
constexpr double BENCH_SIZE_Y = 0.1;
constexpr double BENCH_SIZE_WIDTH = GENERATE_WIDTH;
constexpr double BENCH_SIZE_HEIGHT = GENERATE_HEIGHT;
constexpr double BENCH_SIZE_SEPARATION = GENERATE_SEPARATION;

// The constants for the ability button.
constexpr const char* ABILITY_STRING = "Ability";
constexpr double ABILITY_X = GENERATE_X;
constexpr double ABILITY_Y = GENERATE_Y;
constexpr double ABILITY_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double ABILITY_WIDTH = GENERATE_WIDTH;
constexpr double ABILITY_HEIGHT = GENERATE_HEIGHT;
constexpr double ABILITY_SEPARATION = GENERATE_SEPARATION;

// Constants for the fighter's ability button.
constexpr const char* FIGHTER_ABILITY_STRING = "Ability";
constexpr double FIGHTER_ABILITY_X = 1 - FIGHTER_ENERGY_X;
constexpr double FIGHTER_ABILITY_Y = 0.25;
constexpr double FIGHTER_ABILITY_WIDTH = 0.02;
constexpr double FIGHTER_ABILITY_HEIGHT = 2 * FIGHTER_ABILITY_WIDTH;
constexpr double FIGHTER_ABILITY_SEPARATION = FIGHTER_ABILITY_WIDTH / 20;

// Constants for the fighter's attack button.
constexpr const char* FIGHTER_ATTACK_STRING = "Attack";
constexpr double FIGHTER_ATTACK_X = FIGHTER_ABILITY_X;
constexpr double FIGHTER_ATTACK_Y = 0.5;
constexpr double FIGHTER_ATTACK_WIDTH = 0.02;
constexpr double FIGHTER_ATTACK_HEIGHT = 2 * FIGHTER_ATTACK_WIDTH;
constexpr double FIGHTER_ATTACK_SEPARATION = FIGHTER_ATTACK_WIDTH / 20;

// Constants for the fighter's retreat button.
constexpr const char* FIGHTER_RETREAT_STRING = "Retreat";
constexpr double FIGHTER_RETREAT_X = FIGHTER_ATTACK_X;
constexpr double FIGHTER_RETREAT_Y = 0.75;
constexpr double FIGHTER_RETREAT_WIDTH = 0.02;
constexpr double FIGHTER_RETREAT_HEIGHT = 2 * FIGHTER_RETREAT_WIDTH;
constexpr double FIGHTER_RETREAT_SEPARATION = FIGHTER_RETREAT_WIDTH / 20;

// Constants for the retreat preview button.
#define RETREAT_PREVIEW_STRING fighters[0].get_name()
constexpr double RETREAT_PREVIEW_X = 0.5;
constexpr double RETREAT_PREVIEW_Y = 0.1;
constexpr double RETREAT_PREVIEW_WIDTH = GENERATE_WIDTH;
constexpr double RETREAT_PREVIEW_HEIGHT = GENERATE_HEIGHT;
constexpr double RETREAT_PREVIEW_SEPARATION = GENERATE_SEPARATION;

// The constants for the switch in buttons.
constexpr const char* SWITCH_IN_STRING = "Switch In";
constexpr double SWITCH_IN_X = GENERATE_X;
constexpr double SWITCH_IN_Y = GENERATE_Y;
constexpr double SWITCH_IN_Y_SHIFT = GENERATE_Y_SHIFT;
constexpr double SWITCH_IN_WIDTH = GENERATE_WIDTH;
constexpr double SWITCH_IN_HEIGHT = GENERATE_HEIGHT;
constexpr double SWITCH_IN_SEPARATION = GENERATE_SEPARATION;
//}

// Announcement Constants
//{
// Universal announcement constants.
//{
#define ANNOUNCEMENT_STRING announcement
constexpr double ANNOUNCEMENT_X = 0.5;
constexpr double ANNOUNCEMENT_Y = 0.5;
constexpr double ANNOUNCEMENT_WIDTH = 0.4 * TITLE_WIDTH;
constexpr double ANNOUNCEMENT_HEIGHT = 2 * ANNOUNCEMENT_WIDTH;
constexpr double ANNOUNCEMENT_MAX_WIDTH = 0.75;
constexpr double ANNOUNCEMENT_SEPARATION_X = ANNOUNCEMENT_WIDTH / 20;
constexpr double ANNOUNCEMENT_SEPARATION_Y = ANNOUNCEMENT_HEIGHT / 5;
constexpr Renderer::Justification ANNOUNCEMENT_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;
//}

// Announcement for playing a basic fighter.
//{
#define BENCHED_ANNOUNCEMENT (                      \
	std::string(opposing ? "Your opponent" : "You") \
	+ " played "                                    \
	+ f.get_name()                                  \
	+ " onto the bench."                            \
)
//}

// Announcement for the opponent drawing cards.
//{
#define DRAW_ANNOUNCEMENT (                         \
	std::string(opposing ? "Your opponent" : "You") \
	+ " drew "                                      \
	+ std::to_string(draws)                         \
	+ " card"                                       \
	+ (draws == 1 ? "" : "s")                       \
	+ "."                                           \
)
//}

// Announcement for the player drawing cards.
//{
#define LAST_DRAWN_ANNOUNCEMENT ( \
	"You drew "                   \
	+ last_drawn->get_name()      \
	+ "."                         \
)
//}

// Announcement for the played supporter card.
//{
#define SUPPORTER_ANNOUNCEMENT (                    \
	std::string(opposing ? "Your opponent" : "You") \
	+ " played "                                    \
	+ s.get_name()                                  \
	+ "."                                           \
)
//}

// Announcement for a discarded hand.
//{
#define DISCARD_ALL_ANNOUNCEMENT (                  \
	std::string(opposing ? "Your opponent" : "You") \
	+ " discarded "                                 \
	+ (opposing ? "their" : "your")                 \
	+ " hand!"                                      \
)
//}

// Announcement for an attached energy card.
//{
#define ATTACHMENT_ANNOUNCEMENT ( \
	e.get_name()                  \
	+ " was attached to "         \
	+ recipient->get_name()       \
	+ "."                         \
)
//}

// Announcement for a failed rank up attempt.
//{
#define UNRANKABLE_ANNOUNCEMENT (             \
	"None of your fighters can rank up into " \
	+ f.get_name()                            \
	+ "..."                                   \
)
//}

// Announcement for a successful rank up.
//{
#define RANK_UP_ANNOUNCEMENT (   \
	old_rank.get_name()          \
	+ " ranked up into "         \
	+ fighters[index].get_name() \
	+ "!"                        \
)
//}

// Announcement for an ability use.
//{
#define ABILITY_ANNOUNCEMENT (           \
	fighters[index].get_name()           \
	+ " used "                           \
	+ fighters[index].get_ability_name() \
	+ "."                                \
)
//}

// Announcement for a fighter switch in.
//{
#define SWITCH_IN_ANNOUNCEMENT (              \
	fighters[0].get_name()                    \
	+ " switched into the active position! " \
	+ fighters[index].get_name()              \
	+ " switched out to the bench."           \
)
//}

// Announcement to declare fighter empowerment.
//{
#define POWER_ANNOUNCEMENT (    \
	fighters[index].get_name()  \
	+ " deals "                 \
	+ power                     \
	+ " more damage this turn!" \
)
//}

// Announcement for a fighter retreat.
//{
#define RETREAT_ANNOUNCEMENT (fighters[0].get_name() + " retreated.")
//}

// Announcement for an attack.
//{
#define ATTACK_ANNOUNCEMENT ( \
	fighters[0].get_name()    \
	+ " used "                \
	+ attack.get_name()       \
	+ "!"                     \
)
//}

// Announcement for damage being dealt to the opponent's active fighter.
//{
#define DAMAGE_ANNOUNCEMENT (        \
	opponent->fighters[0].get_name() \
	+ " took "                       \
	+ std::to_string(damage)         \
	+ " damage!"                     \
)
//}

// Announcement for a fighter defeat.
//{
#define DEFEAT_ANNOUNCEMENT ( \
	fighters[i].get_name() \
	+ " was defeated!" \
)
//}

// Announcement for the player having all of their fighters defeated.
//{
#define NO_FIGHTERS_ANNOUNCEMENT (                             \
	opposing ? "You defeated all of your opponent's fighters!" \
	: "All of your fighters were defeated..."                  \
)
//}

// Announcement for the player drawing all of their life cards.
//{
#define NO_LIFE_ANNOUNCEMENT (                               \
	std::string(opposing ? "Your opponent has" : "You have") \
	+ " no more life cards"                                  \
	+ (opposing ? "!" : "...")                               \
)
//}

// Announceent for the opponent seeing how many life cards that the player will draw.
//{
#define LIFE_DRAW_ANNOUNCEMENT (   \
	"Your opponent is choosing "   \
	+ std::to_string(life_draws)   \
	+ " life card"                 \
	+ (life_draws == 1 ? "" : "s") \
	+ " to draw."                  \
)
//}

// Announcement for the player to draw a life card.
//{
constexpr const char* DRAW_LIFE_ANNOUNCEMENT = "Choose a life card to draw.";
//}

// Announcement for the player to choose a new active fighter.
//{
#define NEW_ACTIVE_ANNOUNCEMENT (                                \
	opposing ? "Your opponent is choosing a new active fighter." \
	: "Choose a new active fighter from your bench."             \
)
//}

// Announcement for the new active fighter.
//{
#define REPLACEMENT_ANNOUNCEMENT (                \
	fighters[0].get_name()                        \
	+ " was chosen to be the new active fighter!" \
)
//}

// Announcement for a hand shuffled into the deck.
//{
#define SHUFFLE_ALL_ANNOUNCEMENT (                  \
	std::string(opposing ? "Your opponent" : "You") \
	+ " shuffled "                                  \
	+ (opposing ? "their" : "your")                 \
	+ " hand into "                                 \
	+ (opposing ? "their" : "your")                 \
	+ " deck."                                      \
)
//}

// Announcement for drawing cards at the end of the turn.
//{
#define END_DRAW_ANNOUNCEMENT (                     \
	std::string(opposing ? "Your opponent" : "You") \
	+ " will draw "                                 \
	+ effects[i][1]                                 \
	+ " card"                                       \
	+ (std::stoi(effects[i][1]) == 1 ? "" : "s")    \
	+ " at the end of "                             \
	+ (opposing ? "their" : "your")                 \
	+ " turn."                                      \
)
//}

// Announcement to declare that a card must be shuffled into the deck.
//{
#define TO_SHUFFLE_ANNOUNCEMENT (                                                           \
	opposing ? "Your opponent is choosing a card in their hand to shuffle into their deck." \
	: "Choose a card to shuffle from your hand into your deck."                             \
)
//}

// Announcement to announce the number of cards shuffled.
//{
#define SHUFFLE_ANNOUNCEMENT (                      \
	std::string(opposing ? "Your opponent" : "You") \
	+ " shuffled "                                  \
	+ std::to_string(shuffles)                      \
	+ " card"                                       \
	+ (shuffles == 1 ? "" : "s")                    \
	+ " into "                                      \
	+ (opposing ? "their" : "your")                 \
	+ " deck."                                      \
)
//}

// Announcement to announce the last coin flip.
//{
#define FLIP_ANNOUNCEMENT (                         \
	std::string(opposing ? "Your opponent" : "You") \
	+ " flipped "                                   \
	+ (result == HEADS ? "heads" : "tails")         \
	+ "."                                           \
)
//}

// Announcement to announce the flip counts.
//{
#define FLIP_COUNT_ANNOUNCEMENT (        \
	"Heads: "                            \
	+ std::to_string(flip_counts[HEADS]) \
	+ "\nTails: "                        \
	+ std::to_string(flip_counts[TAILS]) \
)
//}

// Announcement to declare that a card must be discarded.
//{
#define TO_DISCARD_ANNOUNCEMENT (                             \
	opposing ? "Your opponent is choosing a card to discard." \
	: "Choose a card to discard from your hand."              \
)
//}

// Announcement to announce the number of cards discarded.
//{
#define DISCARD_ANNOUNCEMENT (                      \
	std::string(opposing ? "Your opponent" : "You") \
	+ " discarded "                                 \
	+ std::to_string(discards)                      \
	+ " card"                                       \
	+ (discards == 1 ? "" : "s")                    \
	+ "."                                           \
)
//}

// Announcement to declare the name of the card discarded.
//{
#define DISCARD_PEEK_ANNOUNCEMENT ( \
	hand[index].get_name()          \
	+ " was discarded."             \
)
//}

// Announcement to declare that a card will be searched for in the deck.
//{
#define TO_SEARCH_ANNOUNCEMENT (                                           \
	opposing ? "Your opponent is searching their deck for a card to draw." \
	: "Choose a card to draw from your deck."                              \
)
//}

// Announcement to announce the number of cards drawn from a search.
//{
#define SEARCH_ANNOUNCEMENT (                       \
	std::string(opposing ? "Your opponent" : "You") \
	+ " drew "                                      \
	+ std::to_string(searches)                      \
	+ " card"                                       \
	+ (searches == 1 ? "" : "s")                    \
	+ "."                                           \
)
//}

// Announcement to declare that a fighter will be sniped.
//{
#define TO_SNIPE_ANNOUNCEMENT (                                 \
	opposing ? "Your opponent is choosing a fighter to damage." \
	: "Choose a fighter to damage."                             \
)
//}

// Announcement for a fighter being damage from a snipe.
//{
#define SNIPE_ANNOUNCEMENT (             \
	opponent->fighters[index].get_name() \
	+ " took "                           \
	+ std::to_string(snipe)              \
	+ " damage!"                         \
)
//}

// Announcement that displays the last milled card.
//{
#define MILL_PEEK_ANNOUNCEMENT ( \
	last_drawn->get_name()       \
	+ " was discarded."          \
)
//}

// Announcement to show the total number of cards milled.
//{
#define MILL_ANNOUNCEMENT (                         \
	std::string(opposing ? "Your opponent" : "You") \
	+ " discarded "                                 \
	+ std::to_string(mills)                         \
	+ " card"                                       \
	+ (mills == 1 ? "" : "s")                       \
	+ "."                                           \
)
//}

// Announcement to display the health restored to a fighter.
//{
#define HEAL_ANNOUNCEMENT (    \
	fighters[index].get_name() \
	+ " was healed "           \
	+ std::to_string(heal)     \
	+ " damage!"               \
)
//}

// Announcement to announce a change to a fighter's retreat cost.
//{
#define AGILITY_ANNOUNCEMENT (                             \
	opponent->fighters[0].get_name()                       \
	+ "'s retreat cost was "                               \
	+ (std::stoi(agility) < 0 ? "increased" : "decreased") \
	+ " by "                                               \
	+ std::to_string(abs(std::stoi(agility)))              \
	+ "!"                                                  \
)
//}
//}

// Universal Effect Explanation Constants
//{
#define EXPLANATION_STRING explain(effect_name, effect_value)
constexpr double EXPLANATION_X = 0.5;
constexpr double EXPLANATION_Y = 0.5;
constexpr double EXPLANATION_WIDTH = 0.5 * TITLE_WIDTH;
constexpr double EXPLANATION_HEIGHT = 2 * EXPLANATION_WIDTH;
constexpr double EXPLANATION_MAX_WIDTH = 0.75;
constexpr double EXPLANATION_SEPARATION_X = EXPLANATION_WIDTH / 20;
constexpr double EXPLANATION_SEPARATION_Y = EXPLANATION_HEIGHT / 5;
constexpr Renderer::Justification EXPLANATION_JUSTIFICATION = Renderer::CENTRE_JUSTIFY;
constexpr const char* EMPTY_EXPLANATION = "";
//}
//}

// Audio Constants
//{
// Menu song details.
constexpr const char* MENU_SONG_SOURCE = "data/menusong.wav";
constexpr double MENU_SONG_LENGTH = Timer::to_seconds(0, 1, 8);

// Build song details.
constexpr const char* BUILD_SONG_SOURCE = "data/buildsong.wav";
constexpr double BUILD_SONG_LENGTH = Timer::to_seconds(0, 0, 57);

// Game song details.
constexpr const char* DUEL_SONG_SOURCE = "data/duelsong.wav";
constexpr double DUEL_SONG_LENGTH = Timer::to_seconds(0, 1, 55);
//}

// Card Instance Constants
//{
// Fighter Cards
//{
// Driver Family
//{
// Fire Driver Family
//{
// Driver
//{
constexpr const char* DRIVER_NAME = "Driver";
constexpr const char* DRIVER_ELEMENT = FIRE_ELEMENT;
constexpr int DRIVER_HEALTH = 1000;
constexpr int DRIVER_RETREAT_COST = 1000;
constexpr const char* DRIVER_OLD_RANK = NO_OLD_RANK;
constexpr const char* DRIVER_ABILITY_NAME = "Fuel Conversion";
constexpr const char* DRIVER_ABILITY_DESCRIPTION =
	"When this fighter ranks up, convert all energy attached "
	"to this fighter to the element of the new rank."
;
const std::string DRIVER_ABILITY_EFFECTS(
	std::string(RANK_UP_EFFECT) // rank_up
	+ EFFECT_SEPARATOR          //
	+ CONVERSION_EFFECT         // conversion
);
constexpr bool DRIVER_ABILITY_PASSIVE = true;
constexpr int DRIVER_ABILITY_USES = PASSIVE_USES;
constexpr const char* DRIVER_ATTACK_NAME = "Drift";
constexpr const char* DRIVER_ATTACK_DESCRIPTION =
	"Deal 250 damage to your oppenent's active fighter."
;
constexpr const char* DRIVER_ATTACK_EFFECTS = NO_EFFECTS;
constexpr int DRIVER_ATTACK_DAMAGE = 250;
constexpr int DRIVER_ATTACK_COST = 1000;
//}

// Racer
//{
constexpr const char* RACER_NAME = "Racer";
constexpr const char* RACER_ELEMENT = FIRE_ELEMENT;
constexpr int RACER_HEALTH = 1250;
constexpr int RACER_RETREAT_COST = 1000;
constexpr const char* RACER_OLD_RANK = DRIVER_NAME;
constexpr const char* RACER_ABILITY_NAME = "Acceleration";
constexpr const char* RACER_ABILITY_DESCRIPTION =
	"Once a turn, you may switch this fighter in from the bench. "
	"If you do, this fighter deals 150 more damage this turn."
;
const std::string RACER_ABILITY_EFFECTS(
	std::string(SWITCH_IN_EFFECT) // switch_in
	+ EFFECT_SEPARATOR            //
	+ POWER_EFFECT                // power
	+ EFFECT_SEPARATOR            //
	+ "150"                       // 150
);
constexpr bool RACER_ABILITY_PASSIVE = false;
constexpr int RACER_ABILITY_USES = 1;
constexpr const char* RACER_ATTACK_NAME = "Nitro Boost";
constexpr const char* RACER_ATTACK_DESCRIPTION =
	"Deal 350 damage to your oppenent's active fighter."
;
constexpr const char* RACER_ATTACK_EFFECTS = NO_EFFECTS;
constexpr int RACER_ATTACK_DAMAGE = 350;
constexpr int RACER_ATTACK_COST = 1500;
//}

// Hot Rodder
//{
constexpr const char* HOT_RODDER_NAME = "Hot Rodder";
constexpr const char* HOT_RODDER_ELEMENT = FIRE_ELEMENT;
constexpr int HOT_RODDER_HEALTH = 1500;
constexpr int HOT_RODDER_RETREAT_COST = 1000;
constexpr const char* HOT_RODDER_OLD_RANK = RACER_NAME;
constexpr const char* HOT_RODDER_ABILITY_NAME = "Charged Thruster";
constexpr const char* HOT_RODDER_ABILITY_DESCRIPTION =
	"Once a turn, you may switch this fighter in from the bench. "
	"If you do, this fighter deals 400 more damage this turn."
;
const std::string HOT_RODDER_ABILITY_EFFECTS(
	std::string(SWITCH_IN_EFFECT) // switch_in
	+ EFFECT_SEPARATOR            //
	+ POWER_EFFECT                // power
	+ EFFECT_SEPARATOR            //
	+ "400"                       // 400
);
constexpr bool HOT_RODDER_ABILITY_PASSIVE = false;
constexpr int HOT_RODDER_ABILITY_USES = 1;
constexpr const char* HOT_RODDER_ATTACK_NAME = "Super Nitro";
constexpr const char* HOT_RODDER_ATTACK_DESCRIPTION =
	"Deal 350 damage to your oppenent's active fighter."
;
constexpr const char* HOT_RODDER_ATTACK_EFFECTS = NO_EFFECTS;
constexpr int HOT_RODDER_ATTACK_DAMAGE = 350;
constexpr int HOT_RODDER_ATTACK_COST = 2000;
//}
//}

// Water Driver Family
//{
// Sailor
//{
constexpr const char* SAILOR_NAME = "Sailor";
constexpr const char* SAILOR_ELEMENT = WATER_ELEMENT;
constexpr int SAILOR_HEALTH = 1250;
constexpr int SAILOR_RETREAT_COST = 1500;
constexpr const char* SAILOR_OLD_RANK = DRIVER_NAME;
constexpr const char* SAILOR_ABILITY_NAME = "Sailor's Compass";
constexpr const char* SAILOR_ABILITY_DESCRIPTION =
	"Once a turn, you may draw a card."
;
const std::string SAILOR_ABILITY_EFFECTS(
	std::string(DRAW_EFFECT) // draw
	+ EFFECT_SEPARATOR       //
	+ "1"                    // 1
);
constexpr bool SAILOR_ABILITY_PASSIVE = false;
constexpr int SAILOR_ABILITY_USES = 1;
constexpr const char* SAILOR_ATTACK_NAME = "Torpedo";
constexpr const char* SAILOR_ATTACK_DESCRIPTION =
	"Deal 300 damage to one of your opponent's fighters."
;
const std::string SAILOR_ATTACK_EFFECTS(
	std::string(SNIPE_EFFECT) // snipe
	+ EFFECT_SEPARATOR        //
	+ "300"                   // 250
);
constexpr int SAILOR_ATTACK_DAMAGE = 0;
constexpr int SAILOR_ATTACK_COST = 1000;
//}

// Pirate
//{
constexpr const char* PIRATE_NAME = "Pirate";
constexpr const char* PIRATE_ELEMENT = WATER_ELEMENT;
constexpr int PIRATE_HEALTH = 1500;
constexpr int PIRATE_RETREAT_COST = 2000;
constexpr const char* PIRATE_OLD_RANK = SAILOR_NAME;
constexpr const char* PIRATE_ABILITY_NAME = "Plundered";
constexpr const char* PIRATE_ABILITY_DESCRIPTION =
	"Once a turn, you may search your deck for a card and draw it."
;
const std::string PIRATE_ABILITY_EFFECTS(
	std::string(SEARCH_EFFECT) // search
	+ EFFECT_SEPARATOR         //
	+ "1"                      // 1
);
constexpr bool PIRATE_ABILITY_PASSIVE = false;
constexpr int PIRATE_ABILITY_USES = 1;
constexpr const char* PIRATE_ATTACK_NAME = "Plank Walk";
constexpr const char* PIRATE_ATTACK_DESCRIPTION =
	"Deal 300 damage to one of your opponent's fighters. "
	"Deal 100 extra damage to non-water element fighters."
;
const std::string PIRATE_ATTACK_EFFECTS(
	std::string(SNIPE_EFFECT) // snipe
	+ EFFECT_SEPARATOR        //
	+ "400"                   // 400
	+ EFFECT_SEPARATOR        //
	+ POWER_EFFECT            // power
	+ EFFECT_SEPARATOR        //
	+ WATER_ELEMENT           // Water
	+ EFFECT_SEPARATOR        //
	+ "-100"                  // -100
);
constexpr int PIRATE_ATTACK_DAMAGE = 0;
constexpr int PIRATE_ATTACK_COST = 1000;
//}
//}

// Earth Driver Family
//{
// Dirt Biker
//{
constexpr const char* DIRT_BIKER_NAME = "Dirt Biker";
constexpr const char* DIRT_BIKER_ELEMENT = EARTH_ELEMENT;
constexpr int DIRT_BIKER_HEALTH = 1250;
constexpr int DIRT_BIKER_RETREAT_COST = 2000;
constexpr const char* DIRT_BIKER_OLD_RANK = DRIVER_NAME;
constexpr const char* DIRT_BIKER_ABILITY_NAME = "Quick Fix";
constexpr const char* DIRT_BIKER_ABILITY_DESCRIPTION =
	"You may discard the top card of your deck and heal 50 damage from this fighter."
;
const std::string DIRT_BIKER_ABILITY_EFFECTS(
	std::string(MILL_EFFECT) // mill
	+ EFFECT_SEPARATOR       //
	+ "1"                    // 1
	+ EFFECT_TERMINATOR
	+ HEAL_EFFECT            // heal
	+ EFFECT_SEPARATOR       //
	+ "50"                   // 50
);
constexpr bool DIRT_BIKER_ABILITY_PASSIVE = false;
constexpr int DIRT_BIKER_ABILITY_USES = INFINITE_USES;
constexpr const char* DIRT_BIKER_ATTACK_NAME = "Shred";
constexpr const char* DIRT_BIKER_ATTACK_DESCRIPTION =
	"Deal 400 damage to your oppenent's active fighter. "
	"For each card in your trash, deal 10 more damage."
;
const std::string DIRT_BIKER_ATTACK_EFFECTS(
	std::string(POWER_EFFECT) // power
	+ EFFECT_SEPARATOR        //
	+ TRASH_EFFECT            // trash
	+ EFFECT_SEPARATOR        //
	+ "10"                    // 10
);
constexpr int DIRT_BIKER_ATTACK_DAMAGE = 400;
constexpr int DIRT_BIKER_ATTACK_COST = 2000;
//}

// Monster Trucker
//{
constexpr const char* MONSTER_TRUCKER_NAME = "Monster Trucker";
constexpr const char* MONSTER_TRUCKER_ELEMENT = EARTH_ELEMENT;
constexpr int MONSTER_TRUCKER_HEALTH = 1500;
constexpr int MONSTER_TRUCKER_RETREAT_COST = 3000;
constexpr const char* MONSTER_TRUCKER_OLD_RANK = DIRT_BIKER_NAME;
constexpr const char* MONSTER_TRUCKER_ABILITY_NAME = "Scrap Metal";
constexpr const char* MONSTER_TRUCKER_ABILITY_DESCRIPTION =
	"You may discard the top card of your deck and heal 100 damage from this fighter."
;
const std::string MONSTER_TRUCKER_ABILITY_EFFECTS(
	std::string(MILL_EFFECT) // mill
	+ EFFECT_SEPARATOR       //
	+ "1"                    // 1
	+ EFFECT_TERMINATOR
	+ HEAL_EFFECT            // heal
	+ EFFECT_SEPARATOR       //
	+ "100"                  // 100
);
constexpr bool MONSTER_TRUCKER_ABILITY_PASSIVE = false;
constexpr int MONSTER_TRUCKER_ABILITY_USES = INFINITE_USES;
constexpr const char* MONSTER_TRUCKER_ATTACK_NAME = "Crush";
constexpr const char* MONSTER_TRUCKER_ATTACK_DESCRIPTION =
	"Deal 400 damage to your oppenent's active fighter. "
	"For each card in your trash, deal 20 more damage."
;
const std::string MONSTER_TRUCKER_ATTACK_EFFECTS(
	std::string(POWER_EFFECT) // power
	+ EFFECT_SEPARATOR        //
	+ TRASH_EFFECT            // trash
	+ EFFECT_SEPARATOR        //
	+ "20"                    // 20
);
constexpr int MONSTER_TRUCKER_ATTACK_DAMAGE = 400;
constexpr int MONSTER_TRUCKER_ATTACK_COST = 3000;
//}
//}

// Air Driver Family
//{
// Pilot
//{
constexpr const char* PILOT_NAME = "Pilot";
constexpr const char* PILOT_ELEMENT = AIR_ELEMENT;
constexpr int PILOT_HEALTH = 1250;
constexpr int PILOT_RETREAT_COST = 2500;
constexpr const char* PILOT_OLD_RANK = DRIVER_NAME;
constexpr const char* PILOT_ABILITY_NAME = "Airborne";
constexpr const char* PILOT_ABILITY_DESCRIPTION =
	"Your fighters can retreat for 2500 less energy."
;
const std::string PILOT_ABILITY_EFFECTS(
	std::string(AGILITY_AURA_EFFECT) // agility_aura
	+ EFFECT_SEPARATOR               //
	+ "2500"                         // 2500
);
constexpr bool PILOT_ABILITY_PASSIVE = true;
constexpr int PILOT_ABILITY_USES = PASSIVE_USES;
constexpr const char* PILOT_ATTACK_NAME = "Divebomb";
constexpr const char* PILOT_ATTACK_DESCRIPTION =
	"Deal 250 damage to the defending fighter. "
	"It needs 1500 more energy to retreat next turn."
;
const std::string PILOT_ATTACK_EFFECTS(
	std::string(AGILITY_EFFECT) // agility
	+ EFFECT_SEPARATOR          //
	+ "-1500"                   // -1500
);
constexpr int PILOT_ATTACK_DAMAGE = 250;
constexpr int PILOT_ATTACK_COST = 500;
//}

// Astronaut
//{
constexpr const char* ASTRONAUT_NAME = "Astronaut";
constexpr const char* ASTRONAUT_ELEMENT = AIR_ELEMENT;
constexpr int ASTRONAUT_HEALTH = 1500;
constexpr int ASTRONAUT_RETREAT_COST = 4000;
constexpr const char* ASTRONAUT_OLD_RANK = PILOT_NAME;
constexpr const char* ASTRONAUT_ABILITY_NAME = "Zero Gravity";
constexpr const char* ASTRONAUT_ABILITY_DESCRIPTION =
	"Your fighters can retreat for 4000 less energy. "
	"You can retreat your fighters as often as you like."
;
const std::string ASTRONAUT_ABILITY_EFFECTS(
	std::string(AGILITY_AURA_EFFECT) // agility_aura
	+ EFFECT_SEPARATOR               //
	+ "4000"                         // 4000
	+ EFFECT_TERMINATOR
	+ FREEDOM_EFFECT                 // freedom
);
constexpr bool ASTRONAUT_ABILITY_PASSIVE = true;
constexpr int ASTRONAUT_ABILITY_USES = PASSIVE_USES;
constexpr const char* ASTRONAUT_ATTACK_NAME = "Gravity Flip";
constexpr const char* ASTRONAUT_ATTACK_DESCRIPTION =
	"Deal 250 damage to the defending fighter. "
	"It needs 3000 more energy to retreat next turn."
;
const std::string ASTRONAUT_ATTACK_EFFECTS(
	std::string(AGILITY_EFFECT) // agility
	+ EFFECT_SEPARATOR          //
	+ "-3000"                   // -3000
);
constexpr int ASTRONAUT_ATTACK_DAMAGE = 300;
constexpr int ASTRONAUT_ATTACK_COST = 0;
//}
//}
//}

// Mage Family
//{
// Mage
//{
// Can use all energy elements, hits active and bench
//}

// Pyromancer
//{
// Symmetrical mill, semi-symmetrical splash
//}

// Warlock
//{
// Rank down to search trash, recoil attack
//}

// Cleric
//{
// Heal team each turn, heal self for attack
//}

// Vacuumancer
//{
// Pull, push
//}
//}

// Ranker Family
//{
// Miner Family
//{
// Miner
//{
// Flip to search for earth energy, basic attack
//}

// Excavator
//{
// Return energy to hand on rank up, shuffle and redraw
//}
//}

// Swimmer Family
//{
// Swimmer
//{
// Flip to search for water energy, basic attack
//}

// Diver
//{
// Undamagable on rank up, flip heads for effect immunity and recovery
//}	
//}

// Welder Family
//{
// Welder
//{
// Flip to search for fire energy, basic attack
//}

// Pyrotechnician
//{
// Convert all to fire element on rank up, deal damage for usable energy
//}	
//}

// Wind Runner Family
//{
// Wind Runner
//{
// Flip to search for air energy, basic attack
//}

// Cloud Surfer
//{
// Search the deck for cards on rank up, splash attack
//}
//}
//}

// Void Family
//{
// Lost Soul
//{
// Banish fighter and life card and banish mill on defeat, draw fighter (bonus on no draw)
//}

// Banisher
//{
// Symmetrical discard banishment in active, damage over time
//}

// Banshee
//{
// Powered by energy cards in the void, damage for cards in the void
//}

// Cultist
//{
// Search deck and banish, use attack of fighter in void
//}
//}
//}

// Supporter Cards
//{
// Draw
//{
// Professor
//{
constexpr const char* PROFESSOR_NAME = "Professor";
constexpr const char* PROFESSOR_DESCRIPTION = "Discard your hand. Draw 5 cards.";
const std::string PROFESSOR_EFFECTS(
	std::string(DISCARD_EFFECT) // discard
	+ EFFECT_SEPARATOR          //
	+ UNIVERSAL_EFFECT          // all
	+ EFFECT_TERMINATOR
	+ DRAW_EFFECT               // draw
	+ EFFECT_SEPARATOR          //
	+ "5"                       // 5
);
//}

// Researcher
//{
constexpr const char* RESEARCHER_NAME = "Researcher";
constexpr const char* RESEARCHER_DESCRIPTION = "Draw 2 cards.";
const std::string RESEARCHER_EFFECTS(
	std::string(DRAW_EFFECT) // draw
	+ EFFECT_SEPARATOR
	+ "2"                    // 2
);
//}

// Lecturer
//{
constexpr const char* LECTURER_NAME = "Lecturer";
constexpr const char* LECTURER_DESCRIPTION =
	"Shuffle your hand into your deck. Draw 5 cards."
;
const std::string LECTURER_EFFECTS(
	std::string(SHUFFLE_EFFECT) // shuffle
	+ EFFECT_SEPARATOR          //
	+ UNIVERSAL_EFFECT          // all
	+ EFFECT_TERMINATOR
	+ DRAW_EFFECT               // draw
	+ EFFECT_SEPARATOR          //
	+ "5"                       // 5
);
//}

// Investor
//{
constexpr const char* INVESTOR_NAME = "Investor";
constexpr const char* INVESTOR_DESCRIPTION =
	"Shuffle your hand into your deck. "
	"At the end of your turn, draw 8 cards."
;
const std::string INVESTOR_EFFECTS(
	std::string(SHUFFLE_EFFECT) // shuffle
	+ EFFECT_SEPARATOR          //
	+ UNIVERSAL_EFFECT          // all
	+ EFFECT_TERMINATOR
	+ END_DRAW_EFFECT           // end_draw
	+ EFFECT_SEPARATOR          //
	+ "8"                       // 8
);
//}

// Banker
//{
constexpr const char* BANKER_NAME = "Banker";
constexpr const char* BANKER_DESCRIPTION =
	"Shuffle a card from your hand into your deck. "
	"At the end of your turn, draw 4 cards."
;
const std::string BANKER_EFFECTS(
	std::string(SHUFFLE_EFFECT) // shuffle
	+ EFFECT_SEPARATOR          //
	+ "1"                       // 1
	+ EFFECT_TERMINATOR
	+ END_DRAW_EFFECT           // end_draw
	+ EFFECT_SEPARATOR          //
	+ "4"                       // 4
);
//}

// Gambler
//{
constexpr const char* GAMBLER_NAME = "Gambler";
constexpr const char* GAMBLER_DESCRIPTION =
	"Discard a card from your hand. Flip a coin. "
	"If you get heads, draw 4 cards. "
	"If you get tails, draw 2 cards."
;
const std::string GAMBLER_EFFECTS(
	std::string(DISCARD_EFFECT) // discard
	+ EFFECT_SEPARATOR          //
	+ "1"                       // 1
	+ EFFECT_TERMINATOR
	+ FLIP_EFFECT               // flip
	+ EFFECT_SEPARATOR          //
	+ "1"                       // 1
	+ EFFECT_TERMINATOR
	+ HEADS_EFFECT              // heads
	+ EFFECT_SEPARATOR          //
	+ DRAW_EFFECT               // draw
	+ EFFECT_SEPARATOR          //
	+ "4"                       // 4
	+ EFFECT_TERMINATOR
	+ TAILS_EFFECT              // tails
	+ EFFECT_SEPARATOR          //
	+ DRAW_EFFECT               // draw
	+ EFFECT_SEPARATOR          //
	+ "2"                       // 2
);
//}
//}

// Search
//{
// Computer Scientist
//{
// Discard to search
//}

// Experimenter
//{
// Search for 3, draw no.1, discard no.2, banish no. 3
//}

// Alchemist
//{
// Trade card in hand for card in trash
//}

// Electrician
//{
// Search for energy
//}

// Trader
//{
// Trade card in hand for card of same type in deck
//}
//}

// Switch
//{
// Substitute
//{
// Switch in fighter from bench, shuffle this card into the deck, draw a card
//}

// Bounty Hunter
//{
// Switch in fighter from opponent's bench
//}

// Matchmaker
//{
// Switch in fighters from both benches
//}

// Escape Artist
//{
// Return a fighter to hand
//}
//}

// Recycle
//{
// Smuggler
//{
// Search trash for cards, shuffle them into deck
//}

// Glutton
//{
// Flip coins for each energy card, shuffle heads energy into the deck
//}
//}

// Power
//{
// Cheerleader
//{
constexpr const char* CHEERLEADER_NAME = "Cheerleader";
constexpr const char* CHEERLEADER_DESCRIPTION =
	"Attacks deal 250 more damage this turn."
;
const std::string CHEERLEADER_EFFECTS(
	std::string(POWER_EFFECT) // power
	+ EFFECT_SEPARATOR
	+ "250"                   // 250
);
//}

// Maniac
//{
// Discard hand for power boost
//}
//}

// Diruption
//{
// Plumber
//{
// Discard energy
//}

// Miller
//{
// Discard hand to mill
//}

// Scammer
//{
// Swap hand size
//}

// Arsonist
//{
// Symmetrical banishing mill
//}
//}

// Healing
//{
// Nurse
//{
// Heal
//}

// Doctor
//{
// Full heal, effect clear, discard all energy
//}

// Miracle Worker
//{
// Symmetrical Heal
//}
//}
//}

// Energy Cards
//{
// Basic Energy
//{
// Fire Energy
//{
constexpr const char* FIRE_ENERGY_NAME = "Fire Energy";
constexpr const char* FIRE_ENERGY_DESCRIPTION = BASIC_ENERGY_DESCRIPTION;
constexpr const char* FIRE_ENERGY_ELEMENT = FIRE_ELEMENT;
constexpr const char* FIRE_ENERGY_EFFECTS = BASIC_ENERGY_EFFECTS;
constexpr int FIRE_ENERGY_VALUE = BASIC_ENERGY_VALUE;
//}

// Air Energy
//{
constexpr const char* AIR_ENERGY_NAME = "Air Energy";
constexpr const char* AIR_ENERGY_DESCRIPTION = BASIC_ENERGY_DESCRIPTION;
constexpr const char* AIR_ENERGY_ELEMENT = AIR_ELEMENT;
constexpr const char* AIR_ENERGY_EFFECTS = BASIC_ENERGY_EFFECTS;
constexpr int AIR_ENERGY_VALUE = BASIC_ENERGY_VALUE;
//}

// Water Energy
//{
constexpr const char* WATER_ENERGY_NAME = "Water Energy";
constexpr const char* WATER_ENERGY_DESCRIPTION = BASIC_ENERGY_DESCRIPTION;
constexpr const char* WATER_ENERGY_ELEMENT = WATER_ELEMENT;
constexpr const char* WATER_ENERGY_EFFECTS = BASIC_ENERGY_EFFECTS;
constexpr int WATER_ENERGY_VALUE = BASIC_ENERGY_VALUE;
//}

// Earth Energy
//{
constexpr const char* EARTH_ENERGY_NAME = "Earth Energy";
constexpr const char* EARTH_ENERGY_DESCRIPTION = BASIC_ENERGY_DESCRIPTION;
constexpr const char* EARTH_ENERGY_ELEMENT = EARTH_ELEMENT;
constexpr const char* EARTH_ENERGY_EFFECTS = BASIC_ENERGY_EFFECTS;
constexpr int EARTH_ENERGY_VALUE = BASIC_ENERGY_VALUE;
//}
//}

// Special Energy
//{
// Twin Energy
//{
constexpr const char* TWIN_ENERGY_NAME = "Twin Energy";
constexpr const char* TWIN_ENERGY_DESCRIPTION =
	"Provides 2000 energy for fighters of this element."
;
constexpr const char* TWIN_ENERGY_ELEMENT = NO_ELEMENT;
constexpr const char* TWIN_ENERGY_EFFECTS = NO_EFFECTS;
constexpr int TWIN_ENERGY_VALUE = 2000;
//}

// Universal Energy
//{
constexpr const char* UNIVERSAL_ENERGY_NAME = "Universal Energy";
constexpr const char* UNIVERSAL_ENERGY_DESCRIPTION =
	"Provides 750 energy for fighters of all elements."
;
constexpr const char* UNIVERSAL_ENERGY_ELEMENT = NO_ELEMENT;
constexpr const char* UNIVERSAL_ENERGY_EFFECTS = UNIVERSAL_EFFECT;
constexpr int UNIVERSAL_ENERGY_VALUE = 750;
//}

// Draw Energy
//{
// Provides little elementless energy and draws a card
//}
//}
//}
//}
//}

// Basic Classes
//{
/**
 * An abstract base class for objects
 *   that can be affected to inherit from.
 */
class Affectable {
	public:
		/**
		 * Returns a constant reference to the object's effects.
		 */
		const std::vector<std::vector<std::string>>& get_effects() const noexcept {
			return effects;
		}
		
		/**
		 * Converts an effect representation to an effect explanation.
		 */
		static std::string explain(
			const std::string& effect_name,
			const std::string& effect_value
		) noexcept {
			// The explanation for the effect is searched for.
			for (int i = 0; i < EXPLANATION_COUNT; ++i) {
				if (effect_name == EFFECT_REPRESENTATIONS[i]) {
					return EFFECT_EXPLANATIONS(i);
				}
			}
			
			// The explanation for the player-specific effect is searched for.
			for (int i = 0; i < PLAYER_EXPLANATION_COUNT; ++i) {
				if (effect_name == PLAYER_EFFECT_REPRESENTATIONS[i]) {
					return PLAYER_EFFECT_EXPLANATIONS(i);
				}
			}
			
			// If no explanation is found, the empty explanation is returned.
			return EMPTY_EXPLANATION;
		}			
		
		/**
		 * Explains the functionality of an effect.
		 */
		static void explain(
			Display& display,
			const Renderer& renderer,
			const Button& back_button,
			const std::string& message,
			const std::string& effect_name,
			const std::string& effect_value
		) noexcept {
			// The explanation is rendered.
			display.fill();
			display.blit(
				renderer.lined_render(
					display,
					EXPLANATION_STRING,
					EXPLANATION_WIDTH,
					EXPLANATION_HEIGHT,
					EXPLANATION_SEPARATION_X,
					EXPLANATION_MAX_WIDTH,
					EXPLANATION_SEPARATION_Y,
					EXPLANATION_JUSTIFICATION
				),
				EXPLANATION_X,
				EXPLANATION_Y
			);
			back_button.blit_to(display);
			display.update();
			
			// The player proceeds when they or their opponent makes a move.
			while (
				!Events::unpress(NEXT_KEY)
				&& !Events::unpress(BACK_KEY)
				&& !back_button.get_rectangle().unclick()
				&& message == EMPTY_MESSAGE
			) {
				Events::update();
			}
		}
		
		/**
		 * Counts the total effect value of an effect.
		 */
		virtual int effect_count(const std::string& effect) const noexcept {
			int count = 0;
			
			for (int i = 0; i < effects.size(); ++i) {
				if (effects[i][0] == effect) {
					count += std::stoi(effects[i][1]);
				}
			}
			
			return count;
		}
		
		/**
		 * Returns a pointer to the vector of strings matching the given effect.
		 * Returns the null pointer if the effect was not found.
		 */
		virtual const std::vector<std::string>* effect_search(
			const std::string& effect
		) const noexcept {
			// The effect is searched for.
			for (int i = 0; i < effects.size(); ++i) {
				if (effects[i][0] == effect) {
					// A pointer to the vector of strings with the effect is returned.
					return &effects[i];
				}
			}
			
			// The effect wasn't found and a null pointer is returned.
			return nullptr;
		}
		
		/**
		 * Adds an effect to his object.
		 */
		void affect(const std::string& effects) noexcept {
			// A stream is used to parse the effects.
			std::stringstream effect_stream(effects + EFFECT_TERMINATOR);
			std::vector<std::string> proto_effects;
			std::string effect_string;
			
			// The effects are divided by line.
			for (
				std::getline(effect_stream, effect_string, EFFECT_TERMINATOR);
				!effect_stream.eof();
				std::getline(effect_stream, effect_string, EFFECT_TERMINATOR)
			) {
				proto_effects.push_back(effect_string);
			}
			
			// The effects are then divided into words.
			for (int i = 0; i < proto_effects.size(); i++) {
				this->effects.push_back(std::vector<std::string>());
				
				effect_stream.clear();
				effect_stream.seekg(0);
				effect_stream.str(proto_effects[i] + EFFECT_SEPARATOR);
				
				for (
					std::getline(effect_stream, effect_string, EFFECT_SEPARATOR);
					!effect_stream.eof();
					std::getline(effect_stream, effect_string, EFFECT_SEPARATOR)
				) {
					this->effects.back().push_back(effect_string);
				}
			}
		}
		
		/**
		 * Removes all effects from this object that match the given argument.
		 */
		void unaffect(const std::string& effect) noexcept {
			for (int i = 0; i < effects.size(); ++i) {
				if (effects[i][0] == effect) {
					effects.erase(effects.cbegin() + i);
					--i;
				}
			}
		}
		
	protected:
		/**
		 * Parses, extracts, and organises the given effects.
		 */
		Affectable(const std::string& effects) noexcept {
			affect(effects);
		}
		
		std::vector<std::vector<std::string>> effects; // The effects of the object.
};

/**
 * An abstract base class for the card types to inherit from.
 */
class Card: public Affectable {
	public:
		/**
		 * Returns the card's name.
		 */
		const std::string& get_name() const noexcept {
			return name;
		}
		
		/**
		 * Returns the card's type.
		 * The types of card are Fighter, Supporter, and Energy.
		 * The instantiating class should define the card type.
		 */
		const std::string& get_type() const noexcept {
			return type;
		}
		
		/**
		 * Returns the card in string form.
		 * This string should be compatible with the Renderer class.
		 */
		virtual std::string to_string() const noexcept = 0;
		
		/**
		 * Renders the card's text to the display.
		 */
		void render(Display& display, const Renderer& renderer) const noexcept {
			// The components of the display are extracted.
			Sprite& display_sprite = display.get_sprite();
			int display_width = display_sprite.get_width();
			int display_height = display_sprite.get_height();
			
			// The display is blitted to.
			display_sprite.fill();
			
			display_sprite.blit(
				renderer.lined_render(
					to_string(),
					CARD_WIDTH * display_width,
					CARD_HEIGHT * display_height,
					CARD_SEPARATION_X * display_width,
					CARD_MAX_WIDTH * display_width,
					CARD_SEPARATION_Y * display_height,
					CARD_JUSTIFICATION
				),
				CARD_X,
				CARD_Y
			);
		}
		
	protected:
		/**
		 * This class should not be instantiated.
		 * The inheriting class must define the
		 *   card's name, type, and effects.
		 */
		Card(
			const std::string& name,
			const std::string& description,
			const std::string& type,
			const std::string& effects
		) noexcept:
			Affectable(effects),
			name(name),
			description(description),
			type(type)
		{}
		
		std::string name; // The card's name.
		std::string description; // A string that describes the card's effects.
		std::string type; // The card's type (fighter, supporter, or energy).
};

/**
 * A type of card that is attached to fighter cards.
 * These cards pay for the fighter's attack and retreat cost.
 */
class Energy: public Card {
	public:
		/**
		 * Constructs an energy card with the given name,
		 *   description, element, effects, and value.
		 */
		Energy(
			const std::string& name,
			const std::string& description,
			const std::string& element,
			const std::string& effects,
			int value
		) noexcept:
			Card(name, description, ENERGY_TYPE, effects),
			element(element),
			value(value)
		{}
		
		/**
		 * Sets the element of the energy card.
		 */
		void set_element(const std::string& element) noexcept {
			this->element = element;
		}
		
		/**
		 * Returns the energy card's value.
		 */
		int get_value() const noexcept {
			return value;
		}
		
		/**
		 * Returns the value of the energy card for the fighter's attacks.
		 * Usually, returns the value integer for fighters with a matching
		 *   element and zero for fighters without a matching element.
		 */
		int get_value(const std::string& element) const noexcept {
			if (effect_search(UNIVERSAL_EFFECT)) {
				return value;
			}
			
			return this->element == element ? value : 0;
		}
		
		/**
		 * Returns the energy card in string form.
		 * This string is designed for the Renderer class.
		 */
		std::string to_string() const noexcept {
			return
				element + " Element " + type + " Card\n\n"
				+ name + "\n\n" + description
			;
		}
		
	private:
		std::string element; // The element of the fighters that the energy card can power.
		int value; // The amount of energy that this energy card provides.
};

/**
 * A type of card that is played to help assist the player,
 *   but doesn't get played on the field to battle directly.
 */
class Supporter: public Card {
	public:
		/**
		 * Constructs a supporter card with its name, description, and effects.
		 */
		Supporter(
			const std::string& name,
			const std::string& description,
			const std::string& effects
		) noexcept:
			Card(name, description, SUPPORTER_TYPE, effects)
		{}
		
		/**
		 * Returns the supporter card in string form.
		 * This string is designed for the Renderer class.
		 */
		std::string to_string() const noexcept {
			return
				std::string(type) + " Card\n\n"
				+ name + "\n\n" + description
			;
		}
};

/**
 * A feature of all fighters that takes effect when used,
 *   all the time, or at certain points in the game.
 */
class Ability: public Card {
	public:
		/**
		 * Constructs an ability with its name, description,
		 *   effects, passivity, and maximum uses per turn.
		 */
		Ability(
			const std::string& name,
			const std::string& description,
			const std::string& effects,
			bool passive,
			int max_uses
		) noexcept:
			Card(name, description, ABILITY_TYPE, effects),
			passive(passive),
			max_uses(max_uses),
			uses(max_uses)
		{}
		
		/**
		 * Decreases the number of avialable ability uses.
		 */
		void use() noexcept {
			// The number of uses aren't decremented if the ability can be used infinitely.
			if (max_uses != INFINITE_USES) {
				--uses;
			}
		}
		
		/**
		 * Resets the number of avialable ability uses.
		 */
		void reset_uses() noexcept {
			uses = max_uses;
		}
		
		/**
		 * Returns true if the ability is usable.
		 * An ability is usable if it is not passive and
		 *   the number of uses is greater than 0
		 *   (if the maximum number of uses is non-zero,
		 *   as max_uses == 0 implies infinite uses).
		 * This method does not consider the specific
		 *   criteria featured in the ability's effects.
		 */
		bool usable() const noexcept {
			return !passive && (!max_uses || uses > 0);
		}
		
		/**
		 * Returns the ability in string form.
		 * The string is designed for the fighter to use
		 *   in its own to_string() member function.
		 */
		std::string to_string() const noexcept {
			return '\n' + std::string(type) + ": " + name + '\n' + description + '\n';
		}
		
		/**
		 * Returns true if this ability is passive.
		 */
		bool is_passive() const noexcept {
			return passive;
		}
		
		/**
		 * Returns the number of available ability uses.
		 */
		int get_uses() const noexcept {
			return uses;
		}
		
		/**
		 * Returns the maximum number of ability uses.
		 */
		int get_max_uses() const noexcept {
			return max_uses;
		}
		
	private:
		bool passive;
		int max_uses;
		int uses;
};

/**
 * A feature of all fighters that ends the turn when used.
 * Most attacks deal damage and many have an additional effect.
 */
class Attack: public Card {
	public:
		/**
		 * Contructs an attack with its name, description,
		 *   effects, base damage, and energy cost.
		 */
		Attack(
			const std::string& name,
			const std::string& description,
			const std::string& effects,
			int damage,
			int cost
		) noexcept:
			Card(name, description, ATTACK_TYPE, effects),
			damage(damage),
			cost(cost)
		{}
		
		/**
		 * Returns the cost of the attack.
		 */
		int get_cost() const noexcept {
			return cost;
		}
		
		/**
		 * Returns the attack's base damage.
		 */
		int get_damage() const noexcept {
			return damage;
		}
		
		/**
		 * Returns the attack in string form.
		 * The string is designed for the fighter to use
		 *   in its own to_string() member function.
		 */
		std::string to_string() const noexcept {
			return
				'\n' + std::string(type) + ": " + name + '\n'
				+ description + '\n'
				+ "\nAttack Cost: " + std::to_string(cost) + '\n'
			;
		}
		
	private:
		int damage; // The base damage of the attack.
		int cost; // The amount of energy needed to use the attack.
};

/**
 * A type of card that does battle against other fighters on the field.
 */
class Fighter: public Card {
	public:
		/**
		 * Constructs a fighter with its name, element, health,
		 *   retreat cost, rank, previous rank, ability, and attack.
		 */
		Fighter(
			const std::string& name,
			const std::string& element,
			int health,
			int retreat_cost,
			const std::string& old_rank,
			const std::string& ability_name,
			const std::string& ability_description,
			const std::string& ability_effects,
			bool ability_passive,
			int ability_uses,
			const std::string& attack_name,
			const std::string& attack_description,
			const std::string& attack_effects,
			int attack_damage,
			int attack_cost
		) noexcept:
			Card(name, FIGHTER_DESCRIPTION, FIGHTER_TYPE, FIGHTER_EFFECTS),
			element(element),
			health(health),
			max_health(health),
			retreat_cost(retreat_cost),
			old_rank(old_rank),
			ability(
				ability_name,
				ability_description,
				ability_effects,
				ability_passive,
				ability_uses
			),
			attack(
				attack_name,
				attack_description,
				attack_effects,
				attack_damage,
				attack_cost
			)
		{}
		
		/**
		 * Returns the fighter's element.
		 */
		const std::string& get_element() const noexcept {
			return element;
		}
		
		/**
		 * Returns the fighter card in string form.
		 * The string is designed for the Renderer class.
		 */
		std::string to_string() const noexcept {
			return
				element + " Element " + type + " Card\n\n"
				+ name
				+ (
					old_rank == NO_OLD_RANK ? ""
					: std::string(" (from ") + old_rank + ")"
				)
				+ "\n\n"
				+ "Health: " + std::to_string(health) + '/' + std::to_string(max_health) + '\n'
				+ ability.to_string()
				+ attack.to_string()
				+ "Retreat Cost: "
				+ std::to_string(retreat_cost - effect_count(AGILITY_EFFECT))
				+ '\n'
				+ "Ability Uses: "
				+ std::to_string(ability.get_uses())
				+ '/'
				+ std::to_string(ability.get_max_uses())
			;
		}
		
		/**
		 * Returns true if the fighter does not
		 *   rank up from any other fighter card.
		 */
		bool basic() const noexcept {
			return old_rank == NO_OLD_RANK;
		}
		
		/**
		 * Renders the card's text to the display.
		 * Also allows for the fighter's energy and effects to be seen.
		 */
		void view(
			Display& display,
			const Renderer& renderer,
			const Button& back_button,
			const std::string& message = EMPTY_MESSAGE
		) const noexcept {
			// The energy button is initialised.
			Button energy_button(
				renderer.render(
					FIGHTER_ENERGY_STRING,
					FIGHTER_ENERGY_WIDTH * display.width(),
					FIGHTER_ENERGY_HEIGHT * display.height(),
					FIGHTER_ENERGY_SEPARATION * display.width()
				),
				display,
				FIGHTER_ENERGY_X,
				FIGHTER_ENERGY_Y
			);
			
			// The effects button is initialised.
			Button effects_button(
				renderer.render(
					FIGHTER_EFFECTS_STRING,
					FIGHTER_EFFECTS_WIDTH * display.width(),
					FIGHTER_EFFECTS_HEIGHT * display.height(),
					FIGHTER_EFFECTS_SEPARATION * display.width()
				),
				display,
				FIGHTER_EFFECTS_X,
				FIGHTER_EFFECTS_Y
			);
			
			// True when this function should return.
			bool end = false;
			
			while (!end) {
				// The display is rendered.
				render(display, renderer);
				back_button.blit_to(display);
				energy_button.blit_to(display);
				effects_button.blit_to(display);
				display.update();
				
				while (true) {
					// The player can go back using the next or back buttons.
					if (
						Events::unpress(NEXT_KEY)
						|| Events::unpress(BACK_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The energy can be viewed by pressing the energy button.
					else if (energy_button.get_rectangle().unclick()) {
						view_energy(display, renderer, back_button, message);
						break;
					}
					
					// The effects can be viewed by pressing the effects button.
					else if (effects_button.get_rectangle().unclick()) {
						view_effects(display, renderer, back_button, message);
						break;
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Displays the energy cards attached to this fighter.
		 * The card details can be displayed by clicking on the energy card's name.
		 */
		void view_energy(
			Display& display,
			const Renderer& renderer,
			const Button& back_button,
			const std::string& message
		) const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The energy size sprite is intialised.
			Sprite energy_size_sprite(
				renderer.render(
					ENERGY_SIZE_STRING,
					ENERGY_SIZE_WIDTH * display.width(),
					ENERGY_SIZE_HEIGHT * display.height(),
					ENERGY_SIZE_SEPARATION * display.width()
				)
			);
			
			// Determines which cards are displayed.
			int page = 0;
			
			// True if the function should return.
			bool end = false;
			
			while (!end) {
				// The sprites are blitted to the display.
				display.fill();
				back_button.blit_to(display);
				display.blit(energy_size_sprite, ENERGY_SIZE_X, ENERGY_SIZE_Y);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (static_cast<int>(energy.size())  - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < energy.size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							Sprite(
								renderer.render(
									energy[page * PAGE_COUNT + i].get_name(),
									PAGE_WIDTH * display.width(),
									PAGE_HEIGHT * display.height(),
									PAGE_SEPARATION * display.width()
								)
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The value of the energy card is displayed.
					display.blit(
						renderer.render(
							display,
							ENERGY_VALUE_STRING,
							ENERGY_VALUE_WIDTH,
							ENERGY_VALUE_HEIGHT,
							ENERGY_VALUE_SEPARATION
						),
						ENERGY_VALUE_X,
						ENERGY_VALUE_Y + i * ENERGY_VALUE_Y_SHIFT
					);
				}
				
				// The total value of the energy cards attached is calculated.
				int total = energy_value();
				
				// The total value of the energy is rendered.
				display.blit(
					renderer.render(
						display,
						TOTAL_ENERGY_STRING,
						TOTAL_ENERGY_WIDTH,
						TOTAL_ENERGY_HEIGHT,
						TOTAL_ENERGY_SEPARATION
					),
					TOTAL_ENERGY_X,
					TOTAL_ENERGY_Y
				);
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The user can return to the previous menu with
					//   the use of the back button or submit key.
					if (
						Events::unpress(SUBMIT_KEY)
						|| Events::unpress(QUIT_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The page number is decremented (if possible).
					else if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (static_cast<int>(energy.size()) - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < energy.size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								energy[page * PAGE_COUNT + i].render(display, renderer);
								back_button.blit_to(display);
								display.update();
								
								// The player proceeds at their own discretion.
								while (
									!Events::unpress(QUIT_KEY)
									&& !Events::unpress(NEXT_KEY)
									&& !back_button.get_rectangle().unclick()
									&& message == EMPTY_MESSAGE
								) {
									Events::update();
								}
								
								found = true;
								break;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Displays the effects on this fighter.
		 * The details can be displayed by clicking on the effect's name.
		 */
		void view_effects(
			Display& display,
			const Renderer& renderer,
			const Button& back_button,
			const std::string& message
		) const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The vectors of effects and values are inItialised.
			std::vector<std::string> effect_names;
			std::vector<std::string> effect_values;
			
			// A pointer to a single effect.
			const std::vector<std::string>* effect = nullptr;
			
			for (int i = 0; i < EXPLANATION_COUNT; ++i) {
				if (EFFECT_CONDITIONS(i)) {
					effect_names.push_back(EFFECT_REPRESENTATIONS[i]);
					effect_values.push_back(EFFECT_VALUES(i));
				}
			}
			
			// Determines which effects are displayed.
			int page = 0;
			
			// True if the function should return.
			bool end = false;
			
			while (!end) {
				// The sprites are blitted to the display.
				display.fill();
				back_button.blit_to(display);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (static_cast<int>(effect_names.size()) - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < effect_names.size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							renderer.render(
								effect_names[page * PAGE_COUNT + i],
								PAGE_WIDTH * display.width(),
								PAGE_HEIGHT * display.height(),
								PAGE_SEPARATION * display.width()
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The value of the effect is displayed.
					display.blit(
						renderer.render(
							display,
							EFFECT_VALUE_STRING,
							EFFECT_VALUE_WIDTH,
							EFFECT_VALUE_HEIGHT,
							EFFECT_VALUE_SEPARATION
						),
						EFFECT_VALUE_X,
						EFFECT_VALUE_Y + i * EFFECT_VALUE_Y_SHIFT
					);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The user can return to the previous menu with
					//   the use of the back button or submit key.
					if (
						Events::unpress(SUBMIT_KEY)
						|| Events::unpress(QUIT_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The page number is decremented (if possible).
					else if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (static_cast<int>(effect_names.size()) - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < effect_names.size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								explain(
									display,
									renderer,
									back_button,
									message,
									effect_names[page * PAGE_COUNT + i],
									effect_values[page * PAGE_COUNT + i]
								);
								
								found = true;
								break;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Attaches the given card to this fighter.
		 */
		void attach(const Energy& e) noexcept {
			energy.push_back(e);
		}
		
		/**
		 * Resets the number of ability uses.
		 */
		void reset_ability() noexcept {
			ability.reset_uses();
		}
		
		/**
		 * Returns the name of the fighter that this fighter ranks up from.
		 */
		const std::string& get_old_rank() const noexcept {
			return old_rank;
		}
		
		/**
		 * For use when a fighter ranks up.
		 * Transfers all of the damage and energy cards from
		 *   this fighter card to the given fighter card.
		 * Removes all effects from this fighter.
		 */
		void rank_up(Fighter& f) noexcept {
			// Check for rank up effects.
			for (int i = 0; i < ability.get_effects().size(); ++i) {
				if (ability.get_effects()[i][0] == RANK_UP_EFFECT) {
					if (ability.get_effects()[i][1] == CONVERSION_EFFECT) {
						for (int j = 0; j < energy.size(); ++j) {
							energy[j].set_element(f.get_element());
						}
					}
				}
			}
			
			f.energy = energy;
			f.health = f.max_health - (max_health - health);
			reset();
		}
		
		/**
		 * Resets this fighter's health, energy, effects, and ability uses.
		 */
		void reset() noexcept {
			health = max_health;
			energy.clear();
			clear_effects();
			reset_ability();
		}
		
		/**
		 * Returns this fighter's effects (including the effects from a passive ability).
		 */
		std::vector<std::vector<std::string>> get_all_effects() const noexcept {
			std::vector<std::vector<std::string>> all_effects(effects);
			
			if (ability.is_passive()) {
				for (int i = 0; i < ability.get_effects().size(); ++i) {
					all_effects.push_back(ability.get_effects()[i]);
				}
			}
			
			return all_effects;
		}
		
		/**
		 * Returns true if this fighter's ability is usable.
		 */
		bool ability_usable() const noexcept {
			return ability.usable();
		}
		
		/**
		 * Returns true if this fighter has sufficient energy to attack.
		 */
		bool attack_usable() const noexcept {
			return energy_value() >= attack.get_cost();
		}
		
		/**
		 * Returns true if this fighter has sufficient energy to retreat.
		 */
		bool retreat_usable(int agility = 0) const noexcept {
			return
				energy_value()
				>= retreat_cost - effect_count(AGILITY_EFFECT) - agility
			;
		}
		
		/**
		 * Returns the effects of the ability.
		 */
		const std::vector<std::vector<std::string>>& get_ability_effects() const noexcept {
			return ability.get_effects();
		}
		
		/**
		 * Returns the name of the ability.
		 */
		const std::string& get_ability_name() const noexcept {
			return ability.get_name();
		}
		
		/**
		 * Clears the effects on the fighter, but not its ability.
		 */
		void clear_effects() noexcept {
			effects.clear();
		}
		
		/**
		 * Increments the number of uses of the ability.
		 */
		void use_ability() noexcept {
			ability.use();
		}
		
		/**
		 * Returns a pointer to the vector of strings matching the given effect.
		 * Returns the null pointer if the effect was not found.
		 * This member function consider the effects of the ability, as well.
		 */
		const std::vector<std::string>* effect_search(
			const std::string& effect
		) const noexcept {
			// The effect is searched for.
			for (int i = 0; i < effects.size(); ++i) {
				if (effects[i][0] == effect) {
					// A pointer to the vector of strings with the effect is returned.
					return &effects[i];
				}
			}
			
			// The effect wasn't found and a the ability is searched.
			if (ability.is_passive()) {
				return ability.effect_search(effect);
			}
			
			// Only passive abilities are checked.
			else {
				return nullptr;
			}
		}
		
		/**
		 * Counts the total effect value of an effect.
		 * The member function also considers the effects of passive abilities.
		 */
		int effect_count(const std::string& effect) const noexcept {
			int count = 0;
			
			for (int i = 0; i < effects.size(); ++i) {
				if (effects[i][0] == effect) {
					count += std::stoi(effects[i][1]);
				}
			}
			
			if (ability.is_passive()) {
				count += ability.effect_count(effect);
			}
			
			return count;
		}
		
		
		/**
		 * Calculates the total energy value of this fighter.
		 */
		int energy_value() const noexcept {
			int total = 0;
			
			for (int i = 0; i < energy.size(); ++i) {
				total += energy[i].get_value(element);
			}
			
			return total;
		}
		
		/**
		 * Returns a constant reference to the fighter's ability.
		 */
		const Ability& get_ability() const noexcept {
			return ability;
		}
		
		/**
		 * Returns a constant reference to the fighter's attack.
		 */
		const Attack& get_attack() const noexcept {
			return attack;
		}
		
		/**
		 * Deals damage to this fighter.
		 */
		void damage(int amount) noexcept {
			// The fighter should not be healed by negative damage.
			if (amount > 0) {
				health -= amount;
			}
		}
		
		/**
		 * Returns a constant reference to the vector of energy cards.
		 */
		const std::vector<Energy>& get_energy() const noexcept {
			return energy;
		}
		
		/**
		 * Returns the health of the fighter.
		 */
		int get_health() const noexcept {
			return health;
		}
		
		/**
		 * Heals the fighter according the passed argument.
		 * The fighter's health cannot exceed its maximum health.
		 * The fighter's health is not decreased with negative heals.
		 */
		void heal(int heal_value) noexcept {
			// Heals must increase the fighter's health.
			if (heal_value > 0) {
				// health <= max_health
				health =
					health + heal_value > max_health
					? max_health
					: health + heal_value
				;
			}
		}
		
	private:
		std::string element; // Determines which energy can power this fighter's attacks.
		int health; // When this reaches zero (or less), the fighter is defeated.
		int max_health; // The fighter's health cannot exceed this.
		int retreat_cost; // The energy value required for a retreat.
		std::string old_rank; // The fighter that this one ranks up from.
		Ability ability; // The fighter's ability.
		Attack attack; // The fighter's attack.
		std::vector<Energy> energy; // The energy attached to the fighter.
};
//}

// Cards
//{
// Fighters
//{
// Driver Family
//{
const Fighter DRIVER(
	DRIVER_NAME,
	DRIVER_ELEMENT,
	DRIVER_HEALTH,
	DRIVER_RETREAT_COST,
	DRIVER_OLD_RANK,
	DRIVER_ABILITY_NAME,
	DRIVER_ABILITY_DESCRIPTION,
	DRIVER_ABILITY_EFFECTS,
	DRIVER_ABILITY_PASSIVE,
	DRIVER_ABILITY_USES,
	DRIVER_ATTACK_NAME,
	DRIVER_ATTACK_DESCRIPTION,
	DRIVER_ATTACK_EFFECTS,
	DRIVER_ATTACK_DAMAGE,
	DRIVER_ATTACK_COST
);

const Fighter RACER(
	RACER_NAME,
	RACER_ELEMENT,
	RACER_HEALTH,
	RACER_RETREAT_COST,
	RACER_OLD_RANK,
	RACER_ABILITY_NAME,
	RACER_ABILITY_DESCRIPTION,
	RACER_ABILITY_EFFECTS,
	RACER_ABILITY_PASSIVE,
	RACER_ABILITY_USES,
	RACER_ATTACK_NAME,
	RACER_ATTACK_DESCRIPTION,
	RACER_ATTACK_EFFECTS,
	RACER_ATTACK_DAMAGE,
	RACER_ATTACK_COST
);

const Fighter HOT_RODDER(
	HOT_RODDER_NAME,
	HOT_RODDER_ELEMENT,
	HOT_RODDER_HEALTH,
	HOT_RODDER_RETREAT_COST,
	HOT_RODDER_OLD_RANK,
	HOT_RODDER_ABILITY_NAME,
	HOT_RODDER_ABILITY_DESCRIPTION,
	HOT_RODDER_ABILITY_EFFECTS,
	HOT_RODDER_ABILITY_PASSIVE,
	HOT_RODDER_ABILITY_USES,
	HOT_RODDER_ATTACK_NAME,
	HOT_RODDER_ATTACK_DESCRIPTION,
	HOT_RODDER_ATTACK_EFFECTS,
	HOT_RODDER_ATTACK_DAMAGE,
	HOT_RODDER_ATTACK_COST
);

const Fighter SAILOR(
	SAILOR_NAME,
	SAILOR_ELEMENT,
	SAILOR_HEALTH,
	SAILOR_RETREAT_COST,
	SAILOR_OLD_RANK,
	SAILOR_ABILITY_NAME,
	SAILOR_ABILITY_DESCRIPTION,
	SAILOR_ABILITY_EFFECTS,
	SAILOR_ABILITY_PASSIVE,
	SAILOR_ABILITY_USES,
	SAILOR_ATTACK_NAME,
	SAILOR_ATTACK_DESCRIPTION,
	SAILOR_ATTACK_EFFECTS,
	SAILOR_ATTACK_DAMAGE,
	SAILOR_ATTACK_COST
);

const Fighter PIRATE(
	PIRATE_NAME,
	PIRATE_ELEMENT,
	PIRATE_HEALTH,
	PIRATE_RETREAT_COST,
	PIRATE_OLD_RANK,
	PIRATE_ABILITY_NAME,
	PIRATE_ABILITY_DESCRIPTION,
	PIRATE_ABILITY_EFFECTS,
	PIRATE_ABILITY_PASSIVE,
	PIRATE_ABILITY_USES,
	PIRATE_ATTACK_NAME,
	PIRATE_ATTACK_DESCRIPTION,
	PIRATE_ATTACK_EFFECTS,
	PIRATE_ATTACK_DAMAGE,
	PIRATE_ATTACK_COST
);

const Fighter DIRT_BIKER(
	DIRT_BIKER_NAME,
	DIRT_BIKER_ELEMENT,
	DIRT_BIKER_HEALTH,
	DIRT_BIKER_RETREAT_COST,
	DIRT_BIKER_OLD_RANK,
	DIRT_BIKER_ABILITY_NAME,
	DIRT_BIKER_ABILITY_DESCRIPTION,
	DIRT_BIKER_ABILITY_EFFECTS,
	DIRT_BIKER_ABILITY_PASSIVE,
	DIRT_BIKER_ABILITY_USES,
	DIRT_BIKER_ATTACK_NAME,
	DIRT_BIKER_ATTACK_DESCRIPTION,
	DIRT_BIKER_ATTACK_EFFECTS,
	DIRT_BIKER_ATTACK_DAMAGE,
	DIRT_BIKER_ATTACK_COST
);

const Fighter MONSTER_TRUCKER(
	MONSTER_TRUCKER_NAME,
	MONSTER_TRUCKER_ELEMENT,
	MONSTER_TRUCKER_HEALTH,
	MONSTER_TRUCKER_RETREAT_COST,
	MONSTER_TRUCKER_OLD_RANK,
	MONSTER_TRUCKER_ABILITY_NAME,
	MONSTER_TRUCKER_ABILITY_DESCRIPTION,
	MONSTER_TRUCKER_ABILITY_EFFECTS,
	MONSTER_TRUCKER_ABILITY_PASSIVE,
	MONSTER_TRUCKER_ABILITY_USES,
	MONSTER_TRUCKER_ATTACK_NAME,
	MONSTER_TRUCKER_ATTACK_DESCRIPTION,
	MONSTER_TRUCKER_ATTACK_EFFECTS,
	MONSTER_TRUCKER_ATTACK_DAMAGE,
	MONSTER_TRUCKER_ATTACK_COST
);

const Fighter PILOT(
	PILOT_NAME,
	PILOT_ELEMENT,
	PILOT_HEALTH,
	PILOT_RETREAT_COST,
	PILOT_OLD_RANK,
	PILOT_ABILITY_NAME,
	PILOT_ABILITY_DESCRIPTION,
	PILOT_ABILITY_EFFECTS,
	PILOT_ABILITY_PASSIVE,
	PILOT_ABILITY_USES,
	PILOT_ATTACK_NAME,
	PILOT_ATTACK_DESCRIPTION,
	PILOT_ATTACK_EFFECTS,
	PILOT_ATTACK_DAMAGE,
	PILOT_ATTACK_COST
);

const Fighter ASTRONAUT(
	ASTRONAUT_NAME,
	ASTRONAUT_ELEMENT,
	ASTRONAUT_HEALTH,
	ASTRONAUT_RETREAT_COST,
	ASTRONAUT_OLD_RANK,
	ASTRONAUT_ABILITY_NAME,
	ASTRONAUT_ABILITY_DESCRIPTION,
	ASTRONAUT_ABILITY_EFFECTS,
	ASTRONAUT_ABILITY_PASSIVE,
	ASTRONAUT_ABILITY_USES,
	ASTRONAUT_ATTACK_NAME,
	ASTRONAUT_ATTACK_DESCRIPTION,
	ASTRONAUT_ATTACK_EFFECTS,
	ASTRONAUT_ATTACK_DAMAGE,
	ASTRONAUT_ATTACK_COST
);
//}

const Fighter* const ALL_FIGHTERS[FIGHTER_COUNT] = {
	&DRIVER,
	&RACER,
	&HOT_RODDER,
	&SAILOR,
	&PIRATE,
	&DIRT_BIKER,
	&MONSTER_TRUCKER,
	&PILOT,
	&ASTRONAUT
};
//}

// Supporters
//{
// Draw
//{
const Supporter PROFESSOR(
	PROFESSOR_NAME,
	PROFESSOR_DESCRIPTION,
	PROFESSOR_EFFECTS
);

const Supporter RESEARCHER(
	RESEARCHER_NAME,
	RESEARCHER_DESCRIPTION,
	RESEARCHER_EFFECTS
);

const Supporter LECTURER(
	LECTURER_NAME,
	LECTURER_DESCRIPTION,
	LECTURER_EFFECTS
);

const Supporter INVESTOR(
	INVESTOR_NAME,
	INVESTOR_DESCRIPTION,
	INVESTOR_EFFECTS
);

const Supporter BANKER(
	BANKER_NAME,
	BANKER_DESCRIPTION,
	BANKER_EFFECTS
);

const Supporter GAMBLER(
	GAMBLER_NAME,
	GAMBLER_DESCRIPTION,
	GAMBLER_EFFECTS
);
//}

const Supporter* const ALL_SUPPORTERS[SUPPORTER_COUNT] = {
	&PROFESSOR,
	&RESEARCHER,
	&LECTURER,
	&INVESTOR,
	&BANKER,
	&GAMBLER
};
//}

// Energy
//{
// Basic Energy
//{
const Energy FIRE_ENERGY(
	FIRE_ENERGY_NAME,
	FIRE_ENERGY_DESCRIPTION,
	FIRE_ENERGY_ELEMENT,
	FIRE_ENERGY_EFFECTS,
	FIRE_ENERGY_VALUE
);

const Energy AIR_ENERGY(
	AIR_ENERGY_NAME,
	AIR_ENERGY_DESCRIPTION,
	AIR_ENERGY_ELEMENT,
	AIR_ENERGY_EFFECTS,
	AIR_ENERGY_VALUE
);

const Energy WATER_ENERGY(
	WATER_ENERGY_NAME,
	WATER_ENERGY_DESCRIPTION,
	WATER_ENERGY_ELEMENT,
	WATER_ENERGY_EFFECTS,
	WATER_ENERGY_VALUE
);

const Energy EARTH_ENERGY(
	EARTH_ENERGY_NAME,
	EARTH_ENERGY_DESCRIPTION,
	EARTH_ENERGY_ELEMENT,
	EARTH_ENERGY_EFFECTS,
	EARTH_ENERGY_VALUE
);
//}

// Special Energy
//{
const Energy TWIN_ENERGY(
	TWIN_ENERGY_NAME,
	TWIN_ENERGY_DESCRIPTION,
	TWIN_ENERGY_ELEMENT,
	TWIN_ENERGY_EFFECTS,
	TWIN_ENERGY_VALUE
);

const Energy UNIVERSAL_ENERGY(
	UNIVERSAL_ENERGY_NAME,
	UNIVERSAL_ENERGY_DESCRIPTION,
	UNIVERSAL_ENERGY_ELEMENT,
	UNIVERSAL_ENERGY_EFFECTS,
	UNIVERSAL_ENERGY_VALUE
);
//}

const Energy* const ALL_ENERGY[ENERGY_COUNT] = {
	&FIRE_ENERGY,
	&AIR_ENERGY,
	&WATER_ENERGY,
	&EARTH_ENERGY,
	&TWIN_ENERGY,
	&UNIVERSAL_ENERGY
};
//}
//}

// Complex Classes
//{
/**
 * A generic storage for any quantity of cards.
 */
class CardStore {
	public:
		/**
		 * Constructs an empty card store.
		 */
		CardStore() noexcept {}
		
		/**
		 * Constructs a deck consisting of the cards passed (in the deck code).
		 */
		CardStore(const std::string& deck_code) noexcept {
			std::stringstream stream(deck_code);
			
			// The fighter cards are initialised.
			for (int i = 0; i < FIGHTER_COUNT; ++i) {
				int count;
				stream >> count;
				
				for (int j = 0; j < count; ++j) {
					fighters.push_back(*ALL_FIGHTERS[i]);
				}
			}
			
			// The supporter cards are intialised.
			for (int i = 0; i < SUPPORTER_COUNT; ++i) {
				int count;
				stream >> count;
				
				for (int j = 0; j < count; ++j) {
					supporters.push_back(*ALL_SUPPORTERS[i]);
				}
			}
			
			// The energy cards are initialised.
			for (int i = 0; i < ENERGY_COUNT; ++i) {
				int count;
				stream >> count;
				
				for (int j = 0; j < count; ++j) {
					energy.push_back(*ALL_ENERGY[i]);
				}
			}
		}
	
		/**
		 * Returns a reference to the card at the given index.
		 */
		Card& operator[](int index) noexcept {
			// If the index is in the fighter range, the fighter card is returned.
			if (index < fighters.size()) {
				return fighters[index];
			}
			
			else {
				index -= fighters.size();
				
				// If the index is in the supporter range,
				//   the supporter card is returned.
				if (index < supporters.size()) {
					return supporters[index];
				}
				
				// If the index is in the energy range,
				//   the energy card is returned.
				else {
					return energy[index - supporters.size()];
				}
			}
		}
	
		/**
		 * Returns a constant reference to the card at the given index.
		 */
		const Card& operator[](int index) const noexcept {
			// If the index is in the fighter range, the fighter card is returned.
			if (index < fighters.size()) {
				return fighters[index];
			}
			
			else {
				index -= fighters.size();
				
				// If the index is in the supporter range,
				//   the supporter card is returned.
				if (index < supporters.size()) {
					return supporters[index];
				}
				
				// If the index is in the energy range,
				//   the energy card is returned.
				else {
					return energy[index - supporters.size()];
				}
			}
		}
	
		/**
		 * Returns the number of cards stored.
		 */
		int size() const noexcept {
			return fighters.size() + supporters.size() + energy.size();
		}
		
		/**
		 * Returns true if this is a valid starting hand.
		 */
		bool valid() const noexcept {
			bool invalid = true;
			
			for (int i = 0; i < fighters.size(); ++i) {
				if (fighters[i].basic()) {
					invalid = false;
					break;
				}
			}
			
			return !invalid;
		}
		
		/**
		 * Stores a fighter card in the store.
		 */
		void store(const Fighter& f) noexcept {
			fighters.push_back(f);
		}
		
		/**
		 * Stores a supporter card in the store.
		 */
		void store(const Supporter& s) noexcept {
			supporters.push_back(s);
		}
		
		/**
		 * Stores an energy card in the store.
		 */
		void store(const Energy& e) noexcept {
			energy.push_back(e);
		}
		
		/**
		 * Stores a card in the store.
		 */
		void store(const Card& card) noexcept {
			// A fighter card is stored.
			if (card.get_type() == FIGHTER_TYPE) {
				store(static_cast<const Fighter&>(card));
			}
			
			// A supporter card is stored.
			else if (card.get_type() == SUPPORTER_TYPE) {
				store(static_cast<const Supporter&>(card));
			}
			
			// A energy card is stored.
			else {
				store(static_cast<const Energy&>(card));
			}
		}
		
		/**
		 * Stores a card in the store.
		 */
		void store(const std::unique_ptr<Card>& card) noexcept {
			store(*card);
		}
		
		/**
		 * Removes the card at the specified index.
		 */
		std::unique_ptr<Card> remove(int index = 0) {
			if (!size()) {
				throw std::runtime_error(EMPTY_CARD_STORE);
			}
			
			Card& card = operator[](index);
			std::unique_ptr<Card> card_pointer;
			
			if (card.get_type() == FIGHTER_TYPE) {
				card_pointer = std::make_unique<Fighter>(static_cast<Fighter&>(card));
			}
			
			else if (card.get_type() == SUPPORTER_TYPE) {
				card_pointer = std::make_unique<Supporter>(static_cast<Supporter&>(card));
			}
			
			else {
				card_pointer = std::make_unique<Energy>(static_cast<Energy&>(card));
			}
			
			// If the index is in the fighter range, the fighter card is erased.
			if (index < fighters.size()) {
				fighters.erase(fighters.cbegin() + index);
			}
			
			else {
				index -= fighters.size();
				
				// If the index is in the supporter range,
				//   the supporter card is erased.
				if (index < supporters.size()) {
					supporters.erase(supporters.cbegin() + index);
				}
				
				// If the index is in the energy range,
				//   the energy card is erased.
				else {
					energy.erase(energy.cbegin() + (index - supporters.size()));
				}
			}
			
			return card_pointer;
		}
		
		/**
		 * Draws a random card.
		 */
		std::unique_ptr<Card> draw(std::mt19937& generator) {
			return remove(std::uniform_int_distribution<>(0, size() - 1)(generator));
		}
		
		/**
		 * Displays the card store's contents with various modes.
		 */
		void view(
			Display& display,
			const Renderer& renderer,
			const std::string& message = EMPTY_MESSAGE
		) const noexcept {
			// The back button is initialised.
			Button back_button(
				renderer.render(
					BACK_STRING,
					BACK_WIDTH * display.width(),
					BACK_HEIGHT * display.height(),
					BACK_SEPARATION * display.width()
				),
				display,
				BACK_X,
				BACK_Y
			);
			
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The store size sprite is intialised.
			Sprite store_size_sprite(
				renderer.render(
					STORE_SIZE_STRING,
					STORE_SIZE_WIDTH * display.width(),
					STORE_SIZE_HEIGHT * display.height(),
					STORE_SIZE_SEPARATION * display.width()
				)
			);
			
			// Determines which cards are displayed.
			int page = 0;
			
			// True if the function should return.
			bool end = false;
			
			while (!end) {
				// The sprites are blitted to the display.
				display.fill();
				back_button.blit_to(display);
				display.blit(store_size_sprite, STORE_SIZE_X, STORE_SIZE_Y);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (size() - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							Sprite(
								renderer.render(
									operator[](page * PAGE_COUNT + i).get_name(),
									PAGE_WIDTH * display.width(),
									PAGE_HEIGHT * display.height(),
									PAGE_SEPARATION * display.width()
								)
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The user can return to the previous menu with
					//   the use of the back button or submit key.
					if (
						Events::unpress(SUBMIT_KEY)
						|| Events::unpress(QUIT_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The page number is decremented (if possible).
					else if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (size() - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								operator[](page * PAGE_COUNT + i).render(display, renderer);
								back_button.blit_to(display);
								display.update();
								
								// The player proceeds at their own discretion.
								while (
									!Events::unpress(QUIT_KEY)
									&& !Events::unpress(NEXT_KEY)
									&& !back_button.get_rectangle().unclick()
									&& message == EMPTY_MESSAGE
								) {
									Events::update();
								}
								
								found = true;
								break;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
	
		/**
		 * Chooses a basic fighter in the store and returns its index.
		 */
		int choose_basic(
			Display& display,
			const Renderer& renderer
		) const noexcept {
			// The components of the display are extracted.
			Sprite& display_sprite = display.get_sprite();
			int display_width = display_sprite.get_width();
			int display_height = display_sprite.get_height();
			
			// The basic fighter sprite is initialised.
			Sprite basic_fighter_sprite(
				renderer.render(
					BASIC_FIGHTER_STRING,
					BASIC_FIGHTER_WIDTH * display_width,
					BASIC_FIGHTER_HEIGHT * display_height,
					BASIC_FIGHTER_SEPARATION * display_width
				)
			);
			
			// The back button is initialised.
			Button back_button(
				renderer.render(
					BACK_STRING,
					BACK_WIDTH * display_width,
					BACK_HEIGHT * display_height,
					BACK_SEPARATION * display_width
				),
				display_sprite,
				BACK_X,
				BACK_Y
			);
			
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display_width,
					LEFT_HEIGHT * display_height
				),
				display_sprite,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display_width,
					RIGHT_HEIGHT * display_height
				),
				display_sprite,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The choice buttons are initialised.
			std::vector<Button> choice_buttons;
			
			for (int i = 0; i < PAGE_COUNT; ++i) {
				choice_buttons.push_back(
					Button(
						renderer.render(
							CHOICE_STRING,
							CHOICE_WIDTH * display_width,
							CHOICE_HEIGHT * display_height,
							CHOICE_SEPARATION * display_width
						),
						display_sprite,
						CHOICE_X,
						CHOICE_Y + i * CHOICE_Y_SHIFT
					)
				);
			}
	
			// Determines which cards are displayed.
			int page = 0;
			
			while (true) {
				// The sprites are blitted to the display.
				display_sprite.fill();
				display_sprite.blit(
					basic_fighter_sprite,
					BASIC_FIGHTER_X,
					BASIC_FIGHTER_Y
				);
				
				if (page > 0) {
					left_button.blit_to(display_sprite);
				}
				
				if (page < (size() - 1) / PAGE_COUNT) {
					right_button.blit_to(display_sprite);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							renderer.render(
								operator[](page * PAGE_COUNT + i).get_name(),
								PAGE_WIDTH * display_width,
								PAGE_HEIGHT * display_height,
								PAGE_SEPARATION * display_width
							),
							display_sprite,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display_sprite);
					
					if (
						page * PAGE_COUNT + i < fighters.size()
						&& static_cast<const Fighter&>(operator[](
							page * PAGE_COUNT + i
						)).basic()
					) {
						choice_buttons[i].blit_to(display_sprite);
					}
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The page number is decremented (if possible).
					if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (size() - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT && page * PAGE_COUNT + i < size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								operator[](page * PAGE_COUNT + i).render(display, renderer);
								back_button.blit_to(display_sprite);
								display.update();
								
								while (
									!Events::unpress(QUIT_KEY)
									&& !back_button.get_rectangle().unclick()
								) {
									Events::update();
								}
								
								found = true;
								break;
							}
							
							// Chooses a fighter.
							else if (
								page * PAGE_COUNT + i < fighters.size()
								&& static_cast<const Fighter&>(operator[](
									page * PAGE_COUNT + i
								)).basic()
								&& choice_buttons[i].get_rectangle().unclick()
							) {
								return page * PAGE_COUNT + i;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Displays the card store's size.
		 */
		void view_size(Display& display, const Renderer& renderer) const noexcept {
			display.fill();
			display.blit(
				renderer.lined_render(
					VIEW_SIZE_STRING,
					VIEW_SIZE_WIDTH * display.width(),
					VIEW_SIZE_HEIGHT * display.height(),
					VIEW_SIZE_SEPARATION_X * display.width(),
					VIEW_SIZE_MAX_WIDTH * display.width(),
					VIEW_SIZE_SEPARATION_Y * display.height(),
					VIEW_SIZE_JUSTIFICATION
				),
				VIEW_SIZE_X,
				VIEW_SIZE_Y
			);
		}
		
		/**
		 * Allows one to choose a card to play.
		 * Returns the index of the card chosen to be played.
		 */
		int play(
			Display& display,
			const Renderer& renderer,
			const Button& back_button,
			const std::string& message = EMPTY_MESSAGE
		) const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The store size sprite is intialised.
			Sprite store_size_sprite(
				renderer.render(
					STORE_SIZE_STRING,
					STORE_SIZE_WIDTH * display.width(),
					STORE_SIZE_HEIGHT * display.height(),
					STORE_SIZE_SEPARATION * display.width()
				)
			);
			
			// The play buttons are initialised.
			std::vector<Button> play_buttons;
			
			for (int i = 0; i < PAGE_COUNT; ++i) {
				play_buttons.push_back(
					Button(
						renderer.render(
							display,
							PLAY_CARD_STRING,
							PLAY_CARD_WIDTH,
							PLAY_CARD_HEIGHT,
							PLAY_CARD_SEPARATION
						),
						display,
						PLAY_CARD_X,
						PLAY_CARD_Y + i * PLAY_CARD_Y_SHIFT
					)
				);
			}
			
			// Determines which cards are displayed.
			int page = 0;
			
			while (true) {
				// The sprites are blitted to the display.
				display.fill();
				back_button.blit_to(display);
				display.blit(store_size_sprite, STORE_SIZE_X, STORE_SIZE_Y);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (size() - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							renderer.render(
								operator[](page * PAGE_COUNT + i).get_name(),
								PAGE_WIDTH * display.width(),
								PAGE_HEIGHT * display.height(),
								PAGE_SEPARATION * display.width()
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The corresponding play button is displayed.
					play_buttons[i].blit_to(display);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The player can go back with the back button.
					// Receiving a message also moves the player back.
					if (
						Events::unpress(BACK_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						return NO_CHOICE;
					}
					
					// The page number is decremented (if possible).
					else if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (size() - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT && page * PAGE_COUNT + i < size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								operator[](page * PAGE_COUNT + i).render(display, renderer);
								back_button.blit_to(display);
								display.update();
								
								while (
									!Events::unpress(QUIT_KEY)
									&& !back_button.get_rectangle().unclick()
								) {
									Events::update();
								}
								
								found = true;
								break;
							}
							
							// Chooses a card.
							else if (play_buttons[i].get_rectangle().unclick()) {
								return page * PAGE_COUNT + i;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Identical to play(), but has a choice buttons, instead of play buttons
		 *   and the player cannot return to the previous menu without making a choice.
		 */
		int choose(
			Display& display,
			const Renderer& renderer,
			const Button& back_button
		) const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The store size sprite is intialised.
			Sprite store_size_sprite(
				renderer.render(
					STORE_SIZE_STRING,
					STORE_SIZE_WIDTH * display.width(),
					STORE_SIZE_HEIGHT * display.height(),
					STORE_SIZE_SEPARATION * display.width()
				)
			);
			
			// The choice buttons are initialised.
			std::vector<Button> choice_buttons;
			
			for (int i = 0; i < PAGE_COUNT; ++i) {
				choice_buttons.push_back(
					Button(
						renderer.render(
							display,
							CHOICE_STRING,
							CHOICE_WIDTH,
							CHOICE_HEIGHT,
							CHOICE_SEPARATION
						),
						display,
						CHOICE_X,
						CHOICE_Y + i * CHOICE_Y_SHIFT
					)
				);
			}
	
			// Determines which cards are displayed.
			int page = 0;
			
			while (true) {
				// The sprites are blitted to the display.
				display.fill();
				display.blit(store_size_sprite, STORE_SIZE_X, STORE_SIZE_Y);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (size() - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							renderer.render(
								operator[](page * PAGE_COUNT + i).get_name(),
								PAGE_WIDTH * display.width(),
								PAGE_HEIGHT * display.height(),
								PAGE_SEPARATION * display.width()
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The corresponding play button is displayed.
					choice_buttons[i].blit_to(display);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The page number is decremented (if possible).
					if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (size() - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT && page * PAGE_COUNT + i < size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								operator[](page * PAGE_COUNT + i).render(display, renderer);
								back_button.blit_to(display);
								display.update();
								
								while (
									!Events::unpress(QUIT_KEY)
									&& !back_button.get_rectangle().unclick()
								) {
									Events::update();
								}
								
								found = true;
								break;
							}
							
							// Chooses a card.
							else if (choice_buttons[i].get_rectangle().unclick()) {
								return page * PAGE_COUNT + i;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
	private:
		std::vector<Fighter> fighters;     // The store of fighter cards.
		std::vector<Supporter> supporters; // The store of supporter cards.
		std::vector<Energy> energy;        // The store of energy cards.
};

/**
 * A class that defines a player.
 */
class Player: public Affectable {
	public:
		/**
		 * Constructs a player with their deck, an empty hand, an empty trash,
		 *   an empty store of life cards, and an empty board of fighters.
		 */
		Player(
			const std::string& deck_code,
			Display& display,
			const Renderer& renderer,
			const Messenger& messenger,
			MessengerPackage& messenger_package,
			Thread& messenger_thread,
			const Button& back_button,
			const Button& next_button,
			CardStore& the_void,
			std::mt19937& generator,
			bool opposing,
			const bool& turn,
			const int& turn_count
		) noexcept:
			Affectable(PLAYER_EFFECTS),
			deck(deck_code),
			display(display),
			renderer(renderer),
			messenger(messenger),
			messenger_package(messenger_package),
			messenger_thread(messenger_thread),
			back_button(back_button),
			next_button(next_button),
			the_void(the_void),
			generator(generator),
			opposing(opposing),
			message(messenger_package.get_string()),
			turn(turn),
			turn_count(turn_count)
		{}
		
		/**
		 * Sets the opponent.
		 */
		void set_opponent(Player& opponent) noexcept {
			this->opponent = &opponent;
		}
		
		/**
		 * Returns true if the player's hand is valid for play.
		 */
		bool valid_hand() const noexcept {
			return hand.size();
		}
		
		/**
		 * Randomly draws cards from the deck to the hand.
		 * Draws all of the cards in the deck by default.
		 */
		void draw(int count = -1) noexcept {
			if (count < 0) {
				count = deck.size();
			}
			
			for (int i = 0; deck.size() && i < count; ++i) {
				last_drawn = deck.draw(generator);
				hand.store(*last_drawn);
			}
		}
	
		/**
		 * Shuffles the hand into the deck.
		 */
		void shuffle() noexcept {
			while (hand.size()) {
				deck.store(*hand.remove());
			}
		}
		
		/**
		 * Discards the entire hand.
		 */
		void discard() noexcept {
			while (hand.size()) {
				trash.store(*hand.remove());
			}
		}
		
		/**
		 * Draws a new hand from the deck.
		 * If the hand had no basic cards, they are displayed
		 *   and are shuffled back into the deck.
		 */
		void mulligan() noexcept {
			// The components of the display are extracted.
			Sprite& display_sprite = display.get_sprite();
			int display_width = display_sprite.get_width();
			int display_height = display_sprite.get_height();
			
			// The cards are drawn from the deck to form the starting hand.
			draw(HAND_SIZE);
			
			// If the hand is invalid, the hand is displayed are shuffled back into the deck.
			if (!hand.valid()) {
				// The next button is initialised.
				Button next_button(
					renderer.render(
						NEXT_STRING,
						NEXT_WIDTH * display_width,
						NEXT_HEIGHT * display_height,
						NEXT_SEPARATION * display_width
					),
					display_sprite,
					NEXT_X,
					NEXT_Y
				);
				
				// The player is notified that the mulligan failed.
				display_sprite.fill();
				display_sprite.blit(
					renderer.lined_render(
						MULLIGAN_FAIL_STRING,
						MULLIGAN_FAIL_WIDTH * display_width,
						MULLIGAN_FAIL_HEIGHT * display_height,
						MULLIGAN_FAIL_SEPARATION_X * display_width,
						MULLIGAN_FAIL_MAX_WIDTH * display_width,
						MULLIGAN_FAIL_SEPARATION_Y * display_height,
						MULLIGAN_FAIL_JUSTIFICATION
					),
					MULLIGAN_FAIL_X,
					MULLIGAN_FAIL_Y
				);
				next_button.blit_to(display_sprite);
				display.update();
				
				// Proceeds at the player's discretion.
				while (
					!Events::unpress(SUBMIT_KEY)
					&& !next_button.get_rectangle().unclick()
				) {
					Events::update();
				}
				
				// The hand is displayed.
				hand.view(display, renderer);
				
				// The player is notified that another mulligan will be performed.
				display_sprite.fill();
				display_sprite.blit(
					renderer.lined_render(
						NEW_MULLIGAN_STRING,
						NEW_MULLIGAN_WIDTH * display_width,
						NEW_MULLIGAN_HEIGHT * display_height,
						NEW_MULLIGAN_SEPARATION_X * display_width,
						NEW_MULLIGAN_MAX_WIDTH * display_width,
						NEW_MULLIGAN_SEPARATION_Y * display_height,
						NEW_MULLIGAN_JUSTIFICATION
					),
					NEW_MULLIGAN_X,
					NEW_MULLIGAN_Y
				);
				next_button.blit_to(display_sprite);
				display.update();
				
				// Proceeds at the player's discretion.
				while (
					!Events::unpress(SUBMIT_KEY)
					&& !next_button.get_rectangle().unclick()
				) {
					Events::update();
				}
				
				// The hand is shuffled back into the deck.
				shuffle();
			}
			
			++mulligan_count;
		}
		
		/**
		 * Returns the number of mulligans performed.
		 */
		int count_mulligans() const noexcept {
			return mulligan_count;
		}
	
		/**
		 * Places the player's life cards.
		 * Reveals the life cards if the player owns them.
		 */
		void set_life_cards() noexcept {
			for (int i = 0; i < LIFE_SIZE; ++i) {
				life_cards.store(*deck.draw(generator));
			}
			
			// The components of the display are extracted.
			Sprite& display_sprite = display.get_sprite();
			int display_width = display_sprite.get_width();
			int display_height = display_sprite.get_height();
			
			// The life card message is displayed.
			display_sprite.fill();
			display_sprite.blit(
				renderer.lined_render(
					LIFE_STRING,
					LIFE_WIDTH * display_width,
					LIFE_HEIGHT * display_height,
					LIFE_SEPARATION_X * display_width,
					LIFE_MAX_WIDTH * display_width,
					LIFE_SEPARATION_Y * display_height,
					LIFE_JUSTIFICATION
				),
				LIFE_X,
				LIFE_Y
			);
			next_button.blit_to(display_sprite);
			display.update();
			
			// The player can advance at their discretion.
			while (
				!Events::unpress(SUBMIT_KEY)
				&& !next_button.get_rectangle().unclick()
			) {
				Events::update();
			}
			
			// The player may see their own life cards.
			if (!opposing) {
				life_cards.view(display, renderer);
			}
		}
	
		/**
		 * Chooses the player's active fighter.
		 * Returns the choice in string form.
		 */
		std::string set_active() noexcept {
			// The components of the display are extracted.
			Sprite& display_sprite = display.get_sprite();
			int display_width = display_sprite.get_width();
			int display_height = display_sprite.get_height();
			
			display_sprite.fill();
			display_sprite.blit(
				renderer.lined_render(
					SET_ACTIVE_STRING,
					SET_ACTIVE_WIDTH * display_width,
					SET_ACTIVE_HEIGHT * display_height,
					SET_ACTIVE_SEPARATION_X * display_width,
					SET_ACTIVE_MAX_WIDTH * display_width,
					SET_ACTIVE_SEPARATION_Y * display_height,
					SET_ACTIVE_JUSTIFICATION
				),
				SET_ACTIVE_X,
				SET_ACTIVE_Y
			);
			next_button.blit_to(display_sprite);
			display.update();
			
			while (
				!Events::unpress(SUBMIT_KEY)
				&& !next_button.get_rectangle().unclick()
			) {
				Events::update();
			}
			
			int choice = hand.choose_basic(display, renderer);
			fighters.push_back(static_cast<Fighter&>(*hand.remove(choice)));
		
			return std::to_string(choice);
		}
		
		/**
		 * Chooses the opponent's active fighter.
		 */
		void set_active(const std::string& choice) noexcept {
			fighters.push_back(static_cast<Fighter&>(*hand.remove(std::stoi(choice))));
		}
	
		/**
		 * Returns true if the player can draw from their deck.
		 */
		bool can_draw() const noexcept {
			return deck.size();
		}
	
		/**
		 * Displays the last drawn card's name.
		 */
		void display_last_drawn() const noexcept {
			display.fill();
			display.blit(
				renderer.lined_render(
					LAST_DRAWN_STRING,
					LAST_DRAWN_WIDTH * display.width(),
					LAST_DRAWN_HEIGHT * display.height(),
					LAST_DRAWN_SEPARATION_X * display.width(),
					LAST_DRAWN_MAX_WIDTH * display.width(),
					LAST_DRAWN_SEPARATION_Y * display.height(),
					LAST_DRAWN_JUSTIFICATION
				),
				LAST_DRAWN_X,
				LAST_DRAWN_Y
			);
		}
	
		/**
		 * Allows the player to view their hand.
		 */
		void view_hand() const noexcept {
			hand.view(display, renderer, message);
		}
		
		/**
		 * Allows the player to view their deck.
		 */
		void view_deck() const noexcept {
			deck.view(display, renderer, message);
		}
		
		/**
		 * Allows the player to view their trash.
		 */
		void view_trash() const noexcept {
			trash.view(display, renderer, message);
		}
		
		/**
		 * Allows the player to view their life cards.
		 */
		void view_life_cards() const noexcept {
			life_cards.view(display, renderer, message);
		}
	
		/**
		 * Renders the hand size to the display.
		 */
		void view_hand_size() const noexcept {
			hand.view_size(display, renderer);
			back_button.blit_to(display);
			display.update();
			
			// The player proceeds at their own discretion.
			while (
				!Events::unpress(NEXT_KEY)
				&& !Events::unpress(BACK_KEY)
				&& !back_button.get_rectangle().unclick()
				&& message == EMPTY_MESSAGE
			) {
				Events::update();
			}
		}
		
		/**
		 * Renders the deck size to the display.
		 */
		void view_deck_size() const noexcept {
			deck.view_size(display, renderer);
			back_button.blit_to(display);
			display.update();
			
			// The player proceeds at their own discretion.
			while (
				!Events::unpress(NEXT_KEY)
				&& !Events::unpress(BACK_KEY)
				&& !back_button.get_rectangle().unclick()
				&& message == EMPTY_MESSAGE
			) {
				Events::update();
			}
		}
		
		/**
		 * Renders the life cards size to the display.
		 */
		void view_life_cards_size() const noexcept {
			life_cards.view_size(display, renderer);
			back_button.blit_to(display);
			display.update();
			
			// The player proceeds at their own discretion.
			while (
				!Events::unpress(NEXT_KEY)
				&& !Events::unpress(BACK_KEY)
				&& !back_button.get_rectangle().unclick()
				&& message == EMPTY_MESSAGE
			) {
				Events::update();
			}
		}
	
		/**
		 * Displays the player's active fighter.
		 */
		void view_active() const noexcept {
			fighters[0].view(display, renderer, back_button, message);
		}
		
		/**
		 * Displays the player's benched fighters.
		 * Clicking a fighter's name gives more details.
		 */
		void view_bench() const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The bench size sprite is intialised.
			Sprite bench_size_sprite(
				renderer.render(
					BENCH_SIZE_STRING,
					BENCH_SIZE_WIDTH * display.width(),
					BENCH_SIZE_HEIGHT * display.height(),
					BENCH_SIZE_SEPARATION * display.width()
				)
			);
			
			// Determines which cards are displayed.
			int page = 0;
			
			// True if the function should return.
			bool end = false;
			
			while (!end) {
				// The sprites are blitted to the display.
				display.fill();
				back_button.blit_to(display);
				display.blit(bench_size_sprite, BENCH_SIZE_X, BENCH_SIZE_Y);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (fighters.size() - 2) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < fighters.size() - 1;
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							Sprite(
								renderer.render(
									fighters[BENCH_INDEX + page * PAGE_COUNT + i].get_name(),
									PAGE_WIDTH * display.width(),
									PAGE_HEIGHT * display.height(),
									PAGE_SEPARATION * display.width()
								)
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The user can return to the previous menu with
					//   the use of the back button or submit key.
					if (
						Events::unpress(SUBMIT_KEY)
						|| Events::unpress(QUIT_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The page number is decremented (if possible).
					else if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (fighters.size() - 2) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < fighters.size() - 1;
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								fighters[BENCH_INDEX + page * PAGE_COUNT + i].view(
									display,
									renderer,
									back_button,
									message
								);
								
								found = true;
								break;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
	
		/**
		 * Allows the player to play a card from their hand.
		 */
		void play(int index = NO_CHOICE) noexcept {
			if (index == NO_CHOICE) {
				index = hand.play(display, renderer, back_button, message);
			}
			
			// The chosen card is checked.
			if (index >= 0) {
				if (hand[index].get_type() == FIGHTER_TYPE) {
					Fighter& f = static_cast<Fighter&>(hand[index]);
					
					if (!f.basic() && !rank_search(f)) {
						announce(UNRANKABLE_ANNOUNCEMENT);
						
						return;
					}
				}
						
				if (!opposing) {
					messenger.send(PLAY_MESSAGE);
					messenger.send(std::to_string(index));
				}
				
				std::unique_ptr<Card> chosen(hand.remove(index));
				
				// The card is a fighter card.
				if (chosen->get_type() == FIGHTER_TYPE) {
					Fighter& f = static_cast<Fighter&>(*chosen);
					
					// The fighter card is basic.
					if (f.basic()) {
						// The card is played onto the bench.
						fighters.push_back(f);
						announce(BENCHED_ANNOUNCEMENT);
					}
					
					// The fighter is to rank up another.
					else {
						play(f);
					}
				}
				
				// The chosen card is a supporter card.
				else if (chosen->get_type() == SUPPORTER_TYPE) {
					play(static_cast<Supporter&>(*chosen));
				}
				
				// The chosen card is an energy card.
				else {
					play(static_cast<Energy&>(*chosen));
				}
			}
		}
		
		/**
		 * Allows the player to rank up a fighter card into another.
		 */
		void play(Fighter& f) noexcept {
			// Negative if there are multiple fighters that could be ranked up.
			int index = -1;
			
			for (int i = 0; i < fighters.size(); ++i) {
				if (fighters[i].get_name() == f.get_old_rank()) {
					if (index < 0) {
						index = i;
					}
					
					else {
						index = -1;
						break;
					}
				}
			}
			
			// The player should choose a fighter to rank up.
			if (index < 0) {
				// The player chooses the recipient of the energy.
				if (!opposing) {
					index = rank_up(f);
					
					messenger.send(std::to_string(index));
				}
				
				// The opponent awaits the player's choice.
				else {
					// The opponent is notifed that the player is choosing a fighter.
					display.fill();
					display.blit(
						renderer.lined_render(
							display,
							RANK_UP_STRING,
							RANK_UP_WIDTH,
							RANK_UP_HEIGHT,
							RANK_UP_SEPARATION_X,
							RANK_UP_MAX_WIDTH,
							RANK_UP_SEPARATION_Y,
							RANK_UP_JUSTIFICATION
						),
						RANK_UP_X,
						RANK_UP_Y
					);
					display.update();
					
					while (message == EMPTY_MESSAGE) {
						Events::update();
					}
					
					// The attachment indexed is received.
					index = std::stoi(message);
					
					// The message from the opponent is awaited.
					message = EMPTY_MESSAGE;
					messenger_thread.new_thread(
						MessengerPackage::get_message,
						&messenger_package
					);
				}
			}
			
			Fighter old_rank(fighters[index]);
			fighters[index] = f;
			old_rank.rank_up(fighters[index]);
			trash.store(old_rank);
			
			announce(RANK_UP_ANNOUNCEMENT);
		}
		
		/**
		 * Allows the player to play a supporter card.
		 */
		void play(Supporter& s) noexcept {
			// The effects are extracted.
			const std::vector<std::vector<std::string>>& effects = s.get_effects();
			
			// The results of the last set of coin flips.
			std::vector<bool> coin_flips;
			std::array<int, 2> flip_counts;
			
			// The supporter card being played is announced.
			announce(SUPPORTER_ANNOUNCEMENT);
			
			// The effects are resolved.
			for (int i = 0; i < effects.size(); ++i) {
				// The supporter card allows the player to draw.
				if (effects[i][0] == DRAW_EFFECT) {
					int draws = std::stoi(effects[i][1]);
					
					// The number of card draws cannot exceed
					//   the number of cards in the deck.
					if (draws > deck.size()) {
						draws = deck.size();
					}
					
					// The opponent only sees the number of draws.
					if (opposing) {
						draw(draws);
						announce(DRAW_ANNOUNCEMENT);
					}
					
					// The player sees what was drawn.
					else {
						for (int j = 0; j < draws; ++j) {
							draw(1);
							announce(LAST_DRAWN_ANNOUNCEMENT);
						}
						
						announce(DRAW_ANNOUNCEMENT);
					}
				}
				
				// The supporter card discards cards.
				else if (effects[i][0] == DISCARD_EFFECT) {
					// Discards all of the cards in the hand.
					if (effects[i][1] == UNIVERSAL_EFFECT) {
						discard();
						announce(DISCARD_ALL_ANNOUNCEMENT);
					}
				
					// Discards a number of chosen cards from the hand.
					else {
						int discards = std::stoi(effects[i][1]);
						
						if (discards > hand.size()) {
							discards = hand.size();
						}
						
						// The player chooses cards to discard.
						for (int i = 0; i < discards; ++i) {
							int index;
							
							if (!opposing) {
								announce(TO_DISCARD_ANNOUNCEMENT);
								
								index = hand.choose(
									display,
									renderer,
									back_button
								);
								
								messenger.send(std::to_string(index));
							}
							
							else {
								announce(TO_DISCARD_ANNOUNCEMENT, false);
								
								index = std::stoi(message);
								
								// A message is waited for in another thread.
								message = EMPTY_MESSAGE;
								messenger_thread.new_thread(
									MessengerPackage::get_message,
									&messenger_package
								);
							}
							
							if (opposing) {
								announce(DISCARD_PEEK_ANNOUNCEMENT);
							}
							
							trash.store(hand.remove(index));
						}
						
						announce(DISCARD_ANNOUNCEMENT);
					}
				}
				
				// The supporter card shuffles cards into the deck.
				else if (effects[i][0] == SHUFFLE_EFFECT) {
					// Shuffles all of the cards in the hand into the deck.
					if (effects[i][1] == UNIVERSAL_EFFECT) {
						shuffle();
						announce(SHUFFLE_ALL_ANNOUNCEMENT);
					}
					
					// Shuffles a number of chosen cards from the hand into the deck.
					else {
						int shuffles = std::stoi(effects[i][1]);
						
						if (shuffles > hand.size()) {
							shuffles = hand.size();
						}
						
						// The player chooses cards to shuffle into the deck.
						for (int i = 0; i < shuffles; ++i) {
							int index;
							
							if (!opposing) {
								announce(TO_SHUFFLE_ANNOUNCEMENT);
								
								index = hand.choose(
									display,
									renderer,
									back_button
								);
								
								messenger.send(std::to_string(index));
							}
							
							else {
								announce(TO_SHUFFLE_ANNOUNCEMENT, false);
								
								index = std::stoi(message);
								
								// A message is waited for in another thread.
								message = EMPTY_MESSAGE;
								messenger_thread.new_thread(
									MessengerPackage::get_message,
									&messenger_package
								);
							}
								
							deck.store(hand.remove(index));
						}
						
						announce(SHUFFLE_ANNOUNCEMENT);
					}
				}
			
				// The supporter card will draw cards at the turn's end.
				else if (effects[i][0] == END_DRAW_EFFECT) {
					affect(
						effects[i][0]
						+ EFFECT_SEPARATOR
						+ effects[i][1]
					);
					
					announce(END_DRAW_ANNOUNCEMENT);
				}
			
				// The supporter card flips coins.
				else if (effects[i][0] == FLIP_EFFECT) {
					// Preparation for the set of coin flips.
					int flips = std::stoi(effects[i][1]);
					coin_flips.clear();
					flip_counts.fill(0);
					
					for (int i = 0; i < flips; ++i) {
						bool result = coin_flip(generator);
						coin_flips.push_back(result);
						++flip_counts[result];
						announce(FLIP_ANNOUNCEMENT);
					}
					
					announce(FLIP_COUNT_ANNOUNCEMENT);
				}
				
				// Takes effect only if the first coin flip was heads.
				else if (
					effects[i][0] == HEADS_EFFECT
					&& coin_flips[0] == HEADS
				) {
					// The supporter card allows the player to draw.
					if (effects[i][1] == DRAW_EFFECT) {
						int draws = std::stoi(effects[i][2]);
						
						// The number of card draws cannot exceed
						//   the number of cards in the deck.
						if (draws > deck.size()) {
							draws = deck.size();
						}
						
						// The opponent only sees the number of draws.
						if (opposing) {
							draw(draws);
							announce(DRAW_ANNOUNCEMENT);
						}
						
						// The player sees what was drawn.
						else {
							for (int j = 0; j < draws; ++j) {
								draw(1);
								announce(LAST_DRAWN_ANNOUNCEMENT);
							}
						
							announce(DRAW_ANNOUNCEMENT);
						}
					}
				}
				
				// Takes effect only if the first coin flip was tails.
				else if (
					effects[i][0] == TAILS_EFFECT
					&& coin_flips[0] == TAILS
				) {
					// The supporter card allows the player to draw.
					if (effects[i][1] == DRAW_EFFECT) {
						int draws = std::stoi(effects[i][2]);
						
						// The number of card draws cannot exceed
						//   the number of cards in the deck.
						if (draws > deck.size()) {
							draws = deck.size();
						}
						
						// The opponent only sees the number of draws.
						if (opposing) {
							draw(draws);
							announce(DRAW_ANNOUNCEMENT);
						}
						
						// The player sees what was drawn.
						else {
							for (int j = 0; j < draws; ++j) {
								draw(1);
								announce(LAST_DRAWN_ANNOUNCEMENT);
							}
						
							announce(DRAW_ANNOUNCEMENT);
						}
					}
				}
			}
			
			// The supporter card is moved to the trash.
			trash.store(s);
		}
		
		/**
		 * Allows the player to attach an energy card to a fighter card.
		 */
		void play(Energy& e) noexcept {
			// A pointer to the fighter that the energy card will be attached to.
			Fighter* recipient = nullptr;
			
			// If the player has multiple fighters in play,
			//   they must select one to attach the energy to.
			if (fighters.size() > 1) {
				int index;
				
				// The player chooses the recipient of the energy.
				if (!opposing) {
					index = attach(e);
					
					messenger.send(std::to_string(index));
				}
				
				// The opponent awaits the player's choice.
				else {
					// The opponent is notifed that the player is choosing a fighter.
					display.fill();
					display.blit(
						renderer.lined_render(
							ATTACHMENT_STRING,
							ATTACHMENT_WIDTH * display.width(),
							ATTACHMENT_HEIGHT * display.height(),
							ATTACHMENT_SEPARATION_X * display.width(),
							ATTACHMENT_MAX_WIDTH * display.width(),
							ATTACHMENT_SEPARATION_Y * display.height(),
							ATTACHMENT_JUSTIFICATION
						),
						ATTACHMENT_X,
						ATTACHMENT_Y
					);
					display.update();
					
					while (message == EMPTY_MESSAGE) {
						Events::update();
					}
					
					// The attachment indexed is received.
					index = std::stoi(message);
					
					// The message from the opponent is awaited.
					message = EMPTY_MESSAGE;
					messenger_thread.new_thread(
						MessengerPackage::get_message,
						&messenger_package
					);
				}
				
				// The fighter at the index is chosen to be the recipient.
				recipient = &fighters[index];
			}
			
			// Else, the player only has a single fighter in
			//   play, so the energy is attached to that fighter.
			else {
				recipient = &fighters[0];
			}
			
			recipient->attach(e);
			
			announce(ATTACHMENT_ANNOUNCEMENT);
		}
		
		/**
		 * Allows the player to choose a fighter to attach energy to.
		 */
		int attach(const Energy& e) const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The attach buttons are initialised.
			std::vector<Button> attach_buttons;
			
			for (int i = 0; i < PAGE_COUNT; ++i) {
				attach_buttons.push_back(
					Button(
						renderer.render(
							ATTACH_STRING,
							ATTACH_WIDTH * display.width(),
							ATTACH_HEIGHT * display.height(),
							ATTACH_SEPARATION * display.width()
						),
						display,
						ATTACH_X,
						ATTACH_Y + i * ATTACH_Y_SHIFT
					)
				);
			}
	
			// The preview button is initialised.
			Button preview_button(
				renderer.render(
					display,
					ATTACH_PREVIEW_STRING,
					ATTACH_PREVIEW_WIDTH,
					ATTACH_PREVIEW_HEIGHT,
					ATTACH_PREVIEW_SEPARATION
				),
				display,
				ATTACH_PREVIEW_X,
				ATTACH_PREVIEW_Y
			);
	
			// Determines which cards are displayed.
			int page = 0;
			
			while (true) {
				// The sprites are blitted to the display.
				display.fill();
				preview_button.blit_to(display);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (fighters.size() - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < fighters.size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							Sprite(
								renderer.render(
									fighters[page * PAGE_COUNT + i].get_name(),
									PAGE_WIDTH * display.width(),
									PAGE_HEIGHT * display.height(),
									PAGE_SEPARATION * display.width()
								)
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The attach button is displayed.
					attach_buttons[i].blit_to(display);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The page number is decremented (if possible).
					if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (fighters.size() - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// Allows the player to preview the played card.
					else if (preview_button.get_rectangle().unclick()) {
						e.render(display, renderer);
						back_button.blit_to(display);
						display.update();
						
						while (
							!Events::unpress(NEXT_KEY)
							&& !Events::unpress(BACK_KEY)
							&& !back_button.get_rectangle().unclick()
						) {
							Events::update();
						}
						
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < fighters.size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								fighters[page * PAGE_COUNT + i].view(
									display,
									renderer,
									back_button
								);
								
								found = true;
								break;
							}
							
							// Chooses a fighter card to attach to.
							else if (attach_buttons[i].get_rectangle().unclick()) {
								return page * PAGE_COUNT + i;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Allows the player to choose a fighter to rank up.
		 */
		int rank_up(const Fighter& f) const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The rank buttons are initialised.
			std::vector<Button> rank_buttons;
			
			for (int i = 0; i < PAGE_COUNT; ++i) {
				rank_buttons.push_back(
					Button(
						renderer.render(
							RANK_STRING,
							RANK_WIDTH * display.width(),
							RANK_HEIGHT * display.height(),
							RANK_SEPARATION * display.width()
						),
						display,
						RANK_X,
						RANK_Y + i * RANK_Y_SHIFT
					)
				);
			}
	
			// The preview button is initialised.
			Button preview_button(
				renderer.render(
					display,
					RANK_PREVIEW_STRING,
					RANK_PREVIEW_WIDTH,
					RANK_PREVIEW_HEIGHT,
					RANK_PREVIEW_SEPARATION
				),
				display,
				RANK_PREVIEW_X,
				RANK_PREVIEW_Y
			);
	
			// Determines which cards are displayed.
			int page = 0;
			
			while (true) {
				// The sprites are blitted to the display.
				display.fill();
				preview_button.blit_to(display);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (fighters.size() - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < fighters.size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							Sprite(
								renderer.render(
									fighters[page * PAGE_COUNT + i].get_name(),
									PAGE_WIDTH * display.width(),
									PAGE_HEIGHT * display.height(),
									PAGE_SEPARATION * display.width()
								)
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The rank button is displayed.
					if (f.get_old_rank() == fighters[page * PAGE_COUNT + i].get_name()) {
						rank_buttons[i].blit_to(display);
					}
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The page number is decremented (if possible).
					if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (fighters.size() - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// Allows the player to preview the played card.
					else if (preview_button.get_rectangle().unclick()) {
						f.render(display, renderer);
						back_button.blit_to(display);
						display.update();
						
						while (
							!Events::unpress(NEXT_KEY)
							&& !Events::unpress(BACK_KEY)
							&& !back_button.get_rectangle().unclick()
						) {
							Events::update();
						}
						
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < fighters.size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								fighters[page * PAGE_COUNT + i].view(
									display,
									renderer,
									back_button
								);
								
								found = true;
								break;
							}
							
							// Chooses a fighter card to rank to.
							else if (
								f.get_old_rank() == fighters[page * PAGE_COUNT + i].get_name()
								&& rank_buttons[i].get_rectangle().unclick()
							) {
								return page * PAGE_COUNT + i;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Allows the player to use their active fighter.
		 */
		void use_active() noexcept {
			// The energy button is initialised.
			Button energy_button(
				renderer.render(
					FIGHTER_ENERGY_STRING,
					FIGHTER_ENERGY_WIDTH * display.width(),
					FIGHTER_ENERGY_HEIGHT * display.height(),
					FIGHTER_ENERGY_SEPARATION * display.width()
				),
				display,
				FIGHTER_ENERGY_X,
				FIGHTER_ENERGY_Y
			);
			
			// The effects button is initialised.
			Button effects_button(
				renderer.render(
					FIGHTER_EFFECTS_STRING,
					FIGHTER_EFFECTS_WIDTH * display.width(),
					FIGHTER_EFFECTS_HEIGHT * display.height(),
					FIGHTER_EFFECTS_SEPARATION * display.width()
				),
				display,
				FIGHTER_EFFECTS_X,
				FIGHTER_EFFECTS_Y
			);
			
			// The ability button is initialised.
			Button ability_button(
				renderer.render(
					FIGHTER_ABILITY_STRING,
					FIGHTER_ABILITY_WIDTH * display.width(),
					FIGHTER_ABILITY_HEIGHT * display.height(),
					FIGHTER_ABILITY_SEPARATION * display.width()
				),
				display,
				FIGHTER_ABILITY_X,
				FIGHTER_ABILITY_Y
			);
			
			// The attack button is initialised.
			Button attack_button(
				renderer.render(
					FIGHTER_ATTACK_STRING,
					FIGHTER_ATTACK_WIDTH * display.width(),
					FIGHTER_ATTACK_HEIGHT * display.height(),
					FIGHTER_ATTACK_SEPARATION * display.width()
				),
				display,
				FIGHTER_ATTACK_X,
				FIGHTER_ATTACK_Y
			);
			
			// The retreat button is initialised.
			Button retreat_button(
				renderer.render(
					FIGHTER_RETREAT_STRING,
					FIGHTER_RETREAT_WIDTH * display.width(),
					FIGHTER_RETREAT_HEIGHT * display.height(),
					FIGHTER_RETREAT_SEPARATION * display.width()
				),
				display,
				FIGHTER_RETREAT_X,
				FIGHTER_RETREAT_Y
			);
			
			// True when this function should return.
			bool end = false;
			
			while (!end) {
				// The display is rendered.
				fighters[0].render(display, renderer);
				back_button.blit_to(display);
				energy_button.blit_to(display);
				effects_button.blit_to(display);
				
				if (fighters[0].ability_usable()) {
					ability_button.blit_to(display);
				}
				
				if (
					!effect_search(PREPARATION_EFFECT)
					&& !attacked
					&& fighters[0].attack_usable()
				) {
					attack_button.blit_to(display);
				}
				
				if (
					fighters.size() > 1
					&& (!retreated || fighter_effect_search(FREEDOM_EFFECT))
					&& fighters[0].retreat_usable(
						fighter_effect_count(
							AGILITY_AURA_EFFECT
						)
					)
				) {
					retreat_button.blit_to(display);
				}
				
				display.update();
				
				while (true) {
					// The player can go back using the next or back buttons.
					// The opponent mking a move sends the player back, as well.
					if (
						Events::unpress(NEXT_KEY)
						|| Events::unpress(BACK_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The energy can be viewed by clicking the energy button.
					else if (energy_button.get_rectangle().unclick()) {
						fighters[0].view_energy(display, renderer, back_button, message);
						break;
					}
					
					// The effects can be viewed by clicking the effects button.
					else if (effects_button.get_rectangle().unclick()) {
						fighters[0].view_effects(display, renderer, back_button, message);
						break;
					}
					
					// The ability can be used by clicking the ability button.
					else if (
						fighters[0].ability_usable()
						&& ability_button.get_rectangle().unclick()
					) {
						use_ability(0);
						
						return;
					}
					
					// The fighter can retreat by clicking the retreat button.
					else if (
						(!retreated || fighter_effect_search(FREEDOM_EFFECT))
						&& fighters[0].retreat_usable(
							fighter_effect_count(
								AGILITY_AURA_EFFECT
							)
						)
						&& retreat_button.get_rectangle().unclick()
					) {
						retreat();
						
						return;
					}
					
					// The fighter can attack by clicking the retreat button.
					else if (
						!effect_search(PREPARATION_EFFECT)
						&& !attacked
						&& fighters[0].attack_usable()
						&& attack_button.get_rectangle().unclick()
					) {
						// The opponent is notified of the attack.
						messenger.send(ATTACK_MESSAGE);
						
						attack();
						
						return;
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Allows the player to use their benched fighters.
		 */
		void use_bench() noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The bench size sprite is intialised.
			Sprite bench_size_sprite(
				renderer.render(
					BENCH_SIZE_STRING,
					BENCH_SIZE_WIDTH * display.width(),
					BENCH_SIZE_HEIGHT * display.height(),
					BENCH_SIZE_SEPARATION * display.width()
				)
			);
			
			// The ability buttons are initialised.
			std::vector<Button> ability_buttons;
			
			for (int i = 0; i < PAGE_COUNT; ++i) {
				ability_buttons.push_back(
					Button(
						renderer.render(
							ABILITY_STRING,
							ABILITY_WIDTH * display.width(),
							ABILITY_HEIGHT * display.height(),
							ABILITY_SEPARATION * display.width()
						),
						display,
						ABILITY_X,
						ABILITY_Y + i * ABILITY_Y_SHIFT
					)
				);
			}
	
			// Determines which cards are displayed.
			int page = 0;
			
			// True if the function should return.
			bool end = false;
			
			while (!end) {
				// The sprites are blitted to the display.
				display.fill();
				back_button.blit_to(display);
				display.blit(bench_size_sprite, BENCH_SIZE_X, BENCH_SIZE_Y);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (fighters.size() - 2) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < fighters.size() - 1;
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							Sprite(
								renderer.render(
									fighters[BENCH_INDEX + page * PAGE_COUNT + i].get_name(),
									PAGE_WIDTH * display.width(),
									PAGE_HEIGHT * display.height(),
									PAGE_SEPARATION * display.width()
								)
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The ability button is displayed, if it is usable.
					if (fighters[BENCH_INDEX + page * PAGE_COUNT + i].ability_usable()) {
						ability_buttons[i].blit_to(display);
					}
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The user can return to the previous menu with
					//   the use of the back button or submit key.
					if (
						Events::unpress(SUBMIT_KEY)
						|| Events::unpress(QUIT_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The page number is decremented (if possible).
					else if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (fighters.size() - 2) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < fighters.size() - 1;
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								fighters[BENCH_INDEX + page * PAGE_COUNT + i].view(
									display,
									renderer,
									back_button,
									message
								);
								
								found = true;
								break;
							}
							
							// Uses a fighter's ability.
							else if (
								fighters[BENCH_INDEX + page * PAGE_COUNT + i].ability_usable()
								&& ability_buttons[i].get_rectangle().unclick()
							) {
								use_ability(BENCH_INDEX + page * PAGE_COUNT + i);
								
								return;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Allows the user to view the effects on the player.
		 */
		void view_effects() const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The vectors of effects and values are inItialised.
			std::vector<std::string> effect_names;
			std::vector<std::string> effect_values;
			
			// A pointer to a single effect.
			const std::vector<std::string>* effect = nullptr;
			
			for (int i = 0; i < EXPLANATION_COUNT; ++i) {
				if (EFFECT_CONDITIONS(i)) {
					effect_names.push_back(EFFECT_REPRESENTATIONS[i]);
					effect_values.push_back(EFFECT_VALUES(i));
				}
			}
			
			for (int i = 0; i < PLAYER_EXPLANATION_COUNT; ++i) {
				if (PLAYER_EFFECT_CONDITIONS(i)) {
					effect_names.push_back(PLAYER_EFFECT_REPRESENTATIONS[i]);
					effect_values.push_back(PLAYER_EFFECT_VALUES(i));
				}
			}
			
			// Determines which effects are displayed.
			int page = 0;
			
			// True if the function should return.
			bool end = false;
			
			while (!end) {
				// The sprites are blitted to the display.
				display.fill();
				back_button.blit_to(display);
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (static_cast<int>(effect_names.size()) - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < effect_names.size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							renderer.render(
								effect_names[page * PAGE_COUNT + i],
								PAGE_WIDTH * display.width(),
								PAGE_HEIGHT * display.height(),
								PAGE_SEPARATION * display.width()
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The value of the effect is displayed.
					display.blit(
						renderer.render(
							display,
							EFFECT_VALUE_STRING,
							EFFECT_VALUE_WIDTH,
							EFFECT_VALUE_HEIGHT,
							EFFECT_VALUE_SEPARATION
						),
						EFFECT_VALUE_X,
						EFFECT_VALUE_Y + i * EFFECT_VALUE_Y_SHIFT
					);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The user can return to the previous menu with
					//   the use of the back button or submit key.
					if (
						Events::unpress(SUBMIT_KEY)
						|| Events::unpress(QUIT_KEY)
						|| back_button.get_rectangle().unclick()
						|| message != EMPTY_MESSAGE
					) {
						end = true;
						break;
					}
					
					// The page number is decremented (if possible).
					else if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (static_cast<int>(effect_names.size()) - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < effect_names.size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								explain(
									display,
									renderer,
									back_button,
									message,
									effect_names[page * PAGE_COUNT + i],
									effect_values[page * PAGE_COUNT + i]
								);
								
								found = true;
								break;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Displays the announcement passed.
		 * The function returns if the user chooses to advance or
		 *   the passed string is no longer equal to EMPTY_MESSAGE.
		 */
		void announce(const std::string& announcement, bool skippable = true) noexcept {
			display.fill();
			display.blit(
				renderer.lined_render(
					ANNOUNCEMENT_STRING,
					ANNOUNCEMENT_WIDTH * display.width(),
					ANNOUNCEMENT_HEIGHT * display.height(),
					ANNOUNCEMENT_SEPARATION_X * display.width(),
					ANNOUNCEMENT_MAX_WIDTH * display.width(),
					ANNOUNCEMENT_SEPARATION_Y * display.height(),
					ANNOUNCEMENT_JUSTIFICATION
				),
				ANNOUNCEMENT_X,
				ANNOUNCEMENT_Y
			);
			
			if (skippable) {
				next_button.blit_to(display);
			}
			
			display.update();
			
			// The player proceeds at their own discretion
			//   or if the opponent took an action.
			if (skippable) {
				while (
					!Events::unpress(BACK_KEY)
					&& !Events::unpress(NEXT_KEY)
					&& !next_button.get_rectangle().unclick()
					&& message == EMPTY_MESSAGE
				) {
					Events::update();
				}
			}
			
			// The player proceeds when the opponent takes an action.
			else {
				while (message == EMPTY_MESSAGE) {
					Events::update();
				}
			}
		}
		
		/**
		 * Resets the player's attack, retreat, and ability uses.
		 * Performs other simple end of turn effects on the player.
		 */
		void reset() noexcept {
			attacked = false;
			retreated = false;
			depower();
			prepare();
			end_draw();
			
			// Agility is only reset at the end of the player's own turn.
			if (!turn) {
				reset_agility();
			}
			
			for (int i = 0; i < fighters.size(); i++) {
				fighters[i].reset_ability();
			}
		}
		
		/**
		 * Returns true if any of the player's fighters
		 *   can rank up into the given fighter.
		 */
		bool rank_search(const Fighter& f) const noexcept {
			for (int i = 0; i < fighters.size(); ++i) {
				if (fighters[i].get_name() == f.get_old_rank()) {
					return true;
				}
			}
			
			return false;
		}
		
		/**
		 * Uses a fighter's ability.
		 */
		void use_ability(int index = -1) noexcept {
			// The opponent receives the index.
			if (index < 0) {
				opposing = true;
				
				while (message == EMPTY_MESSAGE) {
					Events::update();
				}
				
				// The index of the fighter is extracted.
				index = std::stoi(message);
				
				// The message from the opponent is awaited.
				message = EMPTY_MESSAGE;
				messenger_thread.new_thread(
					MessengerPackage::get_message,
					&messenger_package
				);
			}
			
			// The player notifies the opponent of the ability use.
			else {
				opposing = false;
				
				messenger.send(ABILITY_MESSAGE);
				messenger.send(std::to_string(index));
			}
			
			// A copy of the ability is extracted.
			Ability ability(
				fighters[index].get_ability()
			);
			
			// The effects are extracted.
			const std::vector<std::vector<std::string>>& effects = ability.get_effects();
			
			// The ability use is announced.
			announce(ABILITY_ANNOUNCEMENT);
			
			// The ability's effects are resolved.
			for (int i = 0; i < effects.size(); ++i) {
				// The fighter switches in if it was on the bench.
				if (effects[i][0] == SWITCH_IN_EFFECT) {
					// Switching in can only work from the bench.
					if (index) {
						switch_in(index);
						
						// The switch in is announced.
						announce(SWITCH_IN_ANNOUNCEMENT);
						
						// The fighter is now in the active position.
						index = 0;
						
						// If switching in also boosts power, the fighter is empowered.
						if (
							effects[i].size() > 1
							&& effects[i][1] == POWER_EFFECT
						) {
							fighters[index].affect(
								effects[i][1]
								+ EFFECT_SEPARATOR
								+ effects[i][2]
							);
							std::string power(effects[i][2]);
							announce(POWER_ANNOUNCEMENT);
						}
					}
				}
				
				// The ability allows the player to draw.
				else if (effects[i][0] == DRAW_EFFECT) {
					int draws = std::stoi(effects[i][1]);
					
					// The number of card draws cannot exceed
					//   the number of cards in the deck.
					if (draws > deck.size()) {
						draws = deck.size();
					}
					
					// The opponent only sees the number of draws.
					if (opposing) {
						draw(draws);
						announce(DRAW_ANNOUNCEMENT);
					}
					
					// The player sees what was drawn.
					else {
						for (int j = 0; j < draws; ++j) {
							draw(1);
							announce(LAST_DRAWN_ANNOUNCEMENT);
						}
						
						announce(DRAW_ANNOUNCEMENT);
					}
				}
				
				// The ability allows the player to search for cards in their deck.
				else if (effects[i][0] == SEARCH_EFFECT) {
					int searches = std::stoi(effects[i][1]);
					
					// The number of searches can't exceed the number of cards in the deck.
					if (searches > deck.size()) {
						searches = deck.size();
					}
					
					// The player chooses cards to search for.
					for (int i = 0; i < searches; ++i) {
						int index;
						
						if (!opposing) {
							announce(TO_SEARCH_ANNOUNCEMENT);
							
							index = deck.choose(
								display,
								renderer,
								back_button
							);
							
							messenger.send(std::to_string(index));
						}
						
						else {
							announce(TO_SEARCH_ANNOUNCEMENT, false);
							
							index = std::stoi(message);
							
							// A message is waited for in another thread.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
						}
						
						hand.store(deck.remove(index));
					}
					
					announce(SEARCH_ANNOUNCEMENT);
				}
			
				// The ability discards random cards from the deck.
				else if (effects[i][0] == MILL_EFFECT) {
					// The number of cards to mill are extracted.
					int mills = std::stoi(effects[i][1]);
					
					// The player can't discard more cards than they have in their deck.
					if (mills > deck.size()) {
						mills = deck.size();
					}
					
					// The cards are discarded and displayed.
					for (int i = 0; i < mills; ++i) {
						last_drawn = deck.draw(generator);
						trash.store(last_drawn);
						announce(MILL_PEEK_ANNOUNCEMENT);
					}
					
					// The total number of cards discarded is displayed.
					announce(MILL_ANNOUNCEMENT);
				}
				
				// The ability heals the fighter.
				else if (effects[i][0] == HEAL_EFFECT) {
					// The amount to heal is extracted.
					int heal = std::stoi(effects[i][1]);
					fighters[index].heal(heal);
					announce(HEAL_ANNOUNCEMENT);
				}
			}
		
			// The ability uses are incremented.
			fighters[index].use_ability();
		}
		
		/**
		 * Switches a fighter into the active position from the bench.
		 * The active fighter is switched out to the bench.
		 * The benched fighter has its effect cleared.
		 */
		void switch_in(int index) noexcept {
			Fighter temporary(fighters[index]);
			fighters[index] = fighters[0];
			fighters[0] = temporary;
			fighters[index].clear_effects();
		}
		
		/**
		 * Removes all power effects from this player and their fighters.
		 */
		void depower() noexcept {
			unaffect(POWER_EFFECT);
			
			for (int i = 0; i < fighters.size(); ++i) {
				fighters[i].unaffect(POWER_EFFECT);
			}
		}
		
		/**
		 * Chooses a fighter on the bench to switch in.
		 */
		void retreat(int index = -1) noexcept {
			// The player chooses the fighter that should retreat.
			if (index < 0) {
				// The left button is initialised.
				Button left_button(
					Sprite(
						LEFT_SOURCE,
						LEFT_WIDTH * display.width(),
						LEFT_HEIGHT * display.height()
					),
					display,
					LEFT_X,
					LEFT_Y
				);
				
				// The right button is initialised.
				Button right_button(
					Sprite(
						RIGHT_SOURCE,
						RIGHT_WIDTH * display.width(),
						RIGHT_HEIGHT * display.height()
					),
					display,
					RIGHT_X,
					RIGHT_Y
				);
				
				// The preview button is initialised.
				Button preview_button(
					renderer.render(
						display,
						RETREAT_PREVIEW_STRING,
						RETREAT_PREVIEW_WIDTH,
						RETREAT_PREVIEW_HEIGHT,
						RETREAT_PREVIEW_SEPARATION
					),
					display,
					RETREAT_PREVIEW_X,
					RETREAT_PREVIEW_Y
				);
		
				// The switch_in buttons are initialised.
				std::vector<Button> switch_in_buttons;
				
				for (int i = 0; i < PAGE_COUNT; ++i) {
					switch_in_buttons.push_back(
						Button(
							renderer.render(
								SWITCH_IN_STRING,
								SWITCH_IN_WIDTH * display.width(),
								SWITCH_IN_HEIGHT * display.height(),
								SWITCH_IN_SEPARATION * display.width()
							),
							display,
							SWITCH_IN_X,
							SWITCH_IN_Y + i * SWITCH_IN_Y_SHIFT
						)
					);
				}
		
				// Determines which cards are displayed.
				int page = 0;
				
				// True when the fighter to switch in has been chosen.
				bool end = false;
				
				while (!end) {
					// The sprites are blitted to the display.
					display.fill();
					preview_button.blit_to(display);
					
					// The previous page button is displayed, when relevant.
					if (page > 0) {
						left_button.blit_to(display);
					}
					
					// The next page button is displayed, when relevant.
					if (page < (fighters.size() - 2) / PAGE_COUNT) {
						right_button.blit_to(display);
					}
					
					// A vector of buttons for the names is generated.
					std::vector<Button> name_buttons;
					
					// The cards' names on the page are displayed.
					for (
						int i = 0;
						i < PAGE_COUNT
						&& page * PAGE_COUNT + i < fighters.size() - 1;
						++i
					) {
						// The name button is stored in the vector.
						name_buttons.push_back(
							Button(
								Sprite(
									renderer.render(
										fighters[BENCH_INDEX + page * PAGE_COUNT + i].get_name(),
										PAGE_WIDTH * display.width(),
										PAGE_HEIGHT * display.height(),
										PAGE_SEPARATION * display.width()
									)
								),
								display,
								PAGE_NAME_X,
								PAGE_Y + i * PAGE_Y_SHIFT
							)
						);
						
						// The name is displayed.
						name_buttons[i].blit_to(display);
						
						// The switch_in button is displayed, if it is usable.
						switch_in_buttons[i].blit_to(display);
					}
					
					// The display is updated.
					display.update();
					
					// Loop to get user input.
					while (true) {
						// The user can return to the previous menu with
						//   the use of the back button or submit key.
						if (preview_button.get_rectangle().unclick()) {
							fighters[0].view(
								display,
								renderer,
								back_button,
								message
							);
						}
						
						// The page number is decremented (if possible).
						else if (
							(
								Events::unpress(Events::LEFT)
								|| left_button.get_rectangle().unclick()
							) && page > 0
						) {
							--page;
							break;
						}
						
						// The page number is incremented (if possible).
						else if (
							(
								Events::unpress(Events::RIGHT)
								|| right_button.get_rectangle().unclick()
							) && page < (fighters.size() - 2) / PAGE_COUNT
						) {
							++page;
							break;
						}
						
						// The other buttons are checked.
						else {
							// True if the button being clicked was found.
							bool found = false;
							
							// The plus and minus buttons increment or decrement
							//   the number of copies of a card in the deck.
							// The names display the card's details.
							for (
								int i = 0;
								i < PAGE_COUNT
								&& page * PAGE_COUNT + i < fighters.size() - 1;
								++i
							) {
								// Diplays a card's details.
								if (name_buttons[i].get_rectangle().unclick()) {
									fighters[BENCH_INDEX + page * PAGE_COUNT + i].view(
										display,
										renderer,
										back_button,
										message
									);
									
									found = true;
									break;
								}
								
								// Switches in the benched fighter.
								else if (switch_in_buttons[i].get_rectangle().unclick()) {
									index = BENCH_INDEX + page * PAGE_COUNT + i;
									end = true;
									found = true;
									break;
								}
							}
							
							if (found) {
								break;
							}
						}
						
						// The events are updated.
						Events::update();
					}
				}
			
				messenger.send(RETREAT_MESSAGE);
				messenger.send(std::to_string(index));
			}
			
			announce(RETREAT_ANNOUNCEMENT);
			
			switch_in(index);
			
			announce(SWITCH_IN_ANNOUNCEMENT);
			
			retreated = true;
		}
		
		/**
		 * Performs the active's fighter's attack.
		 */
		void attack() noexcept {
			// A copy of the attack is extracted.
			Attack attack(fighters[0].get_attack());
			
			// The effects are extracted.
			const std::vector<std::vector<std::string>>& effects = attack.get_effects();
			
			// The power boost is calculated.
			int power =
				effect_count(POWER_EFFECT)
				+ fighters[0].effect_count(POWER_EFFECT)
			;
			
			announce(ATTACK_ANNOUNCEMENT);
			
			// The damage boost from the attack's effects.
			int boost = 0;
			
			// The attack's effects are resolved.
			for (int i = 0; i < effects.size(); ++i) {
				// The attack can damage any opposing fighter.
				if (effects[i][0] == SNIPE_EFFECT) {
					int index;
					
					// The player chooses a fighter to deal damage to.
					if (!opposing) {
						announce(TO_SNIPE_ANNOUNCEMENT);
						index = opponent->choose_fighter();
						messenger.send(std::to_string(index));
					}
					
					// The opponent waits for the player to choose.
					else {
						// The snipe choice is waited for.
						announce(TO_SNIPE_ANNOUNCEMENT, false);
						index = std::stoi(message);
						
						// A message is waited for in another thread.
						message = EMPTY_MESSAGE;
						messenger_thread.new_thread(
							MessengerPackage::get_message,
							&messenger_package
						);
					}
					
					int snipe = std::stoi(effects[i][1]) + power + boost;
					
					// The snipe has additional effects.
					if (effects[i].size() > 1) {
						// The snipe's damage can be modified.
						if (effects[i][2] == POWER_EFFECT) {
							// The snipe's damage is affected by the target's element.
							if (
								effects[i][3]
								== opponent->fighters[index].get_element()
							) {
								snipe += std::stoi(effects[i][4]);
							}
						}
					}
					
					opponent->fighters[index].damage(snipe);
					
					announce(SNIPE_ANNOUNCEMENT);
				}
				
				// The attack's damage can be increased.
				else if (effects[i][0] == POWER_EFFECT) {
					// The damage is boosted by the number of cards in the trash.
					if (effects[i][1] == TRASH_EFFECT) {
						boost += trash.size() * std::stoi(effects[i][2]);
					}
				}

				// The target's retreat cost is changed for a turn.
				else if (effects[i][0] == AGILITY_EFFECT) {
					opponent->fighters[0].affect(
						effects[i][0]
						+ EFFECT_SEPARATOR
						+ effects[i][1]
					);
					std::string agility(effects[i][1]);
					announce(AGILITY_ANNOUNCEMENT);
				}
			}
			
			// The damage is caculated.
			int damage = attack.get_damage() + boost;
			
			// Damage is only boosted by power if it was non-zero.
			if (damage) {
				damage += power;
			}
			
			// The opponent's active fighter is damaged.
			opponent->fighters[0].damage(damage);
			
			// The attack's damage is announced.
			if (damage) {
				announce(DAMAGE_ANNOUNCEMENT);
			}
		
			attacked = true;
		}
		
		/**
		 * Checks for defeated fighters.
		 */
		void defeat_check() noexcept {
			// The number of life cards to be drawn.
			int life_draws = 0;
			
			// Defeated benched fighters and their energy are discarded.
			for (int i = fighters.size() - 1; i >= 0; --i) {
				// The fighter was defeated.
				if (fighters[i].get_health() <= 0) {
					// The defeat is announced.
					announce(DEFEAT_ANNOUNCEMENT);
					
					// The energy attached to the fighter is discarded.
					for (int j = 0; j < fighters[i].get_energy().size(); ++j) {
						trash.store(fighters[i].get_energy()[j]);
					}
					
					// Non-active fighters are dealt with.
					if (i > 0) {
						// The fighter is reset and discarded.
						fighters[i].reset();
						trash.store(fighters[i]);
					
						// Benched fighters are removed immediately.
						fighters.erase(fighters.cbegin() + i);
					}
					
					// The number of life cards to be drawn is incremented.
					++life_draws;
				}
			}
			
			// True if the player has reached a loss condition.
			bool defeated = false;
			
			// If the player draws all of their life cards, they lose.
			if (life_draws >= life_cards.size()) {
				// Set for the announcement.
				life_draws = life_cards.size();
				
				// All of the life cards are drawn.
				while (life_cards.size()) {
					hand.store(*life_cards.remove());
				}
				
				announce(NO_LIFE_ANNOUNCEMENT);
				
				// The player is defeated.
				defeated = true;
			}
			
			// The active fighter was defeated.
			if (fighters[0].get_health() <= 0) {
				// If all of the player's fighters are defeated, they lose.
				if (fighters.size() == 1) {
					announce(NO_FIGHTERS_ANNOUNCEMENT);
					
					// The player is defeated.
					defeated = true;
				}
				
				// Else, a new active fighter must be chosen (if not yet defeated).
				else if (!defeated) {
					// The player chooses a new active fighter.
					if (!opposing) {
						announce(NEW_ACTIVE_ANNOUNCEMENT);
						
						new_active();
					}
					
					// The new active fighter is awaited.
					else {
						announce(NEW_ACTIVE_ANNOUNCEMENT, false);
						
						int index = std::stoi(message);
						
						// The message from the opponent is awaited.
						message = EMPTY_MESSAGE;
						messenger_thread.new_thread(
							MessengerPackage::get_message,
							&messenger_package
						);
						
						new_active(index);
					}
				}
			}
			
			// The opponent sees the number of life cards drawn.
			if (opposing && life_draws) {
				announce(LIFE_DRAW_ANNOUNCEMENT, false);
			}
			
			// If the player was not defeated, they draw life cards
			//   for each of their fighters that were defeated.
			if (!defeated) {
				for (int i = 0; i < life_draws; ++i) {
					// If this is the player, they choose the life cards to draw.
					if (!opposing) {
						// Informs the player that they should draw a life card.
						announce(DRAW_LIFE_ANNOUNCEMENT);
						
						// The index of the life card to be drawn is chosen.
						int index = life_cards.choose(
							display,
							renderer,
							back_button
						);
						
						messenger.send(std::to_string(index));
						hand.store(*life_cards.remove(index));
					}
					
					// Else, the choice of life cards is waited for.
					else {
						while (message == EMPTY_MESSAGE) {
							Events::update();
						}
						
						hand.store(*life_cards.remove(std::stoi(message)));
						
						// The message from the opponent is awaited.
						message = EMPTY_MESSAGE;
						messenger_thread.new_thread(
							MessengerPackage::get_message,
							&messenger_package
						);
					}
				}
			}
		}
		
		/**
		 * Returns the number of loss conditions for this fighter.
		 */
		int loss_conditions() const noexcept {
			int conditions = 0;
			
			if (fighters.size() == 1 && fighters[0].get_health() <= 0) {
				++conditions;
			}
			
			if (!life_cards.size()) {
				++conditions;
			}
			
			return conditions;
		}
		
		/**
		 * Chooses a fighter on the bench to replace the active fighter.
		 */
		void new_active(int index = -1) noexcept {
			// The player chooses the fighter that should retreat.
			if (index < 0) {
				// The left button is initialised.
				Button left_button(
					Sprite(
						LEFT_SOURCE,
						LEFT_WIDTH * display.width(),
						LEFT_HEIGHT * display.height()
					),
					display,
					LEFT_X,
					LEFT_Y
				);
				
				// The right button is initialised.
				Button right_button(
					Sprite(
						RIGHT_SOURCE,
						RIGHT_WIDTH * display.width(),
						RIGHT_HEIGHT * display.height()
					),
					display,
					RIGHT_X,
					RIGHT_Y
				);
				
				// The preview button is initialised.
				Button preview_button(
					renderer.render(
						display,
						RETREAT_PREVIEW_STRING,
						RETREAT_PREVIEW_WIDTH,
						RETREAT_PREVIEW_HEIGHT,
						RETREAT_PREVIEW_SEPARATION
					),
					display,
					RETREAT_PREVIEW_X,
					RETREAT_PREVIEW_Y
				);
		
				// The switch_in buttons are initialised.
				std::vector<Button> switch_in_buttons;
				
				for (int i = 0; i < PAGE_COUNT; ++i) {
					switch_in_buttons.push_back(
						Button(
							renderer.render(
								SWITCH_IN_STRING,
								SWITCH_IN_WIDTH * display.width(),
								SWITCH_IN_HEIGHT * display.height(),
								SWITCH_IN_SEPARATION * display.width()
							),
							display,
							SWITCH_IN_X,
							SWITCH_IN_Y + i * SWITCH_IN_Y_SHIFT
						)
					);
				}
		
				// Determines which cards are displayed.
				int page = 0;
				
				// True when the fighter to switch in has been chosen.
				bool end = false;
				
				while (!end) {
					// The sprites are blitted to the display.
					display.fill();
					preview_button.blit_to(display);
					
					// The previous page button is displayed, when relevant.
					if (page > 0) {
						left_button.blit_to(display);
					}
					
					// The next page button is displayed, when relevant.
					if (page < (fighters.size() - 2) / PAGE_COUNT) {
						right_button.blit_to(display);
					}
					
					// A vector of buttons for the names is generated.
					std::vector<Button> name_buttons;
					
					// The cards' names on the page are displayed.
					for (
						int i = 0;
						i < PAGE_COUNT
						&& page * PAGE_COUNT + i < fighters.size() - 1;
						++i
					) {
						// The name button is stored in the vector.
						name_buttons.push_back(
							Button(
								Sprite(
									renderer.render(
										fighters[BENCH_INDEX + page * PAGE_COUNT + i].get_name(),
										PAGE_WIDTH * display.width(),
										PAGE_HEIGHT * display.height(),
										PAGE_SEPARATION * display.width()
									)
								),
								display,
								PAGE_NAME_X,
								PAGE_Y + i * PAGE_Y_SHIFT
							)
						);
						
						// The name is displayed.
						name_buttons[i].blit_to(display);
						
						// The switch_in button is displayed, if it is usable.
						switch_in_buttons[i].blit_to(display);
					}
					
					// The display is updated.
					display.update();
					
					// Loop to get user input.
					while (true) {
						// The user can return to the previous menu with
						//   the use of the back button or submit key.
						if (preview_button.get_rectangle().unclick()) {
							fighters[0].view(
								display,
								renderer,
								back_button,
								message
							);
						}
						
						// The page number is decremented (if possible).
						else if (
							(
								Events::unpress(Events::LEFT)
								|| left_button.get_rectangle().unclick()
							) && page > 0
						) {
							--page;
							break;
						}
						
						// The page number is incremented (if possible).
						else if (
							(
								Events::unpress(Events::RIGHT)
								|| right_button.get_rectangle().unclick()
							) && page < (fighters.size() - 2) / PAGE_COUNT
						) {
							++page;
							break;
						}
						
						// The other buttons are checked.
						else {
							// True if the button being clicked was found.
							bool found = false;
							
							// The plus and minus buttons increment or decrement
							//   the number of copies of a card in the deck.
							// The names display the card's details.
							for (
								int i = 0;
								i < PAGE_COUNT
								&& page * PAGE_COUNT + i < fighters.size() - 1;
								++i
							) {
								// Diplays a card's details.
								if (name_buttons[i].get_rectangle().unclick()) {
									fighters[BENCH_INDEX + page * PAGE_COUNT + i].view(
										display,
										renderer,
										back_button,
										message
									);
									
									found = true;
									break;
								}
								
								// Switches in the benched fighter.
								else if (switch_in_buttons[i].get_rectangle().unclick()) {
									index = BENCH_INDEX + page * PAGE_COUNT + i;
									end = true;
									found = true;
									break;
								}
							}
							
							if (found) {
								break;
							}
						}
						
						// The events are updated.
						Events::update();
					}
				}
			
				messenger.send(std::to_string(index));
			}
			
			// The active fighter is reset and discarded.
			fighters[0].reset();
			trash.store(fighters[0]);
			
			// The benched fighter replaces the active fighter.
			fighters[0] = fighters[index];
		
			// The original benched fighter is removed from the vector.
			fighters.erase(fighters.cbegin() + index);
			
			// The replacement is announced.
			announce(REPLACEMENT_ANNOUNCEMENT);
		}
		
		/**
		 * Randomly returns 0 or 1.
		 */
		static bool coin_flip(std::mt19937& generator) noexcept {
			return std::uniform_int_distribution<>(0, 1)(generator);
		}

		/**
		 * Removes the preparation effect from this fighter.
		 */
		void prepare() noexcept {
			unaffect(PREPARATION_EFFECT);
		}

		/**
		 * Allows player to draw cards at the end of their turn.
		 * This member function also removes the effect from the player.
		 */
		void end_draw() noexcept {
			int draws = effect_count(END_DRAW_EFFECT);
			
			if (draws) {
				// The number of card draws cannot exceed
				//   the number of cards in the deck.
				if (draws > deck.size()) {
					draws = deck.size();
				}
				
				// The opponent only sees the number of draws.
				if (opposing) {
					draw(draws);
					announce(DRAW_ANNOUNCEMENT);
				}
				
				// The player sees what was drawn.
				else {
					for (int j = 0; j < draws; ++j) {
						draw(1);
						announce(LAST_DRAWN_ANNOUNCEMENT);
					}
						
					announce(DRAW_ANNOUNCEMENT);
				}
			}
			
			unaffect(END_DRAW_EFFECT);
		}

		/**
		 * Chooses a fighter and returns its index.
		 */
		int choose_fighter() const noexcept {
			// The left button is initialised.
			Button left_button(
				Sprite(
					LEFT_SOURCE,
					LEFT_WIDTH * display.width(),
					LEFT_HEIGHT * display.height()
				),
				display,
				LEFT_X,
				LEFT_Y
			);
			
			// The right button is initialised.
			Button right_button(
				Sprite(
					RIGHT_SOURCE,
					RIGHT_WIDTH * display.width(),
					RIGHT_HEIGHT * display.height()
				),
				display,
				RIGHT_X,
				RIGHT_Y
			);
			
			// The choice buttons are initialised.
			std::vector<Button> choice_buttons;
			
			for (int i = 0; i < PAGE_COUNT; ++i) {
				choice_buttons.push_back(
					Button(
						renderer.render(
							CHOICE_STRING,
							CHOICE_WIDTH * display.width(),
							CHOICE_HEIGHT * display.height(),
							CHOICE_SEPARATION * display.width()
						),
						display,
						CHOICE_X,
						CHOICE_Y + i * CHOICE_Y_SHIFT
					)
				);
			}
	
			// Determines which cards are displayed.
			int page = 0;
			
			while (true) {
				// The sprites are blitted to the display.
				display.fill();
				
				if (page > 0) {
					left_button.blit_to(display);
				}
				
				if (page < (fighters.size() - 1) / PAGE_COUNT) {
					right_button.blit_to(display);
				}
				
				// A vector of buttons for the names is generated.
				std::vector<Button> name_buttons;
				
				// The cards' names on the page are displayed.
				for (
					int i = 0;
					i < PAGE_COUNT
					&& page * PAGE_COUNT + i < fighters.size();
					++i
				) {
					// The name button is stored in the vector.
					name_buttons.push_back(
						Button(
							Sprite(
								renderer.render(
									fighters[page * PAGE_COUNT + i].get_name(),
									PAGE_WIDTH * display.width(),
									PAGE_HEIGHT * display.height(),
									PAGE_SEPARATION * display.width()
								)
							),
							display,
							PAGE_NAME_X,
							PAGE_Y + i * PAGE_Y_SHIFT
						)
					);
					
					// The name is displayed.
					name_buttons[i].blit_to(display);
					
					// The choice button is displayed.
					choice_buttons[i].blit_to(display);
				}
				
				// The display is updated.
				display.update();
				
				// Loop to get user input.
				while (true) {
					// The page number is decremented (if possible).
					if (
						(
							Events::unpress(Events::LEFT)
							|| left_button.get_rectangle().unclick()
						) && page > 0
					) {
						--page;
						break;
					}
					
					// The page number is incremented (if possible).
					else if (
						(
							Events::unpress(Events::RIGHT)
							|| right_button.get_rectangle().unclick()
						) && page < (fighters.size() - 1) / PAGE_COUNT
					) {
						++page;
						break;
					}
					
					// The other buttons are checked.
					else {
						// True if the button being clicked was found.
						bool found = false;
						
						// The plus and minus buttons increment or decrement
						//   the number of copies of a card in the deck.
						// The names display the card's details.
						for (
							int i = 0;
							i < PAGE_COUNT
							&& page * PAGE_COUNT + i < fighters.size();
							++i
						) {
							// Diplays a card's details.
							if (name_buttons[i].get_rectangle().unclick()) {
								fighters[page * PAGE_COUNT + i].view(
									display,
									renderer,
									back_button
								);
								
								found = true;
								break;
							}
							
							// Chooses a fighter card to choice to.
							else if (choice_buttons[i].get_rectangle().unclick()) {
								return page * PAGE_COUNT + i;
							}
						}
						
						if (found) {
							break;
						}
					}
					
					// The events are updated.
					Events::update();
				}
			}
		}
		
		/**
		 * Resets the agility of the player's fighters.
		 */
		void reset_agility() noexcept {
			for (int i = 0; i < fighters.size(); ++i) {
				fighters[i].unaffect(AGILITY_EFFECT);
			}
		}

		/**
		 * Returns the total effect of all of the player's fighter.
		 */
		int fighter_effect_count(const std::string& effect) const noexcept {
			int count = 0;
			
			for (int i = 0; i < fighters.size(); ++i) {
				count += fighters[i].effect_count(effect);
			}
			
			return count;
		}
		
		/**
		 * Returns true if one of the player's fighters has the given effect.
		 */
		bool fighter_effect_search(const std::string& effect) const noexcept {
			for (int i = 0; i < fighters.size(); ++i) {
				if (fighters[i].effect_search(effect)) {
					return true;
				}
			}
			
			return false;
		}

	private:
		CardStore deck; // The player's deck (where the player's cards start off in).
		CardStore hand; // The player's hand (where cards that can be played go).
		CardStore trash; // The player's trash (where discarded cards are stored).
		CardStore life_cards; // If the player draws all of these cards, they lose.
		// The player's active and benched fighters are stored here.
		std::vector<Fighter> fighters;
		int mulligan_count = 0; // The number of mulligans performed.
		std::unique_ptr<Card> last_drawn; // A copy of the last drawn card.
		bool attacked = false; // True if the player has attacked this turn.
		bool retreated = false; // True if the player has retreated this turn.
		Display& display; // A reference to the display.
		const Renderer& renderer; // A constant reference to the renderer.
		const Messenger& messenger; // A constant reference to the messenger.
		MessengerPackage& messenger_package; // A reference to the messenger thread package.
		Thread& messenger_thread; // A reference to the thread used to get messages.
		const Button& back_button; // A constant reference to the back button.
		const Button& next_button; // A constant reference to the next button.
		Player* opponent; // A pointer to the opponent.
		CardStore& the_void; // A reference to the void card store.
		std::mt19937& generator; // A reference to the random number generator.
		bool opposing; // True if this player is the opponent.
		std::string& message; // A reference to the message sent by the opponent.
		const bool& turn; // A reference to the current turn.
		const int& turn_count; // A reference to the number of turns passed.
};
//}

// Deck Generator
//{
/**
 * A class that defines a generatable deck.
 */
class DeckCode {
	public:
		/**
		 * Constructs a deck code with its name, description, and code.
		 */
		DeckCode(
			const std::string& name,
			const std::string& description,
			const std::array<int, CARD_COUNT>& code
		) noexcept:
			name(name),
			description(description),
			code(code),
			size()
		{
			for (int i = 0; i < CARD_COUNT; ++i) {
				size += code[i];
			}
		}
		
		/**
		 * Returns the deck code's name.
		 */
		const std::string& get_name() const noexcept {
			return name;
		}
		
		/**
		 * Returns the deck's description.
		 */
		const std::string& get_description() const noexcept {
			return description;
		}
		
		/**
		 * Returns the deck's code.
		 */
		const std::array<int, CARD_COUNT>& get_code() const noexcept {
			return code;
		}
		
		/**
		 * Returns the number of cards that will be generated.
		 */
		int get_size() const noexcept {
			return size;
		}
		
	private:
		const std::string name; // The name of the deck.
		const std::string description; // The description of the deck.
		const std::array<int, CARD_COUNT> code; // Corresponds with the deck's contents.
		int size; // The number of cards in the deck.
};

// Deck Codes
//{
const DeckCode CLEAR_DECK(
	"Clear Deck",
	"Clears the deck currently being built.",
	{}
);

const DeckCode DRIVER_FAMILY_DECK(
	"Driver Family",
	"A deck featuring all of the cards in the Driver family!\n"
	"This deck cannot be built with standard procedures.",
	{
		4, // Driver
		1, // Racer
		1, // Hot Rodder
		1, // Sailor
		1, // Pirate
		1, // Dirt Biker
		1, // Monster Trucker
		1, // Pilot
		1, // Astronaut
		2, // Professor
		2, // Researcher
		2, // Lecturer
		2, // Investor
		2, // Banker
		2, // Gambler
		3, // Fire Energy
		0, // Air Energy
		2, // Water Energy
		4, // Earth Energy
		3, // Twin Energy
		4  // Universal Energy
	}
);

const DeckCode UNBOUND_DECK(
	"Unbound",
	"Allows for one to build a deck with 4 copies of a fighter or supporter card.",
	{
		4, // Driver
		4, // Racer
		4, // Hot Rodder
		4, // Sailor
		4, // Pirate
		4, // Dirt Biker
		4, // Monster Trucker
		4, // Pilot
		4, // Astronaut
		4, // Professor
		4, // Researcher
		4, // Lecturer
		4, // Investor
		4, // Banker
		4, // Gambler
		0, // Fire Energy
		0, // Air Energy
		0, // Water Energy
		0, // Earth Energy
		0, // Twin Energy
		0  // Universal Energy
	}
);
//}

// All of the deck codes.
constexpr int DECK_CODE_COUNT = 3;
const DeckCode* const ALL_DECK_CODES[DECK_CODE_COUNT] = {
	&CLEAR_DECK,
	&DRIVER_FAMILY_DECK,
	&UNBOUND_DECK
};
//}

// Main Functions
//{
// Main Game Functions
//{	
/**
 * Converts a deck code from an array to a string.
 */
std::string to_deck_code(const std::array<int, CARD_COUNT>& card_counts) noexcept {
	std::stringstream stream;
	
	for (int i = 0; i < CARD_COUNT; i++) {
		stream << card_counts[i] << ' ';
	}
	
	return stream.str();
}

/**
 * Allows the player to draw extra cards after a successful mulligan.
 * Returns the number of extra cards drawn in string form.
 */
std::string bonus_draw(
	Display& display,
	const Renderer& renderer,
	Player& player,
	std::mt19937& generator,
	const Button& next_button,
	int difference
) {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The bonus sprite is initialised.
	Sprite bonus_sprite(
		renderer.render(
			BONUS_STRING,
			BONUS_WIDTH * display_width,
			BONUS_HEIGHT * display_height,
			BONUS_SEPARATION * display_width
		)
	);
	
	// The number of cards to be drawn.
	std::string bonus;
	
	// True if the function should return.
	bool end = false;
	
	// Loop to display the bonus draw menu.
	while (!end) {
		// The display is blitted to.
		display_sprite.fill();
		display_sprite.blit(bonus_sprite, BONUS_X, BONUS_Y);
		next_button.blit_to(display_sprite);
		
		// The host port is rendered.
		display_sprite.blit(
			renderer.render(
				bonus,
				BONUS_WIDTH * display_width,
				BONUS_HEIGHT * display_height,
				BONUS_SEPARATION * display_width
			),
			BONUS_X,
			BONUS_Y + BONUS_SHIFT
		);
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// If the user clicks the next button or presses
			//   the submit key, the cards are drawn.
			if (
				Events::unpress(SUBMIT_KEY)
				|| next_button.get_rectangle().unclick()
			) {
				int draws;
				
				// An attempt to get an integral number of draws is tried.
				try {
					draws = std::stoi(bonus);
				}
				
				// If it fails, the number of draws is set to -1.
				catch (const std::exception&) {
					draws = -1;
				}
				
				// If the number of cards to be drawn is valid, the cards are drawn.
				// Drawing terminates this functions.
				if (0 <= draws && draws <= difference) {
					player.draw(draws);
					end = true;
				}
				
				break;
			}
			
			// If the user presses the delete button,
			//   the last character entered is removed.
			else if (Events::unpress(DELETE_KEY) && bonus.length()) {
				bonus.pop_back();
				break;
			}
			
			// Else the number buttons are checked to form the bonus string.
			else {
				// True when the key being pressed is found.
				bool found = false;
				
				// The numbers are checked.
				for (int i = 0; !found && i < NUMBERS; i++) {
					if (Events::unpress(Events::NUMBERS[i])) {
						bonus += '0' + i;
						found = true;
					}
				}
				
				// If a valid key was pressed, the display is updated.
				if (found) {
					break;
				}
			}

			Events::update();
		}
	}
	
	return bonus;
}

/**
 * Displays how many cards the opponent drew.
 */
void display_draw_count(
	Display& display,
	const Renderer& renderer,
	int draws
) noexcept {
	display.fill();
	display.blit(
		renderer.lined_render(
			OPPONENT_DRAW_STRING,
			OPPONENT_DRAW_WIDTH * display.width(),
			OPPONENT_DRAW_HEIGHT * display.height(),
			OPPONENT_DRAW_SEPARATION_X * display.width(),
			OPPONENT_DRAW_MAX_WIDTH * display.width(),
			OPPONENT_DRAW_SEPARATION_Y * display.height(),
			OPPONENT_DRAW_JUSTIFICATION
		),
		OPPONENT_DRAW_X,
		OPPONENT_DRAW_Y
	);
}

/**
 * The mulligan is performed.
 * Each player draws cards from their deck to form their starting hand.
 * If a player does not have a "basic" fighter, they redraw.
 * The player that redrew a lower number of times can draw an
 *   extra card for each extra redraw that the opponent performed.
 */
void mulligan(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger,
	std::vector<Player>& players,
	bool turn,
	std::mt19937& generator,
	const Button& next_button
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	display_sprite.fill();
	display_sprite.blit(
		renderer.lined_render(
			MULLIGAN_STRING,
			MULLIGAN_WIDTH * display_width,
			MULLIGAN_HEIGHT * display_height,
			MULLIGAN_SEPARATION_X * display_width,
			MULLIGAN_MAX_WIDTH * display_width,
			MULLIGAN_SEPARATION_Y * display_height,
			MULLIGAN_JUSTIFICATION
		),
		MULLIGAN_X,
		MULLIGAN_Y
	);
	next_button.blit_to(display_sprite);
	display.update();
	
	// The user proceeds at their discretion.
	while (
		!Events::unpress(SUBMIT_KEY)
		&& !next_button.get_rectangle().unclick()
	) {
		Events::update();
	}
	
	// While both players do not have a valid hand, the mulligan continues.
	while (!players[0].valid_hand() || !players[1].valid_hand()) {
		// The first player performs the mulligan if they don't have a valid hand.
		if (!players[turn].valid_hand()) {
			players[turn].mulligan();
		}
		
		// The second player performs the mulligan if they don't have a valid hand.
		if (!players[!turn].valid_hand()) {
			players[!turn].mulligan();
		}
	}
	
	// The difference in the number of mulligans determines the bonus draws.
	int difference = players[1].count_mulligans() - players[0].count_mulligans();
	
	// The number of extra card draws is limited to allow for the life cards to be played.
	if (difference > MAX_BONUS) {
		difference = MAX_BONUS;
	}
	
	else if (difference < -MAX_BONUS) {
		difference = -MAX_BONUS;
	}
	
	// If the player performed fewer mulligans, they may draw extra cards.
	if (difference > 0) {
		display_sprite.fill();
		display_sprite.blit(
			renderer.lined_render(
				BONUS_DRAW_STRING,
				BONUS_DRAW_WIDTH * display_width,
				BONUS_DRAW_HEIGHT * display_height,
				BONUS_DRAW_SEPARATION_X * display_width,
				BONUS_DRAW_MAX_WIDTH * display_width,
				BONUS_DRAW_SEPARATION_Y * display_height,
				BONUS_DRAW_JUSTIFICATION
			),
			BONUS_DRAW_X,
			BONUS_DRAW_Y
		);
		next_button.blit_to(display_sprite);
		display.update();
		
		// The user proceeds at their discretion.
		while (
			!Events::unpress(SUBMIT_KEY)
			&& !next_button.get_rectangle().unclick()
		) {
			Events::update();
		}
		
		players[PLAYER].view_hand();
		
		messenger.send(bonus_draw(
			display,
			renderer,
			players[0],
			generator,
			next_button,
			difference
		));
	}
	
	// If the opponent performed fewer mulligans, the may draw extra cards.
	else if (difference < 0) {
		// The opponent's draw potential is revealed.
		display_sprite.fill();
		display_sprite.blit(
			renderer.lined_render(
				NO_BONUS_DRAW_STRING,
				NO_BONUS_DRAW_WIDTH * display_width,
				NO_BONUS_DRAW_HEIGHT * display_height,
				NO_BONUS_DRAW_SEPARATION_X * display_width,
				NO_BONUS_DRAW_MAX_WIDTH * display_width,
				NO_BONUS_DRAW_SEPARATION_Y * display_height,
				NO_BONUS_DRAW_JUSTIFICATION
			),
			NO_BONUS_DRAW_X,
			NO_BONUS_DRAW_Y
		);
		display.update();
		
		// The draw count is received from the opponent.
		std::string draw_string(EMPTY_MESSAGE);
		MessengerPackage draw_package(messenger, draw_string);
		Thread draw_thread(MessengerPackage::get_message, &draw_package);
		
		// Events are updated to prevent closure due to app inactivity.
		while (draw_string == EMPTY_MESSAGE) {
			Events::update();
		}
		
		int draws = std::stoi(draw_string);
		
		// The user can advance when the opponent has sent their message.
		next_button.blit_to(display_sprite);
		display.update();
		
		// The user proceeds at their discretion.
		while (
			!Events::unpress(SUBMIT_KEY)
			&& !next_button.get_rectangle().unclick()
		) {
			Events::update();
		}
		
		// The opponent draws.
		players[1].draw(draws);
		
		// The opponent's bonus draw is revealed.
		display_draw_count(display, renderer, draws);
		next_button.blit_to(display_sprite);
		display.update();
		
		// The user proceeds at their discretion.
		while (
			!Events::unpress(SUBMIT_KEY)
			&& !next_button.get_rectangle().unclick()
		) {
			Events::update();
		}
	}
}

/**
 * Checks the player for defeated fighters.
 */
int defeat_check(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger,
	MessengerPackage& messenger_package,
	Thread& messenger_thread,
	const Button& back_button,
	const Button& next_button,
	std::vector<Player>& players,
	CardStore& the_void,
	std::mt19937& generator,
	bool turn
) noexcept {
	// The player, whose turn it is, is checked first.
	players[turn].defeat_check();
	
	// The other player is then checked.
	players[!turn].defeat_check();
	
	// The number of win conditions is calculated.
	std::array<int, PLAYERS> win_conditions{};
	
	win_conditions[turn] = players[!turn].loss_conditions();
	win_conditions[!turn] = players[turn].loss_conditions();
	
	// No player has reached a win condition yet.
	if (!win_conditions[turn] && !win_conditions[!turn]) {
		return NO_END;
	}
	
	// Tie game.
	else if (win_conditions[turn] == win_conditions[!turn]) {
		return TIE;
	}
	
	// The winner is returned.
	else {
		return win_conditions[OPPONENT] > win_conditions[PLAYER];
	}
}

/**
 * Hosts the main game.
 */
void game(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger,
	const std::array<int, CARD_COUNT>& card_counts,
	MessengerPackage& messenger_package,
	Thread& messenger_thread
) noexcept {
	// Game set up.
	//{
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The wait screen sprite is intialised.
	Sprite wait_sprite(
		renderer.lined_render(
			WAIT_STRING,
			WAIT_WIDTH * display_width,
			WAIT_HEIGHT * display_height,
			WAIT_SEPARATION_X * display_width,
			WAIT_MAX_WIDTH * display_width,
			WAIT_SEPARATION_Y * display_height,
			WAIT_JUSTIFICATION
		)
	);
	
	// The wait screen is rendered.
	display_sprite.fill();
	display_sprite.blit(wait_sprite, WAIT_X, WAIT_Y);
	display.update();
	
	// The main game song is loaded and queued in another thread.
	Audio duel_song(DUEL_SONG_SOURCE, DUEL_SONG_LENGTH);
	Thread song_thread(Audio::thread_queue, &duel_song);
	
	// The message is extracted from the package.
	std::string& message = messenger_package.get_string();
	
	// The seeder is determined.
	// The player with the smaller value seeds the RNG.
	std::array<double, PLAYERS> speeds = {0, 0};
	
	while (speeds[0] == speeds[1]) {
		speeds[0] = Timer::time();
		messenger.send(std::to_string(speeds[0]));
		
		// The opponent's message is waited for.
		// Event updating is used to prevent "app inactivity".
		while (message == EMPTY_MESSAGE) {
			Events::update();
		}
		
		// If the other player quit, the game cannot begin.
		if (message == TERMINATOR_STRING) {
			duel_song.pause();
			return;
		}
		
		speeds[1] = std::stod(message);
	}
	
	int seed;
	
	// The smaller value player determines the seed and sends it to the other.
	if (speeds[0] < speeds[1]) {
		seed = Timer::current();
		messenger.send(std::to_string(seed));
	}
	
	// The greater value player receives the seed.
	else {
		// The seed is received.
		seed = std::stoi(messenger.read());
	}
	
	// The RNG is seeded.
	std::mt19937 generator(seed);
	
	// The player to go first is determined.
	// Player's turn when turn is false.
	// Opponent's turn when turn is true.
	bool turn;
	
	// A coin is flipped to determine who goes first.
	if (speeds[0] < speeds[1]) {
		turn = Player::coin_flip(generator);
	}
	
	// The coin flip to go first is mirrored.
	else {
		turn = !Player::coin_flip(generator);
	}
	
	// The deck code is converted to string form and exchanged.
	std::array<std::string, PLAYERS> deck_codes;
	deck_codes[0] = to_deck_code(card_counts);
	messenger.send(deck_codes[0]);
	deck_codes[1] = messenger.read();
	
	// The back button is initialised.
	Button back_button(
		renderer.render(
			BACK_STRING,
			BACK_WIDTH * display.width(),
			BACK_HEIGHT * display.height(),
			BACK_SEPARATION * display.width()
		),
		display,
		BACK_X,
		BACK_Y
	);
	
	// The next button is initialised.
	Button next_button(
		renderer.render(
			NEXT_STRING,
			NEXT_WIDTH * display_width,
			NEXT_HEIGHT * display_height,
			NEXT_SEPARATION * display_width
		),
		display_sprite,
		NEXT_X,
		NEXT_Y
	);
	
	// The void is initialised.
	// The void is shared by the players.
	CardStore the_void;
	
	// Counts the number of rounds that have passed.
	// Fighters may not attack on the first turn.
	int turn_count = 0;
	
	// The players are initialised.
	std::vector<Player> players;
	
	for (int i = 0; i < PLAYERS; ++i) {
		players.push_back(
			Player(
				deck_codes[i],
				display,
				renderer,
				messenger,
				messenger_package,
				messenger_thread,
				back_button,
				next_button,
				the_void,
				generator,
				i,
				turn,
				turn_count
			)
		);
	}
	
	for (int i = 0; i < PLAYERS; ++i) {
		players[i].set_opponent(players[!i]);
	}
	
	// The player ordering is revealed.
	display_sprite.fill();
	display_sprite.blit(
		renderer.lined_render(
			ORDER_STRING,
			ORDER_WIDTH * display_width,
			ORDER_HEIGHT * display_height,
			ORDER_SEPARATION_X * display_width,
			ORDER_MAX_WIDTH * display_width,
			ORDER_SEPARATION_Y * display_height,
			ORDER_JUSTIFICATION
		),
		ORDER_X,
		ORDER_Y
	);
	next_button.blit_to(display_sprite);
	display.update();
	
	// The user may proceed at their discretion.
	while (
		!Events::unpress(SUBMIT_KEY)
		&& !next_button.get_rectangle().unclick()
	) {
		Events::update();
	}
	
	// The players perform the mulligan.
	mulligan(display, renderer, messenger, players, turn, generator, next_button);
	
	// The life cards are set up.
	players[turn].set_life_cards();
	players[!turn].set_life_cards();
	
	// The player sets up and sends their board.
	messenger.send(players[0].set_active());
	
	// The opponent's choice is waited for.
	message = "";
	messenger_thread.new_thread(MessengerPackage::get_message, &messenger_package);
	
	display.fill();
	display.blit(
		renderer.lined_render(
			WAIT_STRING,
			WAIT_WIDTH * display.width(),
			WAIT_HEIGHT * display.height(),
			WAIT_SEPARATION_X * display.width(),
			WAIT_MAX_WIDTH * display.width(),
			WAIT_SEPARATION_Y * display.height()
		),
		WAIT_X,
		WAIT_Y
	);
	display.update();
	
	while (message == "") {
		Events::update();
	}
	
	// The opponent's board is set up.
	players[1].set_active(message);
	
	// Non-negative when the game should end.
	int winner = -1;
	
	// The message from the opponent is awaited.
	message = EMPTY_MESSAGE;
	messenger_thread.new_thread(
		MessengerPackage::get_message,
		&messenger_package
	);
	
	// The player taking the first turn can't attack on their first turn.
	players[turn].affect(PREPARATION_EFFECT);
	//}
	
	// Board buttons initialised.
	//{
	// The player's buttons are initialised.
	//{
	// Button for the player's deck.
	Button your_deck_button(
		renderer.lined_render(
			YOUR_DECK_STRING,
			YOUR_DECK_WIDTH * display.width(),
			YOUR_DECK_HEIGHT * display.height(),
			YOUR_DECK_SEPARATION_X * display.width(),
			YOUR_DECK_MAX_WIDTH * display.width(),
			YOUR_DECK_SEPARATION_Y * display.height(),
			YOUR_DECK_JUSTIFICATION
		),
		display,
		YOUR_DECK_X,
		YOUR_DECK_Y
	);
	
	// Button for the player's trash.
	Button your_trash_button(
		renderer.lined_render(
			YOUR_TRASH_STRING,
			YOUR_TRASH_WIDTH * display.width(),
			YOUR_TRASH_HEIGHT * display.height(),
			YOUR_TRASH_SEPARATION_X * display.width(),
			YOUR_TRASH_MAX_WIDTH * display.width(),
			YOUR_TRASH_SEPARATION_Y * display.height(),
			YOUR_TRASH_JUSTIFICATION
		),
		display,
		YOUR_TRASH_X,
		YOUR_TRASH_Y
	);
	
	// Button for the player's hand.
	Button your_hand_button(
		renderer.lined_render(
			YOUR_HAND_STRING,
			YOUR_HAND_WIDTH * display.width(),
			YOUR_HAND_HEIGHT * display.height(),
			YOUR_HAND_SEPARATION_X * display.width(),
			YOUR_HAND_MAX_WIDTH * display.width(),
			YOUR_HAND_SEPARATION_Y * display.height(),
			YOUR_HAND_JUSTIFICATION
		),
		display,
		YOUR_HAND_X,
		YOUR_HAND_Y
	);
	
	// Button for the player's life cards.
	Button your_life_button(
		renderer.lined_render(
			YOUR_LIFE_STRING,
			YOUR_LIFE_WIDTH * display.width(),
			YOUR_LIFE_HEIGHT * display.height(),
			YOUR_LIFE_SEPARATION_X * display.width(),
			YOUR_LIFE_MAX_WIDTH * display.width(),
			YOUR_LIFE_SEPARATION_Y * display.height(),
			YOUR_LIFE_JUSTIFICATION
		),
		display,
		YOUR_LIFE_X,
		YOUR_LIFE_Y
	);
	
	// Button for the player's active fighter.
	Button your_active_button(
		renderer.lined_render(
			YOUR_ACTIVE_STRING,
			YOUR_ACTIVE_WIDTH * display.width(),
			YOUR_ACTIVE_HEIGHT * display.height(),
			YOUR_ACTIVE_SEPARATION_X * display.width(),
			YOUR_ACTIVE_MAX_WIDTH * display.width(),
			YOUR_ACTIVE_SEPARATION_Y * display.height(),
			YOUR_ACTIVE_JUSTIFICATION
		),
		display,
		YOUR_ACTIVE_X,
		YOUR_ACTIVE_Y
	);
	
	// Button for the player's benched fighters.
	Button your_bench_button(
		renderer.lined_render(
			YOUR_BENCH_STRING,
			YOUR_BENCH_WIDTH * display.width(),
			YOUR_BENCH_HEIGHT * display.height(),
			YOUR_BENCH_SEPARATION_X * display.width(),
			YOUR_BENCH_MAX_WIDTH * display.width(),
			YOUR_BENCH_SEPARATION_Y * display.height(),
			YOUR_BENCH_JUSTIFICATION
		),
		display,
		YOUR_BENCH_X,
		YOUR_BENCH_Y
	);
	
	// Button for the player's effects fighters.
	Button your_effects_button(
		renderer.lined_render(
			YOUR_EFFECTS_STRING,
			YOUR_EFFECTS_WIDTH * display.width(),
			YOUR_EFFECTS_HEIGHT * display.height(),
			YOUR_EFFECTS_SEPARATION_X * display.width(),
			YOUR_EFFECTS_MAX_WIDTH * display.width(),
			YOUR_EFFECTS_SEPARATION_Y * display.height(),
			YOUR_EFFECTS_JUSTIFICATION
		),
		display,
		YOUR_EFFECTS_X,
		YOUR_EFFECTS_Y
	);
	//}
	
	// The opponent's buttons are initialised.
	//{
	// Button for the opponent's deck.
	Button opponent_deck_button(
		renderer.lined_render(
			OPPONENT_DECK_STRING,
			OPPONENT_DECK_WIDTH * display.width(),
			OPPONENT_DECK_HEIGHT * display.height(),
			OPPONENT_DECK_SEPARATION_X * display.width(),
			OPPONENT_DECK_MAX_WIDTH * display.width(),
			OPPONENT_DECK_SEPARATION_Y * display.height(),
			OPPONENT_DECK_JUSTIFICATION
		),
		display,
		OPPONENT_DECK_X,
		OPPONENT_DECK_Y
	);
	
	// Button for the opponent's trash.
	Button opponent_trash_button(
		renderer.lined_render(
			OPPONENT_TRASH_STRING,
			OPPONENT_TRASH_WIDTH * display.width(),
			OPPONENT_TRASH_HEIGHT * display.height(),
			OPPONENT_TRASH_SEPARATION_X * display.width(),
			OPPONENT_TRASH_MAX_WIDTH * display.width(),
			OPPONENT_TRASH_SEPARATION_Y * display.height(),
			OPPONENT_TRASH_JUSTIFICATION
		),
		display,
		OPPONENT_TRASH_X,
		OPPONENT_TRASH_Y
	);
	
	// Button for the opponent's hand.
	Button opponent_hand_button(
		renderer.lined_render(
			OPPONENT_HAND_STRING,
			OPPONENT_HAND_WIDTH * display.width(),
			OPPONENT_HAND_HEIGHT * display.height(),
			OPPONENT_HAND_SEPARATION_X * display.width(),
			OPPONENT_HAND_MAX_WIDTH * display.width(),
			OPPONENT_HAND_SEPARATION_Y * display.height(),
			OPPONENT_HAND_JUSTIFICATION
		),
		display,
		OPPONENT_HAND_X,
		OPPONENT_HAND_Y
	);
	
	// Button for the opponent's life cards.
	Button opponent_life_button(
		renderer.lined_render(
			OPPONENT_LIFE_STRING,
			OPPONENT_LIFE_WIDTH * display.width(),
			OPPONENT_LIFE_HEIGHT * display.height(),
			OPPONENT_LIFE_SEPARATION_X * display.width(),
			OPPONENT_LIFE_MAX_WIDTH * display.width(),
			OPPONENT_LIFE_SEPARATION_Y * display.height(),
			OPPONENT_LIFE_JUSTIFICATION
		),
		display,
		OPPONENT_LIFE_X,
		OPPONENT_LIFE_Y
	);
	
	// Button for the opponent's active fighter.
	Button opponent_active_button(
		renderer.lined_render(
			OPPONENT_ACTIVE_STRING,
			OPPONENT_ACTIVE_WIDTH * display.width(),
			OPPONENT_ACTIVE_HEIGHT * display.height(),
			OPPONENT_ACTIVE_SEPARATION_X * display.width(),
			OPPONENT_ACTIVE_MAX_WIDTH * display.width(),
			OPPONENT_ACTIVE_SEPARATION_Y * display.height(),
			OPPONENT_ACTIVE_JUSTIFICATION
		),
		display,
		OPPONENT_ACTIVE_X,
		OPPONENT_ACTIVE_Y
	);
	
	// Button for the opponent's benched fighters.
	Button opponent_bench_button(
		renderer.lined_render(
			OPPONENT_BENCH_STRING,
			OPPONENT_BENCH_WIDTH * display.width(),
			OPPONENT_BENCH_HEIGHT * display.height(),
			OPPONENT_BENCH_SEPARATION_X * display.width(),
			OPPONENT_BENCH_MAX_WIDTH * display.width(),
			OPPONENT_BENCH_SEPARATION_Y * display.height(),
			OPPONENT_BENCH_JUSTIFICATION
		),
		display,
		OPPONENT_BENCH_X,
		OPPONENT_BENCH_Y
	);
	
	// Button for the opponent's effects fighters.
	Button opponent_effects_button(
		renderer.lined_render(
			OPPONENT_EFFECTS_STRING,
			OPPONENT_EFFECTS_WIDTH * display.width(),
			OPPONENT_EFFECTS_HEIGHT * display.height(),
			OPPONENT_EFFECTS_SEPARATION_X * display.width(),
			OPPONENT_EFFECTS_MAX_WIDTH * display.width(),
			OPPONENT_EFFECTS_SEPARATION_Y * display.height(),
			OPPONENT_EFFECTS_JUSTIFICATION
		),
		display,
		OPPONENT_EFFECTS_X,
		OPPONENT_EFFECTS_Y
	);
	//}
	
	// The other buttons are initialised.
	//{
	// Button for the void.
	Button the_void_button(
		renderer.render(
			THE_VOID_STRING,
			THE_VOID_WIDTH * display.width(),
			THE_VOID_HEIGHT * display.height(),
			THE_VOID_SEPARATION * display.width()
		),
		display,
		THE_VOID_X,
		THE_VOID_Y
	);
	
	// Button to end one's turn.
	Button end_turn_button(
		renderer.render(
			END_TURN_STRING,
			END_TURN_WIDTH * display.width(),
			END_TURN_HEIGHT * display.height(),
			END_TURN_SEPARATION * display.width()
		),
		display,
		END_TURN_X,
		END_TURN_Y
	);
	
	// Button to concede.
	Button concede_button(
		renderer.render(
			CONCEDE_STRING,
			CONCEDE_WIDTH * display.width(),
			CONCEDE_HEIGHT * display.height(),
			CONCEDE_SEPARATION * display.width()
		),
		display,
		CONCEDE_X,
		CONCEDE_Y
	);
	//}
	//}
	
	// The main game loop.
	while (winner < 0) {
		// If the player can draw at the start of their turn, they do so.
		if (players[turn].can_draw()) {
			int draws = TURN_DRAW;
			
			players[turn].draw(draws);
			
			// True when the turn should end.
			bool end = false;
			
			// Player's turn
			if (!turn) {
				// The drawn card is displayed.
				players[PLAYER].display_last_drawn();
				next_button.blit_to(display);
				display.update();
				
				// The player proceeds at their own discretion
				//   or if the opponent conceded.
				while (
					!Events::unpress(SUBMIT_KEY)
					&& !next_button.get_rectangle().unclick()
					&& message == EMPTY_MESSAGE
				) {
					Events::update();
				}
				
				// Loop to render and read.
				while (!end && winner < 0) {
					// The board is renderered.
					//{
					// The display is cleared.
					display.fill();
					
					// The player's buttons are blitted.
					your_deck_button.blit_to(display);
					your_trash_button.blit_to(display);
					your_hand_button.blit_to(display);
					your_life_button.blit_to(display);
					your_active_button.blit_to(display);
					your_bench_button.blit_to(display);
					your_effects_button.blit_to(display);
					
					// The opponent's buttons are blitted.
					opponent_deck_button.blit_to(display);
					opponent_trash_button.blit_to(display);
					opponent_hand_button.blit_to(display);
					opponent_life_button.blit_to(display);
					opponent_active_button.blit_to(display);
					opponent_bench_button.blit_to(display);
					opponent_effects_button.blit_to(display);
					
					// The other buttons are blitted.
					the_void_button.blit_to(display);
					end_turn_button.blit_to(display);
					concede_button.blit_to(display);
					
					// The display is updated.
					display.update();
					//}
				
					// True when the board should be rerendered.
					bool rerender = false;
				
					// Loop to get user input.
					while (!rerender) {
						// End turn and concede.
						//{
						// The player can end their turn by
						//   clicking the end turn button.
						if (end_turn_button.get_rectangle().unclick()) {
							messenger.send(END_TURN_STRING);
							end = true;
							break;
						}
						
						// The player can concede by clicking the concede button.
						else if (concede_button.get_rectangle().unclick()) {
							messenger.send(CONCEDE_STRING);
							
							// The player is informed that they conceded.
							display.fill();
							display.blit(
								renderer.lined_render(
									PLAYER_CONCEDE_STRING,
									PLAYER_CONCEDE_WIDTH * display.width(),
									PLAYER_CONCEDE_HEIGHT * display.height(),
									PLAYER_CONCEDE_SEPARATION_X * display.width(),
									PLAYER_CONCEDE_MAX_WIDTH * display.width(),
									PLAYER_CONCEDE_SEPARATION_Y * display.height(),
									PLAYER_CONCEDE_JUSTIFICATION
								),
								PLAYER_CONCEDE_X,
								PLAYER_CONCEDE_Y
							);
							next_button.blit_to(display);
							display.update();
							
							// The player proceeds at their own discretion.
							while (
								!Events::unpress(SUBMIT_KEY)
								&& !next_button.get_rectangle().unclick()
							) {
								Events::update();
							}
							
							winner = OPPONENT;
							end = true;
							break;
						}
						//}
						
						// Game state checks.
						//{
						// The player can view their deck by clicking on it.
						else if (your_deck_button.get_rectangle().unclick()) {
							players[PLAYER].view_deck();
							rerender = true;
						}
						
						// The player can view their trash by clicking on it.
						else if (your_trash_button.get_rectangle().unclick()) {
							players[PLAYER].view_trash();
							rerender = true;
						}
						
						// The plyer can view their life cards by clicking on them.
						else if (your_life_button.get_rectangle().unclick()) {
							players[PLAYER].view_life_cards();
							rerender = true;
						}
						
						// The player can view the void by clicking on it.
						else if (the_void_button.get_rectangle().unclick()) {
							the_void.view(display, renderer, message);
							rerender = true;
						}
						
						// The player can view the opponent's hand's size.
						else if (opponent_hand_button.get_rectangle().unclick()) {
							players[OPPONENT].view_hand_size();
							rerender = true;
						}
						
						// The player can view the opponent's deck's size.
						else if (opponent_deck_button.get_rectangle().unclick()) {
							players[OPPONENT].view_deck_size();
							rerender = true;
						}
						
						// The player can view the opponent's trash's size.
						else if (opponent_trash_button.get_rectangle().unclick()) {
							players[OPPONENT].view_trash();
							rerender = true;
						}
						
						// The player can view the opponent's life cards' size.
						else if (opponent_life_button.get_rectangle().unclick()) {
							players[OPPONENT].view_life_cards_size();
							rerender = true;
						}
						
						// The player can view their opponent's active fighter.
						else if (opponent_active_button.get_rectangle().unclick()) {
							players[OPPONENT].view_active();
							rerender = true;
						}
						
						// The player can view their opponent's benched fighters.
						else if (opponent_bench_button.get_rectangle().unclick()) {
							players[OPPONENT].view_bench();
							rerender = true;
						}
						
						// The player can view their effects.
						else if (your_effects_button.get_rectangle().unclick()) {
							players[PLAYER].view_effects();
							rerender = true;
						}
						
						// The player can view their opponent's effects.
						else if (opponent_effects_button.get_rectangle().unclick()) {
							players[OPPONENT].view_effects();
							rerender = true;
						}
						//}
						
						// Potential moves.
						//{
						// The player may play a card from their hand during their turn.
						else if (your_hand_button.get_rectangle().unclick()) {
							players[turn].play();
							rerender = true;
						}
						
						// The player may use their active fighter during their turn.
						else if (your_active_button.get_rectangle().unclick()) {
							players[turn].use_active();
							rerender = true;
						}
						
						// The player may use their benched fighters during their turn.
						else if (your_bench_button.get_rectangle().unclick()) {
							players[turn].use_bench();
							rerender = true;
						}
						//}
						
						// Opponent's actions.
						//{
						// The opponent conceded.
						if (message == CONCEDE_STRING) {
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
						
							// The player is informed that the opponent conceded.
							display.fill();
							display.blit(
								renderer.lined_render(
									OPPONENT_CONCEDE_STRING,
									OPPONENT_CONCEDE_WIDTH * display.width(),
									OPPONENT_CONCEDE_HEIGHT * display.height(),
									OPPONENT_CONCEDE_SEPARATION_X * display.width(),
									OPPONENT_CONCEDE_MAX_WIDTH * display.width(),
									OPPONENT_CONCEDE_SEPARATION_Y * display.height(),
									OPPONENT_CONCEDE_JUSTIFICATION
								),
								OPPONENT_CONCEDE_X,
								OPPONENT_CONCEDE_Y
							);
							next_button.blit_to(display);
							display.update();
							
							// The player proceeds at their own discretion.
							// The opponent quitting forces a procession.
							while (
								!Events::unpress(SUBMIT_KEY)
								&& !next_button.get_rectangle().unclick()
								&& message != TERMINATOR_STRING
							) {
								Events::update();
							}
							
							winner = PLAYER;
							end = true;
							break;
						}
						//}
						
						// The events are updated.
						Events::update();
					}
				
					// A concede doesn't require a check.
					if (winner == NO_END) {
						// The players are checked for any defeated fighters.
						winner = defeat_check(
							display,
							renderer,
							messenger,
							messenger_package,
							messenger_thread,
							back_button,
							next_button,
							players,
							the_void,
							generator,
							turn
						);
					}
				}
			}
			
			// Opponent's turn.
			else {
				// The number of cards that the opponent drew is displayed.
				display_draw_count(display, renderer, draws);
				next_button.blit_to(display);
				display.update();
				
				// The player proceeds at their own discretion
				//   or when the opponent makes a move.
				while (
					!Events::unpress(SUBMIT_KEY)
					&& !next_button.get_rectangle().unclick()
					&& message == EMPTY_MESSAGE
				) {
					Events::update();
				}
				
				// Loop to render, read, and mirror the opponent's actions.
				while (!end && winner < 0) {
					// The board is renderered.
					//{
					// The display is cleared.
					display.fill();
					
					// The player's buttons are blitted.
					your_deck_button.blit_to(display);
					your_trash_button.blit_to(display);
					your_hand_button.blit_to(display);
					your_life_button.blit_to(display);
					your_active_button.blit_to(display);
					your_bench_button.blit_to(display);
					your_effects_button.blit_to(display);
					
					// The opponent's buttons are blitted.
					opponent_deck_button.blit_to(display);
					opponent_trash_button.blit_to(display);
					opponent_hand_button.blit_to(display);
					opponent_life_button.blit_to(display);
					opponent_active_button.blit_to(display);
					opponent_bench_button.blit_to(display);
					opponent_effects_button.blit_to(display);
					
					// The void' button is blitted.
					the_void_button.blit_to(display);
					concede_button.blit_to(display);
					
					// The display is updated.
					display.update();
					//}
				
					// True when the board should be rerendered.
					bool rerender = false;
				
					// Loop for user input.
					while (!rerender) {
						// The player's actions.
						//{
						// The player can concede by clicking the concede button.
						if (concede_button.get_rectangle().unclick()) {
							messenger.send(CONCEDE_STRING);
							
							// The player is informed that they conceded.
							display.fill();
							display.blit(
								renderer.lined_render(
									PLAYER_CONCEDE_STRING,
									PLAYER_CONCEDE_WIDTH * display.width(),
									PLAYER_CONCEDE_HEIGHT * display.height(),
									PLAYER_CONCEDE_SEPARATION_X * display.width(),
									PLAYER_CONCEDE_MAX_WIDTH * display.width(),
									PLAYER_CONCEDE_SEPARATION_Y * display.height(),
									PLAYER_CONCEDE_JUSTIFICATION
								),
								PLAYER_CONCEDE_X,
								PLAYER_CONCEDE_Y
							);
							next_button.blit_to(display);
							display.update();
							
							// The player proceeds at their own discretion.
							while (
								!Events::unpress(SUBMIT_KEY)
								&& !next_button.get_rectangle().unclick()
							) {
								Events::update();
							}
							
							winner = OPPONENT;
							end = true;
							break;
						}
						
						// The player can view their hand by clicking on it.
						else if (your_hand_button.get_rectangle().unclick()) {
							players[PLAYER].view_hand();
							rerender = true;
						}
						
						// The player can view their deck by clicking on it.
						else if (your_deck_button.get_rectangle().unclick()) {
							players[PLAYER].view_deck();
							rerender = true;
						}
						
						// The player can view their trash by clicking on it.
						else if (your_trash_button.get_rectangle().unclick()) {
							players[PLAYER].view_trash();
							rerender = true;
						}
						
						// The plyer can view their life cards by clicking on them.
						else if (your_life_button.get_rectangle().unclick()) {
							players[PLAYER].view_life_cards();
							rerender = true;
						}
						
						// The player can view the void by clicking on it.
						else if (the_void_button.get_rectangle().unclick()) {
							the_void.view(display, renderer, message);
							rerender = true;
						}
						
						// The player can view the opponent's hand's size.
						else if (opponent_hand_button.get_rectangle().unclick()) {
							players[OPPONENT].view_hand_size();
							rerender = true;
						}
						
						// The player can view the opponent's deck's size.
						else if (opponent_deck_button.get_rectangle().unclick()) {
							players[OPPONENT].view_deck_size();
							rerender = true;
						}
						
						// The player can view the opponent's trash's size.
						else if (opponent_trash_button.get_rectangle().unclick()) {
							players[OPPONENT].view_trash();
							rerender = true;
						}
						
						// The player can view the opponent's life cards' size.
						else if (opponent_life_button.get_rectangle().unclick()) {
							players[OPPONENT].view_life_cards_size();
							rerender = true;
						}
						
						// The player can view their active fighter.
						else if (your_active_button.get_rectangle().unclick()) {
							players[PLAYER].view_active();
							rerender = true;
						}
						
						// The player can view their benched fighters.
						else if (your_bench_button.get_rectangle().unclick()) {
							players[PLAYER].view_bench();
							rerender = true;
						}
						
						// The player can view their opponent's active fighter.
						else if (opponent_active_button.get_rectangle().unclick()) {
							players[OPPONENT].view_active();
							rerender = true;
						}
						
						// The player can view their opponent's benched fighters.
						else if (opponent_bench_button.get_rectangle().unclick()) {
							players[OPPONENT].view_bench();
							rerender = true;
						}
						
						// The player can view their effects.
						else if (your_effects_button.get_rectangle().unclick()) {
							players[PLAYER].view_effects();
							rerender = true;
						}
						
						// The player can view their opponent's effects.
						else if (opponent_effects_button.get_rectangle().unclick()) {
							players[OPPONENT].view_effects();
							rerender = true;
						}
						//}
						
						// The opponent's actions.
						//{
						// The opponent ended their turn.
						if (message == END_TURN_STRING) {
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
							
							end = true;
							break;
						}
						
						// The opponent conceded.
						else if (message == CONCEDE_STRING) {
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
							
							// The player is informed that the opponent conceded.
							display.fill();
							display.blit(
								renderer.lined_render(
									OPPONENT_CONCEDE_STRING,
									OPPONENT_CONCEDE_WIDTH * display.width(),
									OPPONENT_CONCEDE_HEIGHT * display.height(),
									OPPONENT_CONCEDE_SEPARATION_X * display.width(),
									OPPONENT_CONCEDE_MAX_WIDTH * display.width(),
									OPPONENT_CONCEDE_SEPARATION_Y * display.height(),
									OPPONENT_CONCEDE_JUSTIFICATION
								),
								OPPONENT_CONCEDE_X,
								OPPONENT_CONCEDE_Y
							);
							next_button.blit_to(display);
							display.update();
							
							// The player proceeds at their own discretion.
							// The opponent quitting forces a procession.
							while (
								!Events::unpress(SUBMIT_KEY)
								&& !next_button.get_rectangle().unclick()
								&& message != TERMINATOR_STRING
							) {
								Events::update();
							}
							
							winner = PLAYER;
							end = true;
							break;
						}
						
						// The opponent played a card.
						else if (message == PLAY_MESSAGE) {
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
							
							// The message is waited for.
							while (message == EMPTY_MESSAGE) {
								Events::update();
							}
							
							// The index of the card is taken.
							int index = std::stoi(message);
							
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
						
							players[turn].play(index);
							
							rerender = true;
						}
						
						// The opponent used an ability.
						else if (message == ABILITY_MESSAGE) {
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
							
							// The ability is used.
							players[turn].use_ability();
							
							rerender = true;
						}
						
						// The opponent retreated their active fighter.
						else if (message == RETREAT_MESSAGE) {
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
							
							// The message is waited for.
							while (message == EMPTY_MESSAGE) {
								Events::update();
							}
							
							// The index of the fighter to switch is extracted.
							int index = std::stoi(message);
							
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
						
							players[turn].retreat(index);
							
							rerender = true;
						}
						
						// The opponent attacked with their active fighter.
						else if (message == ATTACK_MESSAGE) {
							// The message from the opponent is awaited.
							message = EMPTY_MESSAGE;
							messenger_thread.new_thread(
								MessengerPackage::get_message,
								&messenger_package
							);
							
							players[turn].attack();
							
							rerender = true;
						}
						//}
						
						// The events are updated.
						Events::update();
					}
				
					// A concede doesn't require a check.
					if (winner == NO_END) {
						// The players are checked for any defeated fighters.
						winner = defeat_check(
							display,
							renderer,
							messenger,
							messenger_package,
							messenger_thread,
							back_button,
							next_button,
							players,
							the_void,
							generator,
							turn
						);
					}
				}
			}
			
			// End of turn effects.
			if (winner < 0) {
				// The players perform their end of turn effects.
				players[turn].reset();
				players[!turn].reset();
				
				// The other player takes their turn.
				turn = !turn;
				
				// The number of turns taken is incremented.
				++turn_count;
			}
		}
		
		// Else, they lose.
		else {
			// The player is informed that the draw failed.
			display.fill();
			display.blit(
				renderer.lined_render(
					DRAW_FAIL_STRING,
					DRAW_FAIL_WIDTH * display.width(),
					DRAW_FAIL_HEIGHT * display.height(),
					DRAW_FAIL_SEPARATION_X * display.width(),
					DRAW_FAIL_MAX_WIDTH * display.width(),
					DRAW_FAIL_SEPARATION_Y * display.height(),
					DRAW_FAIL_JUSTIFICATION
				),
				DRAW_FAIL_X,
				DRAW_FAIL_Y
			);
			next_button.blit_to(display);
			display.update();
			
			// The player proceeds at their own discretion.
			while (
				!Events::unpress(SUBMIT_KEY)
				&& !next_button.get_rectangle().unclick()
				&& message != TERMINATOR_STRING
			) {
				Events::update();
			}
			
			winner = !turn;
		}
	}
	
	// Post game.
	//{
	// The play is notified if they won or lost.
	display.fill();
	display.blit(
		renderer.render(
			GAME_STRING,
			GAME_WIDTH * display.width(),
			GAME_HEIGHT * display.height(),
			GAME_SEPARATION * display.width()
		),
		GAME_X,
		GAME_Y
	);
	next_button.blit_to(display);
	display.update();
	
	// The player may advance at their discretion.
	// The opponent quitting forces a procession.
	while (
		!Events::unpress(SUBMIT_KEY)
		&& !next_button.get_rectangle().unclick()
		&& message != TERMINATOR_STRING
	) {
		Events::update();
	}
	
	// The song is paused to terminate the thread.
	duel_song.pause();
	//}
}
//}

// Deck Building Menus
//{
/**
 * Tells the user that the player that they connected
 *   with has an incompatible version of the program.
 */
void incompatible(Display& display, const Renderer& renderer) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The incomptability sprite is initialised.
	Sprite incompatible_sprite(
		renderer.lined_render(
			INCOMPATIBLE_STRING,
			INCOMPATIBLE_WIDTH * display_width,
			INCOMPATIBLE_HEIGHT * display_height,
			INCOMPATIBLE_SEPARATION_X * display_width,
			INCOMPATIBLE_MAX_WIDTH * display_width,
			INCOMPATIBLE_SEPARATION_Y * display_height,
			INCOMPATIBLE_JUSTIFICATION
		)
	);
	
	// The back button is intialised.
	Button back_button(
		Sprite(
			renderer.render(
				BACK_STRING,
				BACK_WIDTH * display_width,
				BACK_HEIGHT * display_height,
				BACK_SEPARATION * display_width
			)
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The display is blitted to.
	display_sprite.fill();
	display_sprite.blit(incompatible_sprite, INCOMPATIBLE_X, INCOMPATIBLE_Y);
	back_button.blit_to(display_sprite);
	display.update();
	
	// Loop for user input.
	while (
		!Events::unpress(QUIT_KEY)
		&& !back_button.get_rectangle().unclick()
	) {
		Events::update();
	}
}	

/**
 * Adds fighter cards to the player's deck.
 */
void add_fighter(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger,
	std::array<int, CARD_COUNT>& card_counts,
	int& card_count,
	const std::string& message
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The deck builder sprite is intialised.
	Sprite builder_sprite(
		renderer.render(
			BUILDER_STRING,
			BUILDER_WIDTH * display_width,
			BUILDER_HEIGHT * display_height,
			BUILDER_SEPARATION * display_width
		)
	);
	
	// The back button is initialised.
	Button back_button(
		Sprite(
			renderer.render(
				BACK_STRING,
				BACK_WIDTH * display_width,
				BACK_HEIGHT * display_height,
				BACK_SEPARATION * display_width
			)
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The left button is initialised.
	Button left_button(
		Sprite(
			LEFT_SOURCE,
			LEFT_WIDTH * display_width,
			LEFT_HEIGHT * display_height
		),
		display_sprite,
		LEFT_X,
		LEFT_Y
	);
	
	// The right button is initialised.
	Button right_button(
		Sprite(
			RIGHT_SOURCE,
			RIGHT_WIDTH * display_width,
			RIGHT_HEIGHT * display_height
		),
		display_sprite,
		RIGHT_X,
		RIGHT_Y
	);
	
	// The minus buttons are intialised.
	std::vector<Button> minus_buttons;
	
	for (int i = 0; i < PAGE_COUNT; ++i) {
		minus_buttons.push_back(
			Button(
				Sprite(
					MINUS_SOURCE,
					MINUS_WIDTH * display_width,
					MINUS_HEIGHT * display_height
				),
				display_sprite,
				MINUS_X,
				MINUS_Y + i * MINUS_Y_SHIFT
			)
		);
	}
	
	// The plus buttons are initialised.
	std::vector<Button> plus_buttons;
	
	for (int i = 0; i < PAGE_COUNT; ++i) {
		plus_buttons.push_back(
			Button(
				Sprite(
					PLUS_SOURCE,
					PLUS_WIDTH * display_width,
					PLUS_HEIGHT * display_height
				),
				display_sprite,
				PLUS_X,
				PLUS_Y + i * PLUS_Y_SHIFT
			)
		);
	}
	
	// Determines which cards are displayed.
	int page = 0;
	
	// True if the function should return.
	bool end = false;
	
	while (!end) {
		// The sprites are blitted to the display.
		display_sprite.fill();
		display_sprite.blit(builder_sprite, BUILDER_X, BUILDER_Y);
		back_button.blit_to(display_sprite);
		
		if (page > 0) {
			left_button.blit_to(display_sprite);
		}
		
		if (page < (FIGHTER_COUNT - 1) / PAGE_COUNT) {
			right_button.blit_to(display_sprite);
		}
		
		// The deck's capacity info is displayed.
		display_sprite.blit(
			renderer.render(
				CAPACITY_STRING,
				CAPACITY_WIDTH * display_width,
				CAPACITY_HEIGHT * display_height,
				CAPACITY_SEPARATION * display_width
			),
			CAPACITY_X,
			CAPACITY_Y
		);
		
		// A vector of buttons for the names is generated.
		std::vector<Button> name_buttons;
		
		// The cards' names on the page are displayed.
		for (
			int i = 0;
			i < PAGE_COUNT
			&& page * PAGE_COUNT + i < FIGHTER_COUNT;
			++i
		) {
			// The name button is stored in the vector.
			name_buttons.push_back(
				Button(
					Sprite(
						renderer.render(
							ALL_FIGHTERS[page * PAGE_COUNT + i]->get_name(),
							PAGE_WIDTH * display_width,
							PAGE_HEIGHT * display_height,
							PAGE_SEPARATION * display_width
						)
					),
					display_sprite,
					PAGE_NAME_X,
					PAGE_Y + i * PAGE_Y_SHIFT
				)
			);
			
			// The name is displayed.
			name_buttons[i].blit_to(display_sprite);
			
			// The card count is displayed.
			display_sprite.blit(
				renderer.render(
					std::to_string(card_counts[page * PAGE_COUNT + i])
					+ '/'
					+ std::to_string(MAX_FIGHTER_COPIES),
					PAGE_WIDTH * display_width,
					PAGE_HEIGHT * display_height,
					PAGE_SEPARATION * display_width
				),
				PAGE_VALUE_X,
				PAGE_Y + i * PAGE_Y_SHIFT
			);
			
			if (card_counts[page * PAGE_COUNT + i]) {
				minus_buttons[i].blit_to(display_sprite);
			}
			
			if (
				card_counts[page * PAGE_COUNT + i] < MAX_FIGHTER_COPIES
				&& card_count < DECK_SIZE
			) {
				plus_buttons[i].blit_to(display_sprite);
			}
		}
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// The user can return to the deck building menu
			//   with the use of the back button.
			// The opponent disconnecting also has this effect.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
				|| message == TERMINATOR_STRING
			) {
				end = true;
				break;
			}
			
			// The page number is decremented (if possible).
			else if (
				(
					Events::unpress(Events::LEFT)
					|| left_button.get_rectangle().unclick()
				) && page > 0
			) {
				--page;
				break;
			}
			
			// The page number is incremented (if possible).
			else if (
				(
					Events::unpress(Events::RIGHT)
					|| right_button.get_rectangle().unclick()
				) && page < (FIGHTER_COUNT - 1) / PAGE_COUNT
			) {
				++page;
				break;
			}
			
			// The other buttons are checked.
			else {
				// True if the button being clicked was found.
				bool found = false;
				
				// The plus and minus buttons increment or decrement
				//   the number of copies of a card in the deck.
				// The names display the card's details.
				for (
					int i = 0;
					i < PAGE_COUNT && page * PAGE_COUNT + i < FIGHTER_COUNT;
					++i
				) {
					// Removes a card.
					if (
						card_counts[page * PAGE_COUNT + i]
						&& minus_buttons[i].get_rectangle().unclick()
					) {
						--card_counts[page * PAGE_COUNT + i];
						--card_count;
						found = true;
						break;
					}
					
					// Adds a card.
					else if (
						card_counts[page * PAGE_COUNT + i] < MAX_FIGHTER_COPIES
						&& card_count < DECK_SIZE
						&& plus_buttons[i].get_rectangle().unclick()
					) {
						++card_counts[page * PAGE_COUNT + i];
						++card_count;
						found = true;
						break;
					}
					
					// Diplays a card's details.
					else if (name_buttons[i].get_rectangle().unclick()) {
						ALL_FIGHTERS[page * PAGE_COUNT + i]->render(display, renderer);
						back_button.blit_to(display_sprite);
						display.update();
						
						while (
							!Events::unpress(QUIT_KEY)
							&& !back_button.get_rectangle().unclick()
						) {
							Events::update();
						}
						
						found = true;
						break;
					}
				}
				
				if (found) {
					break;
				}
			}
			
			// The events are updated.
			Events::update();
		}
	}
}

/**
 * Adds supporter cards to the player's deck.
 */
void add_supporter(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger,
	std::array<int, CARD_COUNT>& card_counts,
	int& card_count,
	const std::string& message
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The deck builder sprite is intialised.
	Sprite builder_sprite(
		renderer.render(
			BUILDER_STRING,
			BUILDER_WIDTH * display_width,
			BUILDER_HEIGHT * display_height,
			BUILDER_SEPARATION * display_width
		)
	);
	
	// The back button is initialised.
	Button back_button(
		Sprite(
			renderer.render(
				BACK_STRING,
				BACK_WIDTH * display_width,
				BACK_HEIGHT * display_height,
				BACK_SEPARATION * display_width
			)
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The left button is initialised.
	Button left_button(
		Sprite(
			LEFT_SOURCE,
			LEFT_WIDTH * display_width,
			LEFT_HEIGHT * display_height
		),
		display_sprite,
		LEFT_X,
		LEFT_Y
	);
	
	// The right button is initialised.
	Button right_button(
		Sprite(
			RIGHT_SOURCE,
			RIGHT_WIDTH * display_width,
			RIGHT_HEIGHT * display_height
		),
		display_sprite,
		RIGHT_X,
		RIGHT_Y
	);
	
	// The minus buttons are intialised.
	std::vector<Button> minus_buttons;
	
	for (int i = 0; i < PAGE_COUNT; ++i) {
		minus_buttons.push_back(
			Button(
				Sprite(
					MINUS_SOURCE,
					MINUS_WIDTH * display_width,
					MINUS_HEIGHT * display_height
				),
				display_sprite,
				MINUS_X,
				MINUS_Y + i * MINUS_Y_SHIFT
			)
		);
	}
	
	
	// The plus buttons are initialised.
	std::vector<Button> plus_buttons;
	
	for (int i = 0; i < PAGE_COUNT; ++i) {
		plus_buttons.push_back(
			Button(
				Sprite(
					PLUS_SOURCE,
					PLUS_WIDTH * display_width,
					PLUS_HEIGHT * display_height
				),
				display_sprite,
				PLUS_X,
				PLUS_Y + i * PLUS_Y_SHIFT
			)
		);
	}
	
	// Determines which cards are displayed.
	int page = 0;
	
	// True if the function should return.
	bool end = false;
	
	while (!end) {
		// The sprites are blitted to the display.
		display_sprite.fill();
		display_sprite.blit(builder_sprite, BUILDER_X, BUILDER_Y);
		back_button.blit_to(display_sprite);
		
		if (page > 0) {
			left_button.blit_to(display_sprite);
		}
		
		if (page < (SUPPORTER_COUNT - 1) / PAGE_COUNT) {
			right_button.blit_to(display_sprite);
		}
		
		// The deck's capacity info is displayed.
		display_sprite.blit(
			renderer.render(
				CAPACITY_STRING,
				CAPACITY_WIDTH * display_width,
				CAPACITY_HEIGHT * display_height,
				CAPACITY_SEPARATION * display_width
			),
			CAPACITY_X,
			CAPACITY_Y
		);
		
		// A vector of buttons for the names is generated.
		std::vector<Button> name_buttons;
		
		// The cards' names on the page are displayed.
		for (
			int i = 0;
			i < PAGE_COUNT
			&& page * PAGE_COUNT + i < SUPPORTER_COUNT;
			++i
		) {
			// The name button is stored in the vector.
			name_buttons.push_back(
				Button(
					Sprite(
						renderer.render(
							ALL_SUPPORTERS[page * PAGE_COUNT + i]->get_name(),
							PAGE_WIDTH * display_width,
							PAGE_HEIGHT * display_height,
							PAGE_SEPARATION * display_width
						)
					),
					display_sprite,
					PAGE_NAME_X,
					PAGE_Y + i * PAGE_Y_SHIFT
				)
			);
			
			// The name is displayed.
			name_buttons[i].blit_to(display_sprite);
			
			// The card count is displayed.
			display_sprite.blit(
				renderer.render(
					std::to_string(card_counts[FIGHTER_COUNT + page * PAGE_COUNT + i])
					+ '/'
					+ std::to_string(MAX_SUPPORTER_COPIES),
					PAGE_WIDTH * display_width,
					PAGE_HEIGHT * display_height,
					PAGE_SEPARATION * display_width
				),
				PAGE_VALUE_X,
				PAGE_Y + i * PAGE_Y_SHIFT
			);
			
			if (card_counts[FIGHTER_COUNT + page * PAGE_COUNT + i]) {
				minus_buttons[i].blit_to(display_sprite);
			}
			
			if (
				card_counts[FIGHTER_COUNT + page * PAGE_COUNT + i] < MAX_SUPPORTER_COPIES
				&& card_count < DECK_SIZE
			) {
				plus_buttons[i].blit_to(display_sprite);
			}
		}
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// The user can return to the deck building menu
			//   with the use of the back button.
			// The opponent disconnecting also has this effect.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
				|| message == TERMINATOR_STRING
			) {
				end = true;
				break;
			}
			
			// The page number is decremented (if possible).
			else if (
				(
					Events::unpress(Events::LEFT)
					|| left_button.get_rectangle().unclick()
				) && page > 0
			) {
				--page;
				break;
			}
			
			// The page number is incremented (if possible).
			else if (
				(
					Events::unpress(Events::RIGHT)
					|| right_button.get_rectangle().unclick()
				) && page < (SUPPORTER_COUNT - 1) / PAGE_COUNT
			) {
				++page;
				break;
			}
			
			// The other buttons are checked.
			else {
				// True if the button being clicked was found.
				bool found = false;
				
				// The plus and minus buttons increment or decrement
				//   the number of copies of a card in the deck.
				// The names display the card's details.
				for (
					int i = 0;
					i < PAGE_COUNT && page * PAGE_COUNT + i < SUPPORTER_COUNT;
					++i
				) {
					// Removes a card.
					if (
						card_counts[FIGHTER_COUNT + page * PAGE_COUNT + i]
						&& minus_buttons[i].get_rectangle().unclick()
					) {
						--card_counts[FIGHTER_COUNT + page * PAGE_COUNT + i];
						--card_count;
						found = true;
						break;
					}
					
					// Adds a card.
					else if (
						card_counts[FIGHTER_COUNT + page * PAGE_COUNT + i]
						< MAX_SUPPORTER_COPIES
						&& card_count < DECK_SIZE
						&& plus_buttons[i].get_rectangle().unclick()
					) {
						++card_counts[FIGHTER_COUNT + page * PAGE_COUNT + i];
						++card_count;
						found = true;
						break;
					}
					
					// Diplays a card's details.
					else if (name_buttons[i].get_rectangle().unclick()) {
						ALL_SUPPORTERS[page * PAGE_COUNT + i]->render(display, renderer);
						back_button.blit_to(display_sprite);
						display.update();
						
						while (
							!Events::unpress(QUIT_KEY)
							&& !back_button.get_rectangle().unclick()
						) {
							Events::update();
						}
						
						found = true;
						break;
					}
				}
				
				if (found) {
					break;
				}
			}
			
			// The events are updated.
			Events::update();
		}
	}
}

/**
 * Adds energy cards to the player's deck.
 */
void add_energy(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger,
	std::array<int, CARD_COUNT>& card_counts,
	int& card_count,
	const std::string& message
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The deck builder sprite is intialised.
	Sprite builder_sprite(
		renderer.render(
			BUILDER_STRING,
			BUILDER_WIDTH * display_width,
			BUILDER_HEIGHT * display_height,
			BUILDER_SEPARATION * display_width
		)
	);
	
	// The back button is initialised.
	Button back_button(
		Sprite(
			renderer.render(
				BACK_STRING,
				BACK_WIDTH * display_width,
				BACK_HEIGHT * display_height,
				BACK_SEPARATION * display_width
			)
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The left button is initialised.
	Button left_button(
		Sprite(
			LEFT_SOURCE,
			LEFT_WIDTH * display_width,
			LEFT_HEIGHT * display_height
		),
		display_sprite,
		LEFT_X,
		LEFT_Y
	);
	
	// The right button is initialised.
	Button right_button(
		Sprite(
			RIGHT_SOURCE,
			RIGHT_WIDTH * display_width,
			RIGHT_HEIGHT * display_height
		),
		display_sprite,
		RIGHT_X,
		RIGHT_Y
	);
	
	// The minus buttons are intialised.
	std::vector<Button> minus_buttons;
	
	for (int i = 0; i < PAGE_COUNT; ++i) {
		minus_buttons.push_back(
			Button(
				Sprite(
					MINUS_SOURCE,
					MINUS_WIDTH * display_width,
					MINUS_HEIGHT * display_height
				),
				display_sprite,
				MINUS_X,
				MINUS_Y + i * MINUS_Y_SHIFT
			)
		);
	}
	
	
	// The plus buttons are initialised.
	std::vector<Button> plus_buttons;
	
	for (int i = 0; i < PAGE_COUNT; ++i) {
		plus_buttons.push_back(
			Button(
				Sprite(
					PLUS_SOURCE,
					PLUS_WIDTH * display_width,
					PLUS_HEIGHT * display_height
				),
				display_sprite,
				PLUS_X,
				PLUS_Y + i * PLUS_Y_SHIFT
			)
		);
	}
	
	// Determines which cards are displayed.
	int page = 0;
	
	// True if the function should return.
	bool end = false;
	
	while (!end) {
		// The sprites are blitted to the display.
		display_sprite.fill();
		display_sprite.blit(builder_sprite, BUILDER_X, BUILDER_Y);
		back_button.blit_to(display_sprite);
		
		if (page > 0) {
			left_button.blit_to(display_sprite);
		}
		
		if (page < (ENERGY_COUNT - 1) / PAGE_COUNT) {
			right_button.blit_to(display_sprite);
		}
		
		// The deck's capacity info is displayed.
		display_sprite.blit(
			renderer.render(
				CAPACITY_STRING,
				CAPACITY_WIDTH * display_width,
				CAPACITY_HEIGHT * display_height,
				CAPACITY_SEPARATION * display_width
			),
			CAPACITY_X,
			CAPACITY_Y
		);
		
		// A vector of buttons for the names is generated.
		std::vector<Button> name_buttons;
		
		// The cards' names on the page are displayed.
		for (
			int i = 0;
			i < PAGE_COUNT
			&& page * PAGE_COUNT + i < ENERGY_COUNT;
			++i
		) {
			// The name button is stored in the vector.
			name_buttons.push_back(
				Button(
					Sprite(
						renderer.render(
							ALL_ENERGY[page * PAGE_COUNT + i]->get_name(),
							PAGE_WIDTH * display_width,
							PAGE_HEIGHT * display_height,
							PAGE_SEPARATION * display_width
						)
					),
					display_sprite,
					PAGE_NAME_X,
					PAGE_Y + i * PAGE_Y_SHIFT
				)
			);
			
			// The name is displayed.
			name_buttons[i].blit_to(display_sprite);
			
			// The card count is displayed.
			display_sprite.blit(
				renderer.render(
					std::to_string(card_counts[
						FIGHTER_COUNT + SUPPORTER_COUNT + page * PAGE_COUNT + i
					])
					+ '/'
					+ std::to_string(MAX_ENERGY_COPIES),
					PAGE_WIDTH * display_width,
					PAGE_HEIGHT * display_height,
					PAGE_SEPARATION * display_width
				),
				PAGE_VALUE_X,
				PAGE_Y + i * PAGE_Y_SHIFT
			);
			
			if (card_counts[FIGHTER_COUNT + SUPPORTER_COUNT + page * PAGE_COUNT + i]) {
				minus_buttons[i].blit_to(display_sprite);
			}
			
			if (
				card_counts[FIGHTER_COUNT + SUPPORTER_COUNT + page * PAGE_COUNT + i]
				< MAX_ENERGY_COPIES
				&& card_count < DECK_SIZE
			) {
				plus_buttons[i].blit_to(display_sprite);
			}
		}
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// The user can return to the deck building menu
			//   with the use of the back button.
			// The opponent disconnecting also has this effect.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
				|| message == TERMINATOR_STRING
			) {
				end = true;
				break;
			}
			
			// The page number is decremented (if possible).
			else if (
				(
					Events::unpress(Events::LEFT)
					|| left_button.get_rectangle().unclick()
				) && page > 0
			) {
				--page;
				break;
			}
			
			// The page number is incremented (if possible).
			else if (
				(
					Events::unpress(Events::RIGHT)
					|| right_button.get_rectangle().unclick()
				) && page < (ENERGY_COUNT - 1) / PAGE_COUNT
			) {
				++page;
				break;
			}
			
			// The other buttons are checked.
			else {
				// True if the button being clicked was found.
				bool found = false;
				
				// The plus and minus buttons increment or decrement
				//   the number of copies of a card in the deck.
				// The names display the card's details.
				for (
					int i = 0;
					i < PAGE_COUNT && page * PAGE_COUNT + i < ENERGY_COUNT;
					++i
				) {
					// Removes a card.
					if (
						card_counts[FIGHTER_COUNT + SUPPORTER_COUNT + page * PAGE_COUNT + i]
						&& minus_buttons[i].get_rectangle().unclick()
					) {
						--card_counts[
							FIGHTER_COUNT + SUPPORTER_COUNT + page * PAGE_COUNT + i
						];
						--card_count;
						found = true;
						break;
					}
					
					// Adds a card.
					else if (
						card_counts[FIGHTER_COUNT + SUPPORTER_COUNT + page * PAGE_COUNT + i]
						< MAX_ENERGY_COPIES
						&& card_count < DECK_SIZE
						&& plus_buttons[i].get_rectangle().unclick()
					) {
						++card_counts[
							FIGHTER_COUNT + SUPPORTER_COUNT + page * PAGE_COUNT + i
						];
						++card_count;
						found = true;
						break;
					}
					
					// Diplays a card's details.
					else if (name_buttons[i].get_rectangle().unclick()) {
						ALL_ENERGY[page * PAGE_COUNT + i]->render(display, renderer);
						back_button.blit_to(display_sprite);
						display.update();
						
						while (
							!Events::unpress(QUIT_KEY)
							&& !back_button.get_rectangle().unclick()
						) {
							Events::update();
						}
						
						found = true;
						break;
					}
				}
				
				if (found) {
					break;
				}
			}
			
			// The events are updated.
			Events::update();
		}
	}
}

/**
 * Generates a premade deck.
 */
void generate(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger,
	std::array<int, CARD_COUNT>& card_counts,
	int& card_count,
	const std::string& message
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The deck builder sprite is intialised.
	Sprite builder_sprite(
		renderer.render(
			BUILDER_STRING,
			BUILDER_WIDTH * display_width,
			BUILDER_HEIGHT * display_height,
			BUILDER_SEPARATION * display_width
		)
	);
	
	// The back button is initialised.
	Button back_button(
		Sprite(
			renderer.render(
				BACK_STRING,
				BACK_WIDTH * display_width,
				BACK_HEIGHT * display_height,
				BACK_SEPARATION * display_width
			)
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The left button is initialised.
	Button left_button(
		Sprite(
			LEFT_SOURCE,
			LEFT_WIDTH * display_width,
			LEFT_HEIGHT * display_height
		),
		display_sprite,
		LEFT_X,
		LEFT_Y
	);
	
	// The right button is initialised.
	Button right_button(
		Sprite(
			RIGHT_SOURCE,
			RIGHT_WIDTH * display_width,
			RIGHT_HEIGHT * display_height
		),
		display_sprite,
		RIGHT_X,
		RIGHT_Y
	);
	
	// The generate buttons are intialised.
	std::vector<Button> generate_buttons;
	
	for (int i = 0; i < PAGE_COUNT; ++i) {
		generate_buttons.push_back(
			Button(
				renderer.render(
					GENERATE_STRING,
					GENERATE_WIDTH * display_width,
					GENERATE_HEIGHT * display_height,
					GENERATE_SEPARATION * display_width
				),
				display_sprite,
				GENERATE_X,
				GENERATE_Y + i * GENERATE_Y_SHIFT
			)
		);
	}
	
	// Determines which decks are displayed.
	int page = 0;
	
	// True if the function should return.
	bool end = false;
	
	while (!end) {
		// The sprites are blitted to the display.
		display_sprite.fill();
		display_sprite.blit(builder_sprite, BUILDER_X, BUILDER_Y);
		back_button.blit_to(display_sprite);
		
		if (page > 0) {
			left_button.blit_to(display_sprite);
		}
		
		if (page < (DECK_CODE_COUNT - 1) / PAGE_COUNT) {
			right_button.blit_to(display_sprite);
		}
		
		// The deck's capacity info is displayed.
		display_sprite.blit(
			renderer.render(
				CAPACITY_STRING,
				CAPACITY_WIDTH * display_width,
				CAPACITY_HEIGHT * display_height,
				CAPACITY_SEPARATION * display_width
			),
			CAPACITY_X,
			CAPACITY_Y
		);
		
		// A vector of buttons for the names is generated.
		std::vector<Button> name_buttons;
		
		// The decks' names on the page are displayed.
		for (
			int i = 0;
			i < PAGE_COUNT
			&& page * PAGE_COUNT + i < DECK_CODE_COUNT;
			++i
		) {
			// The name button is stored in the vector.
			name_buttons.push_back(
				Button(
					Sprite(
						renderer.render(
							ALL_DECK_CODES[page * PAGE_COUNT + i]->get_name(),
							PAGE_WIDTH * display_width,
							PAGE_HEIGHT * display_height,
							PAGE_SEPARATION * display_width
						)
					),
					display_sprite,
					PAGE_NAME_X,
					PAGE_Y + i * PAGE_Y_SHIFT
				)
			);
			
			// The name is displayed.
			name_buttons[i].blit_to(display_sprite);
			
			// The generate buttons are diplayed.
			generate_buttons[i].blit_to(display_sprite);
		}
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// The user can return to the deck building menu
			//   with the use of the back button.
			// The opponent disconnecting also has this effect.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
				|| message == TERMINATOR_STRING
			) {
				end = true;
				break;
			}
			
			// The page number is decremented (if possible).
			else if (
				(
					Events::unpress(Events::LEFT)
					|| left_button.get_rectangle().unclick()
				) && page > 0
			) {
				--page;
				break;
			}
			
			// The page number is incremented (if possible).
			else if (
				(
					Events::unpress(Events::RIGHT)
					|| right_button.get_rectangle().unclick()
				) && page < (DECK_CODE_COUNT - 1) / PAGE_COUNT
			) {
				++page;
				break;
			}
			
			// The other buttons are checked.
			else {
				// True if the button being clicked was found.
				bool found = false;
				
				// The plus and minus buttons increment or decrement
				//   the number of copies of a card in the deck.
				// The names display the card's details.
				for (
					int i = 0;
					i < PAGE_COUNT && page * PAGE_COUNT + i < DECK_CODE_COUNT;
					++i
				) {
					// Generates the chosen deck.
					if (generate_buttons[i].get_rectangle().unclick()) {
						card_counts = ALL_DECK_CODES[page * PAGE_COUNT + i]->get_code();
						card_count = ALL_DECK_CODES[page * PAGE_COUNT + i]->get_size();
						found = true;
						break;
					}
					
					// Displays a deck's details.
					else if (name_buttons[i].get_rectangle().unclick()) {
						display_sprite.fill();
						display_sprite.blit(
							renderer.lined_render(
								DESCRIPTION_STRING,
								DESCRIPTION_WIDTH * display_width,
								DESCRIPTION_HEIGHT * display_height,
								DESCRIPTION_SEPARATION_X * display_width,
								DESCRIPTION_MAX_WIDTH * display_width,
								DESCRIPTION_SEPARATION_Y * display_height,
								DESCRIPTION_JUSTIFICATION
							),
							DESCRIPTION_X,
							DESCRIPTION_Y
						);
						back_button.blit_to(display_sprite);
						display.update();
						
						// Pressing or clicking back stops displaying the deck's details.
						while (
							!Events::unpress(QUIT_KEY)
							&& !back_button.get_rectangle().unclick()
						) {
							Events::update();
						}
						
						found = true;
						break;
					}
				}
				
				if (found) {
					break;
				}
			}
			
			// The events are updated.
			Events::update();
		}
	}
}

/**
 * Returns true if the deck has a fighter that
 *   does not rank up from another fighter.
 */
bool has_basic(const std::array<int, CARD_COUNT>& card_counts) noexcept {
	for (int i = 0; i < FIGHTER_COUNT; i++) {
		if (card_counts[i]) {
			if (ALL_FIGHTERS[i]->basic()) {
				return true;
			}
		}
	}
	
	return false;
}

/**
 * Returns true if the deck is valid.
 * Gives the reason for deck invalidity if false is to be returned.
 */
bool valid_deck(
	Display& display,
	const Renderer& renderer,
	const std::array<int, CARD_COUNT>& card_counts,
	const int& card_count
) noexcept {
	std::string error_string;
	
	if (card_count == DECK_SIZE) {
		if (has_basic(card_counts)) {
			return true;
		}
		
		else {
			error_string = NO_BASICS_STRING;
		}
	}
	
	else {
		error_string = INVALID_SIZE_STRING;
	}
	
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The error sprite is initialised.
	Sprite deck_error_sprite(
		renderer.lined_render(
			error_string,
			DECK_ERROR_WIDTH * display_width,
			DECK_ERROR_HEIGHT * display_height,
			DECK_ERROR_SEPARATION_X * display_width,
			DECK_ERROR_MAX_WIDTH * display_width,
			DECK_ERROR_SEPARATION_Y * display_height,
			DECK_ERROR_JUSTIFICATION
		)
	);
	
	// The back button is initialised.
	Button back_button(
		Sprite(
			renderer.render(
				BACK_STRING,
				BACK_WIDTH * display_width,
				BACK_HEIGHT * display_height,
				BACK_SEPARATION * display_width
			)
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The display is blitted to.
	display_sprite.fill();
	display_sprite.blit(deck_error_sprite, DECK_ERROR_X, DECK_ERROR_Y);
	back_button.blit_to(display_sprite);
	display.update();
	
	// The error message is displayed until the user goes back.
	while (
		!Events::unpress(QUIT_KEY)
		&& !back_button.get_rectangle().unclick()
	) {
		Events::update();
	}
	
	return false;
}

/**
 * Builds each player's deck and sends them to the opponent.
 * Also sends the RNG from the server to the
 *   client and seeds both player's RNG.
 */
void build_deck(
	Display& display,
	const Renderer& renderer,
	const Messenger& messenger
) noexcept {
	std::string connection_test = System::version(VERSION);
	
	// Sends a message to the other player to confirm the connection.
	// The message sent is the program version in string form.
	messenger.send(connection_test);
	
	// If the received string does not match, the connection was unsuccessful.
	// This ensures that other TCP program do not connect with this one.
	// This also ensures that the versions of the program match.
	// This also allows for connection bridging to be performed safely,
	//   as the game will not start until both players connect.
	if (messenger.read() != connection_test) {
		incompatible(display, renderer);
		messenger.send(TERMINATOR_STRING);
		return;
	}
	
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The deck builder sprite is intialised.
	Sprite builder_sprite(
		renderer.render(
			BUILDER_STRING,
			BUILDER_WIDTH * display_width,
			BUILDER_HEIGHT * display_height,
			BUILDER_SEPARATION * display_width
		)
	);
	
	// The fighter button is intialised.
	Button fighter_button(
		Sprite(
			renderer.render(
				FIGHTER_STRING,
				FIGHTER_WIDTH * display_width,
				FIGHTER_HEIGHT * display_height,
				FIGHTER_SEPARATION * display_width
			)
		),
		display_sprite,
		FIGHTER_X,
		FIGHTER_Y
	);
	
	// The supporter button is intitialised.
	Button supporter_button(
		Sprite(
			renderer.render(
				SUPPORTER_STRING,
				SUPPORTER_WIDTH * display_width,
				SUPPORTER_HEIGHT * display_height,
				SUPPORTER_SEPARATION * display_width
			)
		),
		display_sprite,
		SUPPORTER_X,
		SUPPORTER_Y
	);
	
	// The energy button is intialised.
	Button energy_button(
		Sprite(
			renderer.render(
				ENERGY_STRING,
				ENERGY_WIDTH * display_width,
				ENERGY_HEIGHT * display_height,
				ENERGY_SEPARATION * display_width
			)
		),
		display_sprite,
		ENERGY_X,
		ENERGY_Y
	);
	
	// The generator button is initialised.
	Button generator_button(
		Sprite(
			renderer.render(
				GENERATOR_STRING,
				GENERATOR_WIDTH * display_width,
				GENERATOR_HEIGHT * display_height,
				GENERATOR_SEPARATION * display_width
			)
		),
		display_sprite,
		GENERATOR_X,
		GENERATOR_Y
	);
	
	// The done button is initialised.
	Button done_button(
		Sprite(
			renderer.render(
				DONE_STRING,
				DONE_WIDTH * display_width,
				DONE_HEIGHT * display_height,
				DONE_SEPARATION * display_width
			)
		),
		display_sprite,
		DONE_X,
		DONE_Y
	);
	
	// The quit button is initialised.
	Button quit_button(
		Sprite(
			renderer.render(
				QUIT_STRING,
				QUIT_WIDTH * display_width,
				QUIT_HEIGHT * display_height,
				QUIT_SEPARATION * display_width
			)
		),
		display_sprite,
		QUIT_X_ALT,
		QUIT_Y
	);
	
	// The deck building song is loaded and queued in another thread.
	Audio build_song(BUILD_SONG_SOURCE, BUILD_SONG_LENGTH);
	Thread song_thread(Audio::thread_queue, &build_song);
	
	// The opponent's message is read and stored in another thread.
	std::string message(EMPTY_MESSAGE);
	MessengerPackage package(messenger, message);
	Thread message_thread(MessengerPackage::get_message, &package);
	
	// The number of cards currently in the player's deck.
	int card_count = 0;
	
	// The number of cards that should be included in the players deck.
	std::array<int, CARD_COUNT> card_counts{};
	
	// True if the function should return.
	bool end = false;
	
	// Loop to display the deck building main menu.
	while (!end) {
		// The display is blitted to.
		display_sprite.fill();
		display_sprite.blit(builder_sprite, BUILDER_X, BUILDER_Y);
		fighter_button.blit_to(display_sprite);
		supporter_button.blit_to(display_sprite);
		energy_button.blit_to(display_sprite);
		generator_button.blit_to(display_sprite);
		done_button.blit_to(display_sprite);
		quit_button.blit_to(display_sprite);
		
		// The deck's capacity info is displayed.
		display_sprite.blit(
			renderer.render(
				CAPACITY_STRING,
				CAPACITY_WIDTH * display_width,
				CAPACITY_HEIGHT * display_height,
				CAPACITY_SEPARATION * display_width
			),
			CAPACITY_X,
			CAPACITY_Y
		);
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// If the quit button was pressed or
			//   clicked, or the opponent disconnected,
			//   the port menu is returned to.
			if (
				quit_button.get_rectangle().unclick()
				|| message == TERMINATOR_STRING
			) {
				end = true;
				break;
			}
			
			// Else, if the fighter button was clicked,
			//   the fighter addition menu is opened.
			else if (fighter_button.get_rectangle().unclick()) {
				add_fighter(
					display,
					renderer,
					messenger,
					card_counts,
					card_count,
					message
				);
				
				break;
			}
			
			// Else, if the supporter button was clicked,
			//   the supporter addition menu is opened.
			else if (supporter_button.get_rectangle().unclick()) {
				add_supporter(
					display,
					renderer,
					messenger,
					card_counts,
					card_count,
					message
				);
				
				break;
			}
			
			// Else, if the energy button was clicked,
			//   the energy addition menu is opened.
			else if (energy_button.get_rectangle().unclick()) {
				add_energy(
					display,
					renderer,
					messenger,
					card_counts,
					card_count,
					message
				);
				
				break;
			}
			
			// Else, if the deck generator button was clicked,
			//   the deck generator menu is opened.
			else if (generator_button.get_rectangle().unclick()) {
				generate(
					display,
					renderer,
					messenger,
					card_counts,
					card_count,
					message
				);
				
				break;
			}
			
			// Else, if the done button was pressed or clicked
			//   and the deck is valid, the game begins.
			else if (done_button.get_rectangle().unclick()) {
				// Separate if statement to get the break (for rendering this menu).
				if (valid_deck(display, renderer, card_counts, card_count)) {
					build_song.pause();
					song_thread.wait();
					build_song.play();
					build_song.dequeue();
					game(
						display,
						renderer,
						messenger,
						card_counts,
						package,
						message_thread
					);
					song_thread.new_thread(Audio::thread_queue, &build_song);
				}
				
				break;
			}
			
			// The events are updated.
			Events::update();
		}
	}
	
	// The other player is notified that this player has disconnected.
	messenger.send(TERMINATOR_STRING);
	
	// The build song is paused, which terminates the queuing thread.
	build_song.pause();
}
//}

// Main and Connection Menus
//{
/**
 * Attempts to initialise the server.
 * The user may cancel this intialisation.
 */
void set_server(
	Display& display,
	const Renderer& renderer,
	Audio& menu_song,
	Thread& song_thread,
	Button& back_button,
	int port
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The wait sprite is intialised.
	Sprite wait_sprite(
		renderer.lined_render(
			WAIT_STRING,
			WAIT_WIDTH * display_width,
			WAIT_HEIGHT * display_height,
			WAIT_SEPARATION_X * display_width,
			WAIT_MAX_WIDTH * display_width,
			WAIT_SEPARATION_Y * display_height,
			WAIT_JUSTIFICATION
		)
	);
	
	// True if the function should return.
	bool end = false;
	
	// The server is initialised in another thread.
	// This allows the user to cancel the operation.
	std::unique_ptr<Server> server;
	ServerPackage package(server, end, port);
	Thread thread(ServerPackage::make_server, &package);
	
	// Loop to display the wait screen.
	while (!end) {
		// The display is blitted to.
		display_sprite.fill();
		display_sprite.blit(wait_sprite, WAIT_X, WAIT_Y);
		back_button.blit_to(display_sprite);
		display.update();
		
		// Loop to get user input and wait for the client.
		while (!end) {
			// If the user clicks the back button or presses
			//   the quit key, the port menu is returned to.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
			) {
				end = true;
			}
			
			// If the server was successfully constructed,
			//   the main game is moved to.
			// The main menu music stops playing and is dequeued.
			// The music starts playing from the start,
			//   when the main game function returns.
			// This screen is not returned to.
			else if (server) {
				menu_song.pause();
				song_thread.wait();
				menu_song.play();
				menu_song.dequeue();
				
				build_deck(
					display,
					renderer,
					*server
				);
				
				song_thread.new_thread(Audio::thread_queue, &menu_song);
				end = true;
			}
			
			// The events are updated.
			Events::update();
		}
	}
}

/**
 * Attempts to initialise the client.
 * The initialisation is cancelled if the host cannot be resolved.
 */
void set_client(
	Display& display,
	const Renderer& renderer,
	Audio& menu_song,
	Thread& song_thread,
	Button& back_button,
	const std::string& address,
	int port
) noexcept {
	// The main menu music is stopped.
	menu_song.pause();
	song_thread.wait();
	menu_song.play();
	menu_song.dequeue();
	
	// An attempt is made to connect to the server.
	try {
		build_deck(
			display,
			renderer,
			Client(address, port)
		);
	}
	
	// If the server cannot be connected to, an error message
	//   is displayed on the screen and the user can return
	//   to the port configuration menu.
	catch (const std::exception&) {
		// The components of the display are extracted.
		Sprite& display_sprite = display.get_sprite();
		int display_width = display_sprite.get_width();
		int display_height = display_sprite.get_height();
		
		Sprite no_server_sprite(
			renderer.lined_render(
				NO_SERVER_STRING,
				NO_SERVER_WIDTH * display_width,
				NO_SERVER_HEIGHT * display_height,
				NO_SERVER_SEPARATION_X * display_width,
				NO_SERVER_MAX_WIDTH * display_width,
				NO_SERVER_SEPARATION_Y * display_height,
				NO_SERVER_JUSTIFICATION
			)
		);
		
		// The display is blitted to.
		display_sprite.fill();
		display_sprite.blit(no_server_sprite, NO_SERVER_X, NO_SERVER_Y);
		back_button.blit_to(display_sprite);
		display.update();
		
		// Loop for input.
		while (
			!Events::unpress(QUIT_KEY)
			&& !back_button.get_rectangle().unclick()
		) {
			Events::update();
		}
	}
	
	// The main menu music recommences from the start.
	song_thread.new_thread(Audio::thread_queue, &menu_song);
}

/**
 * Sets the host's port.
 */
void set_port(
	Display& display,
	const Renderer& renderer,
	Audio& menu_song,
	Thread& song_thread,
	Button& back_button,
	Button& next_button,
	const std::string& address
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The port sprite is initialised.
	Sprite port_sprite(
		renderer.render(
			PORT_STRING,
			PORT_WIDTH * display_width,
			PORT_HEIGHT * display_height,
			PORT_SEPARATION * display_width
		)
	);
	
	// The host's port.
	std::string port;
	
	// True if the function should return.
	bool end = false;
	
	// Loop to display the port menu.
	while (!end) {
		// The display is blitted to.
		display_sprite.fill();
		display_sprite.blit(port_sprite, PORT_X, PORT_Y);
		back_button.blit_to(display_sprite);
		next_button.blit_to(display_sprite);
		
		// The host port is rendered.
		display_sprite.blit(
			renderer.render(
				port,
				PORT_WIDTH * display_width,
				PORT_HEIGHT * display_height,
				PORT_SEPARATION * display_width
			),
			PORT_X,
			PORT_Y + PORT_SHIFT
		);
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// If the user clicks the back button or presses
			//   the quit key, the address menu is returned to.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
			) {
				end = true;
				break;
			}
			
			// If the user clicks the next button or presses the
			//   submit key, the messenger is initialised.
			else if (
				Events::unpress(SUBMIT_KEY)
				|| next_button.get_rectangle().unclick()
			) {
				try {
					// The server is hosted at the given port.
					if (address == SERVER_STRING) {
						set_server(
							display,
							renderer,
							menu_song,
							song_thread,
							back_button,
							std::stoi(port)
						);
					}
					
					// The client attempts to connect to the server.
					else {
						set_client(
							display,
							renderer,
							menu_song,
							song_thread,
							back_button,
							address,
							std::stoi(port)
						);
					}
				}
				
				catch (const std::exception&) {}
				
				break;
			}
			
			// If the user presses the delete button,
			//   the last character entered is removed.
			else if (Events::unpress(DELETE_KEY) && port.length()) {
				port.pop_back();
				break;
			}
			
			// Else the number buttons are checked to form the port string.
			else {
				// True when the key being pressed is found.
				bool found = false;
				
				// The numbers are checked.
				for (int i = 0; !found && i < NUMBERS; i++) {
					if (Events::unpress(Events::NUMBERS[i])) {
						port += '0' + i;
						found = true;
					}
				}
				
				// If a valid key was pressed, the display is updated.
				if (found) {
					break;
				}
			}

			Events::update();
		}
	}
}

/**
 * Sets the host's address.
 */
void set_address(
	Display& display,
	const Renderer& renderer,
	Audio& menu_song,
	Thread& song_thread,
	Button& back_button,
	Button& next_button
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The address sprite is initialised.
	Sprite address_sprite(
		renderer.render(
			ADDRESS_STRING,
			ADDRESS_WIDTH * display_width,
			ADDRESS_HEIGHT * display_height,
			ADDRESS_SEPARATION * display_width
		)
	);
	
	// The address of the host.
	std::string address;
	
	// True if the function should return.
	bool end = false;
	
	// Loop to display the address menu.
	while (!end) {
		// The display is blitted to.
		display_sprite.fill();
		display_sprite.blit(address_sprite, ADDRESS_X, ADDRESS_Y);
		back_button.blit_to(display_sprite);
		next_button.blit_to(display_sprite);
		
		// The host address is rendered.
		display_sprite.blit(
			renderer.render(
				address,
				ADDRESS_WIDTH * display_width,
				ADDRESS_HEIGHT * display_height,
				ADDRESS_SEPARATION * display_width
			),
			ADDRESS_X,
			ADDRESS_Y + ADDRESS_SHIFT
		);
		
		// The display is updated.
		display.update();
		
		// Loop to get user input.
		while (true) {
			// If the user clicks the back button or presses
			//   the quit key, the connect menu is returned to.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
			) {
				end = true;
				break;
			}
			
			// If the user clicks the next button or presses
			//   the submit key, the port menu is moved to.
			else if (
				Events::unpress(SUBMIT_KEY)
				|| next_button.get_rectangle().unclick()
			) {
				set_port(
					display,
					renderer,
					menu_song,
					song_thread,
					back_button,
					next_button,
					address
				);
				
				break;
			}
			
			// If the user presses the delete button,
			//   the last character entered is removed.
			else if (Events::unpress(DELETE_KEY) && address.length()) {
				address.pop_back();
				break;
			}
			
			// A full stop is appended to the address, if
			//   the user pressed the full stop button.
			else if (Events::unpress(Events::FULL_STOP)) {
				address += '.';
				break;
			}
			
			// Else the number buttons are checked to form the address string.
			else {
				// True when the key being pressed is found.
				bool found = false;
				
				// The numbers are checked.
				for (int i = 0; !found && i < NUMBERS; i++) {
					if (Events::unpress(Events::NUMBERS[i])) {
						address += '0' + i;
						found = true;
					}
				}
				
				// If a valid key was pressed, the display is updated.
				if (found) {
					break;
				}
			}

			Events::update();
		}
	}
}

/**
 * Connects the player with another.
 * One player will host the server.
 * The other player will connect to the server as a client.
 */
void connect(
	Display& display,
	const Renderer& renderer,
	Audio& menu_song,
	Thread& song_thread
) noexcept {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The server button is initialised.
	Button server_button(
		Sprite(
			renderer.render(
				SERVER_STRING,
				SERVER_WIDTH * display_width,
				SERVER_HEIGHT * display_height,
				SERVER_SEPARATION * display_width
			)
		),
		display_sprite,
		SERVER_X,
		SERVER_Y
	);
	
	// The client button is initialised.
	Button client_button(
		Sprite(
			renderer.render(
				CLIENT_STRING,
				CLIENT_WIDTH * display_width,
				CLIENT_HEIGHT * display_height,
				CLIENT_SEPARATION * display_width
			)
		),
		display_sprite,
		CLIENT_X,
		CLIENT_Y
	);
	
	// The back button is initialised.
	Button back_button(
		Sprite(
			renderer.render(
				BACK_STRING,
				BACK_WIDTH * display_width,
				BACK_HEIGHT * display_height,
				BACK_SEPARATION * display_width
			)
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The next button is initialised for future use.
	Button next_button(
		Sprite(
			renderer.render(
				NEXT_STRING,
				NEXT_WIDTH * display_width,
				NEXT_HEIGHT * display_height,
				NEXT_SEPARATION * display_width
			)
		),
		display_sprite,
		NEXT_X,
		NEXT_Y
	);
	
	// True if the function should return.
	bool end = false;
	
	// Loop to display the connection menu.
	while (!end) {
		// The sprites are blitted to the display.
		display_sprite.fill();
		server_button.blit_to(display_sprite);
		client_button.blit_to(display_sprite);
		back_button.blit_to(display_sprite);
		display.update();
		
		// Loop to get user input.
		while (true) {
			// If the user clicks the back button or the
			//   quit key, the main menu is returned to.
			if (
				Events::unpress(QUIT_KEY)
				|| back_button.get_rectangle().unclick()
			) {
				end = true;
				break;
			}
			
			// If the server button is clicked, the port for
			//   the server to be hosted on is prompted for.
			else if (server_button.get_rectangle().unclick()) {
				set_port(
					display,
					renderer,
					menu_song,
					song_thread,
					back_button,
					next_button,
					SERVER_STRING
				);
				
				break;
			}
			
			// If the client button is clicked, the
			//   address of the server is prompted for.
			else if (client_button.get_rectangle().unclick()) {
				set_address(
					display,
					renderer,
					menu_song,
					song_thread,
					back_button,
					next_button
				);
				
				break;
			}
			
			// The events are updated.
			Events::update();
		}
	}
}

/**
 * A card game designed by Chigozie Agomo.
 * Powered by the SDL and Net Utilities library.
 * A retake on LifeTCG with graphics.
 */
int main(int argc, char** argv) noexcept {
	// The library is initialised for video, audio, and networking.
	System::initialise(System::VIDEO | System::AUDIO | System::NET);
	
	// The version of this program and the version of
	//   the SDL and Net Utilities library are displayed.
	std::string version_string = System::version(VERSION);
	std::cout
		<< "\nDemi Duel by Chigozie Agomo.\nVersion: "
		<< version_string
		<< "\n\nPowered by:\n"
		<< System::info()
		<< std::endl
	;
	
	{
		// The display is initialised and its components are extracted.
		Display display(TITLE_STRING, WINDOW_WIDTH, WINDOW_HEIGHT);
		Sprite& display_sprite = display.get_sprite();
		int display_width = display_sprite.get_width();
		int display_height = display_sprite.get_height();
		
		// The renderer is initialised.
		//   The characters and sources are set.
		std::array<char, RENDERER_COUNT> characters;
		std::array<std::string, RENDERER_COUNT> sources;
		
		//     The directory is set.
		for (int i = 0; i < RENDERER_COUNT; i++) {
			sources[i] = SOURCE_DIRECTORY;
		}
		
		//     The lowercase letters are set.
		for (int i = 0; i < LETTERS; i++) {
			characters[i] = 'a' + i;
			sources[i] += 'a' + i;
		}
		
		// The uppercase letters are set.
		for (int i = 0; i < LETTERS; i++) {
			characters[LETTERS + i] = 'A' + i;
			sources[LETTERS + i] += 'a' + i;
		}
		
		//     The numbers are set.
		for (int i = 0; i < NUMBERS; i++) {
			characters[2 * LETTERS + i] = '0' + i;
			sources[2 * LETTERS + i] += '0' + i;
		}
		
		//     The file extension is set.
		for (int i = 0; i < RENDERER_COUNT; i++) {
			sources[i] += SOURCE_EXTENSION;
		}
		
		// The punctuation characters and sources are set.
		characters[RENDERER_COUNT - 4] = '.';
		sources[RENDERER_COUNT - 4] = FULL_STOP_SOURCE;
		characters[RENDERER_COUNT - 3] = ',';
		sources[RENDERER_COUNT - 3] = COMMA_SOURCE;
		characters[RENDERER_COUNT - 2] = ':';
		sources[RENDERER_COUNT - 2] = COLON_SOURCE;
		characters[RENDERER_COUNT - 1] = '/';
		sources[RENDERER_COUNT - 1] = SLASH_SOURCE;
		characters[RENDERER_COUNT - 7] = '!';
		sources[RENDERER_COUNT - 7] = EXCLAMATION_SOURCE;
		characters[RENDERER_COUNT - 6] = '?';
		sources[RENDERER_COUNT - 6] = QUESTION_SOURCE;
		characters[RENDERER_COUNT - 5] = ';';
		sources[RENDERER_COUNT - 5] = SEMICOLON_SOURCE;
		characters[RENDERER_COUNT - 9] = '(';
		sources[RENDERER_COUNT - 9] = LEFT_BRACKET_SOURCE;
		characters[RENDERER_COUNT - 8] = ')';
		sources[RENDERER_COUNT - 8] = RIGHT_BRACKET_SOURCE;
		characters[RENDERER_COUNT - 10] = '\'';
		sources[RENDERER_COUNT - 10] = APOSTROPHE_SOURCE;
		characters[RENDERER_COUNT - 12] = '+';
		sources[RENDERER_COUNT - 12] = PLUS_SOURCE;
		characters[RENDERER_COUNT - 11] = '-';
		sources[RENDERER_COUNT - 11] = MINUS_SOURCE;
		
		//   The sprites are loaded.
		FullRenderer<RENDERER_COUNT> renderer(characters, sources);
		
		// The title is rendered.
		Sprite title_sprite(
			renderer.render(
				TITLE_STRING,
				TITLE_WIDTH * display_width,
				TITLE_HEIGHT * display_height,
				TITLE_SEPARATION * display_width
			)
		);
		
		// The copyright is rendered.
		Sprite credits_sprite(
			renderer.lined_render(
				CREDITS_STRING,
				CREDITS_WIDTH * display_width,
				CREDITS_HEIGHT * display_height,
				CREDITS_SEPARATION_X * display_width,
				CREDITS_MAX_WIDTH * display_width,
				CREDITS_SEPARATION_Y * display_height,
				CREDITS_JUSTIFICATION
			)
		);
		
		// The quit button is initialised.
		Button quit_button(
			Sprite(
				renderer.render(
					QUIT_STRING,
					QUIT_WIDTH * display_width,
					QUIT_HEIGHT * display_height,
					QUIT_SEPARATION * display_width
				)
			),
			display_sprite,
			QUIT_X,
			QUIT_Y
		);
		
		// The play button is initialised.
		Button play_button(
			Sprite(
				renderer.render(
					PLAY_STRING,
					PLAY_WIDTH * display_width,
					PLAY_HEIGHT * display_height,
					PLAY_SEPARATION * display_width
				)
			),
			display_sprite,
			PLAY_X,
			PLAY_Y
		);
		
		// The menu song is loaded and queued in another thread.
		Audio menu_song(MENU_SONG_SOURCE, MENU_SONG_LENGTH);
		Thread thread(Audio::thread_queue, &menu_song);
		
		// True when the program should end.
		bool end = false;
		
		// Loop to display the main menu.
		while (!end) {
			display_sprite.fill();
			display_sprite.blit(title_sprite, TITLE_X, TITLE_Y);
			display_sprite.blit(credits_sprite, CREDITS_X, CREDITS_Y);
			quit_button.blit_to(display_sprite);
			play_button.blit_to(display_sprite);
			display.update();
			
			// Loop to get user input.
			while (true) {
				// The user can quit with the keyboard or mouse.
				if (
					Events::press(QUIT_KEY)
					|| quit_button.get_rectangle().click()
				) {
					end = true;
					break;
				}
				
				// The user can start by clicking the play button.
				else if (
					play_button.get_rectangle().unclick()
				) {
					connect(display, renderer, menu_song, thread);
					break;
				}
				
				// The events are updated.
				Events::update();
			}
		}

		// The menu song is paused, which terminates the queuing thread.
		menu_song.pause();
	}
	
	// The library is shut down.
	System::terminate();
	return 0;
}
//}
//}

/* CHANGELOG:
	v0.1:
	  The essential game components were implemented.
	  The cards Driver, Racer, Hot Rodder, Professor, Researcher,
	    Fire Energy, Air Energy, Water Energy, Earth Energy,
		Twin Energy, and Universal Energy were added.
	v0.2:
	  The cards Lecturer, Investor, Banker, and Gambler were added.
	  Racer's attack's damage was decreased from 500 to 400.
	  Racer's ability now applies a power effect of 100.
	  Preparation no longer affects the first player for the entire game.
	  Increased the number of cards in a deck from 30 to 40.
	  Increased the number of life cards placed from 3 to 4.
	  Increased the number of cards in the starting hand from 5 to 8.
	v0.3
	  The cards Sailor, Pirate, Dirt Biker, Monster
	    Trucker, Pilot, and Astronaut were added.
	  Racer's attack cost was decreased from 2000 to 1500.
	  Fighters now display what they rank up from in brackets.
	  Fighters can no longer attempt to retreat when the bench is empty.
	  Fighters now display their number of ability uses.
	  The "defending fighter" in the attack description has
	    been renamed to the "opponent's active fighter".
	  Racer's attack's damage was reduced from 400 to 350.
	  Racer's ability's damage boost was increased from 100 to 150.
	  Hot Rodder's attack's damage was reduced from 500 to 350.
	  Hot Rodder's ability's damage boost was increased from 250 to 400.
	  Drawing now display the total number of cards drawn for the player drawing.
 */