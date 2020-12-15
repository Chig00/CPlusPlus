#include <cmath>
#include <sstream>
#include "client.hpp"
#include "sdlutil.hpp"

// Constants
//   Title
const char* const TITLE = "Run and Gun (Server) by Chigozie Agomo";

//   Colour
const int BACKGROUND[] = { 0, 0, 0 };
const int PLAYER_COLOUR[] = { 0, 0, 0xff };
const int ENEMY_COLOUR[] = { 0xff, 0, 0 };

//   Size
const double PLAYER_WIDTH = 1.0 / 16;
const double PLAYER_HEIGHT = 1.0 / 9;
const double BULLET_WIDTH = 1.0 / 64;
const double BULLET_HEIGHT = 1.0 / 36;

//   Spawn
const double SPAWN = 0.5;
const double PLAYER_SPAWN = 0.3;
const double ENEMY_SPAWN = 0.7;

//   Controls
const int UP = SDL_SCANCODE_W;
const int DOWN = SDL_SCANCODE_S;
const int LEFT = SDL_SCANCODE_A;
const int RIGHT = SDL_SCANCODE_D;
const int EXIT = SDL_SCANCODE_ESCAPE;

//   Velocity
const double PLAYER_VELOCITY = 0.5;
const double BULLET_VELOCITY = 1;

//   Stun duration
const double STUN = 1;

/* Class for the players' bullets
   Bullets knock back the opponent on contact
   Only one bullet can be active for each player at a time
   Bullets are deactivated upon contacting the opponent or exiting the screen
 */
class Bullet {
public:
	/* Constructs the player's bullet, which starts off being inactive
	   The colour of the bullet matches its player
	 */
	Bullet(int display_width, int display_height, int r, int g, int b) {
		surface = new Surface(display_width, display_height, 0, 0, BULLET_WIDTH, BULLET_HEIGHT, r, g, b);
		active = false;
		clicking = false;
	}

	/* The memory allocated to the surface is freed
	 */
	~Bullet() {
		delete surface;
	}

	/* Returns the bullet's position in string form
	 */
	std::string status() {
		std::stringstream stream;
		stream << active << ' ' << position[0] << ' ' << position[1];
		return stream.str();
	}

	/* Sets the bullet activity
	   Also sets the position if active
	 */
	void activate(bool a, double x, double y) {
		active = a;

		if (active) {
			position[0] = 1 - x;
			position[1] = y;
			last_move = get_time();
		}
	}

	/* Deactivates the bullet
	 */
	void deactivate() {
		active = false;
	}

	/* Returns true if the bullet is active
	 */
	bool is_active() {
		return active;
	}

	SDL_Rect get_rect() {
		return surface->get_rect();
	}

	/* Updates the bullet
	   Activates the bullet with a left-click
	   Moves the bullet if it is active
	   Deactivates it if it moved offscreen
	 */
	void update(int dx, int dy, double ox, double oy) {
		// A bullet can only be shot when inactive
		if (!active) {
			// A click must be released for a shot to be refired
			if (!clicking) {
				int x;
				int y;

				// The mouse's  and state are gotten
				if (click(SDL_BUTTON_LEFT, &x, &y)) {
					// The x and y coordinates of the mouse form a vector with
					//   the player's position as the origin
					double x2 = x - dx * ox;
					double y2 = y - dy * oy;

					// The bullet's position is set
					position[0] = ox;
					position[1] = oy;

					// The unit vector is found
					velocity[0] =
						BULLET_VELOCITY * x2
						/ std::sqrt(x2 * x2 + y2 * y2)
						;
					velocity[1] =
						BULLET_VELOCITY * y2
						/ std::sqrt(x2 * x2 + y2 * y2)
						;

					// The bullet is now active
					active = true;

					// The player is now clicking
					clicking = true;
				}
			}

			// The game checks if the player has released the mouse
			else if (!click(SDL_BUTTON_LEFT)) {
				clicking = false;
			}
		}

		// Moves the bullet if it is active
		if (active) {
			double new_move = get_time();
			double move = new_move - last_move;
			last_move = new_move;
			position[0] += move * velocity[0];
			position[1] += move * velocity[1];
		}

		// If the bullet moved offscreen, it is deactivated
		if (position[0] < -BULLET_WIDTH / 2) {
			active = false;
		}

		else if (position[0] > 1 + BULLET_WIDTH / 2) {
			active = false;
		}

		else if (position[1] < -BULLET_HEIGHT / 2) {
			active = false;
		}

		else if (position[1] > 1 + BULLET_HEIGHT / 2) {
			active = false;
		}
	}

	/* Blits the bullet to the surface
	 */
	void blit(SDL_Surface* surf) {
		surface->blit(surf, position[0], position[1]);
	}

private:
	Surface* surface;
	double position[2];
	double velocity[2];
	bool active;
	bool clicking;
	double last_move;
};

/* Class for the player and the opponent
   The player can move with the keyboard and shoot with the mouse
 */
class Player {
public:
	/* Constructs a player at their spawn
	 */
	Player(double spawn, int display_width, int display_height, int r, int g, int b) {
		position[0] = spawn;
		position[1] = SPAWN;
		surface = new Surface(display_width, display_height, spawn, SPAWN, PLAYER_WIDTH, PLAYER_HEIGHT, r, g, b);
		bullet = new Bullet(display_width, display_height, r, g, b);
		last_move = get_time();
		stunned = false;
	}

	/* Frees the memory dynamically allocated to the player
	 */
	~Player() {
		delete bullet;
		delete surface;
	}

	/* Updates the player
	   The player is moved according to the button presses
	   The bullet is shot depending on the mouse's state
	   The bullet is moved if it is active
	   Checks are not performed in this method
	   The player does not move if stunned by the opponent's bullet
	 */
	void update(int x, int y) {
		double new_move = get_time();

		if (!stunned) {
			double move = PLAYER_VELOCITY * (new_move - last_move);
			last_move = new_move;

			if (key_press(UP)) {
				if (!key_press(DOWN)) {
					position[1] -= move;
				}
			}

			else if (key_press(DOWN)) {
				position[1] += move;
			}

			if (key_press(LEFT)) {
				if (!key_press(RIGHT)) {
					position[0] -= move;
				}
			}

			else if (key_press(RIGHT)) {
				position[0] += move;
			}
		}

		else if (new_move >= last_move + STUN) {
			last_move = new_move;
			stunned = false;
		}

		bullet->update(x, y, position[0], position[1]);
	}

	/* Updates the opponent
	   Performs checks for both players and their bullets
	   Players offscreen are moved back onscreen
	   Bullets offscreen are deactivated
	   Bullets colliding with opposing player's will knock those player's back
	   Also renders the players and their bullets to the display
	 */
	void update(std::string data, Player* player, Display* display) {
		// The data stream is initialised
		std::stringstream stream(data);

		// The bullet data
		bool active;
		double x;
		double y;

		// The data is extracted
		stream >> position[0] >> position[1] >> active >> x >> y;

		// The position is mirrored left-to-right
		position[0] = 1 - position[0];

		// The bullet is activated
		bullet->activate(active, x, y);

		// The players are moved back onscreen
		fix_position();
		player->fix_position();

		if (player->intersect(bullet->get_rect())) {
			player->stunned = true;
			player->last_move = get_time();
			player->bullet->deactivate();
		}

		// The player's surface are blitted to the display
		blit(display->get_surface());
		player->blit(display->get_surface());

		if (bullet_active()) {
			blit_bullet(display->get_surface());
		}

		if (player->bullet_active()) {
			player->blit_bullet(display->get_surface());
		}
	}

	/* Returns a string containing the player's information
	 */
	std::string status() {
		std::stringstream stream;
		stream << position[0] << ' ' << position[1] << ' ' << bullet->status();
		return stream.str();
	}

	/* Blits the player's surface to the given one
	 */
	void blit(SDL_Surface* surf) {
		surface->blit(surf, position[0], position[1]);
	}

	/* Blits the player's bullet's surface to the given one
	 */
	void blit_bullet(SDL_Surface* surf) {
		bullet->blit(surf);
	}

	/* Moves the player back onscreen
	 */
	void fix_position() {
		if (position[0] < PLAYER_WIDTH / 2) {
			position[0] = PLAYER_WIDTH / 2;
		}

		else if (position[0] > 1 - PLAYER_WIDTH / 2) {
			position[0] = 1 - PLAYER_WIDTH / 2;
		}

		if (position[1] < PLAYER_HEIGHT / 2) {
			position[1] = PLAYER_HEIGHT / 2;
		}

		else if (position[1] > 1 - PLAYER_HEIGHT / 2) {
			position[1] = 1 - PLAYER_HEIGHT / 2;
		}
	}

	/* Returns true if the player's bullet is active
	 */
	bool bullet_active() {
		return bullet->is_active();
	}

	/* Returns true if the given rect intersects with the player
	 */
	bool intersect(SDL_Rect rect) {
		return SDL_HasIntersection(&surface->get_rect(), &rect);
	}

private:
	Surface* surface;
	double position[2];
	double last_move;
	Bullet* bullet;
	bool stunned;
};

/* A battle arena connecting two computers
   Players can move around and shoot
 */
int main(int argc, char* argv[]) {
	// The IP address of the server
	std::string ip_address;

	// If the IP address of the server was given as a commandline argument, it is used
	if (argc == 2) {
		ip_address = argv[1];
	}

	// Else, the IP address is prompted for
	else {
		std::cout << "IP Address: ";
		std::getline(std::cin, ip_address);
	}

	// The messenger is initialised
	ClientMessenger messenger(ip_address);

	// The server is sent the ok signal
	messenger.send("ok");

	// SDL is initialised
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	// The display is initialised
	Display* display = new Display(TITLE);

	// The players are initialised
	Player* player = new Player(PLAYER_SPAWN, display->get_width(), display->get_height(), PLAYER_COLOUR[0], PLAYER_COLOUR[1], PLAYER_COLOUR[2]);
	Player* enemy = new Player(ENEMY_SPAWN, display->get_width(), display->get_height(), ENEMY_COLOUR[0], ENEMY_COLOUR[1], ENEMY_COLOUR[2]);

	// Main game loop
	while (!key_press(EXIT)) {
		display->fill(BACKGROUND[0], BACKGROUND[1], BACKGROUND[2]);
		player->update(display->get_width(), display->get_height());
		messenger.send(player->status());
		enemy->update(messenger.read(), player, display);

		display->update();
		SDL_PumpEvents();
	}

	// The dynamically allocated memory is freed
	delete enemy;
	delete player;
	delete display;

	// SDL is shut down
	SDL_Quit();

	return 0;
}