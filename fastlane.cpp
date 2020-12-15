#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

#define TITLE "Fast Lane by Chigozie Agomo"
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800
#define RESET SDL_SCANCODE_R
#define QUIT SDL_SCANCODE_ESCAPE
#define MOVE SDL_SCANCODE_SPACE
#define BG_R 0
#define BG_G 0
#define BG_B 0
#define PLAYER_Y_SHIFT 50
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100
#define P_R 0
#define P_G 0
#define P_B 255
#define WALL_WIDTH 200
#define WALL_HEIGHT 25
#define BASE_VEL 0.5
#define VEL_GRAD 0.05
#define W_R 255
#define W_G 0
#define W_B 0

int coin_flip() {
	return 2 * rand() / (RAND_MAX + 1);
}

class Player {
	public:
		Player() {
			rect.y = WINDOW_HEIGHT - PLAYER_HEIGHT - PLAYER_Y_SHIFT;
			rect.w = PLAYER_WIDTH;
			rect.h = PLAYER_HEIGHT;
			press = false;
		}
		
		void init() {
			rect.x = WINDOW_WIDTH / 4 - PLAYER_WIDTH / 2 + coin_flip() * WINDOW_WIDTH / 2;
		}
		
		void update(SDL_Surface* display) {
			if (SDL_GetKeyboardState(NULL)[MOVE]) {
				if (!press) {
					if (rect.x - (WINDOW_WIDTH / 4 - PLAYER_WIDTH / 2)) {
						rect.x -= WINDOW_WIDTH / 2;
					}
					
					else {
						rect.x += WINDOW_WIDTH / 2;
					}
					
					press = true;
				}
			}
			
			else if (press) {
				press = false;
			}
			
			SDL_FillRect(display, &rect, SDL_MapRGB(display->format, P_R, P_G, P_B));
		}
		
		SDL_Rect* get_rect() {
			return &rect;
		}
		
	private:
		SDL_Rect rect;
		bool press;
};

class Wall {
	public:
		Wall() {
			rect.w = WALL_WIDTH;
			rect.h = WALL_HEIGHT;
			vel[0] = 0;
		}
		
		void init(int score) {
			pos[0] = WINDOW_WIDTH / 4 - WALL_WIDTH / 2 + coin_flip() * WINDOW_WIDTH / 2;
			pos[1] = -WALL_HEIGHT;
			set_rect();
			
			vel[1] = get_vel(score);
		}
		
		bool update(Player player, int* score, SDL_Surface* display) {
			if (pos[1] >= WINDOW_HEIGHT) {
				init(++*score);
			}
			
			pos[1] += vel[1];
			set_rect();
			
			SDL_FillRect(display, &rect, SDL_MapRGB(display->format, W_R, W_G, W_B));
			
			return SDL_HasIntersection(player.get_rect(), &rect);
		}
	
	private:
		void set_rect() {
			rect.x = pos[0];
			rect.y = pos[1];
		}
		
		double get_vel(int score) {
			return BASE_VEL + VEL_GRAD * score;
		}
		
		SDL_Rect rect;
		double pos[2];
		double vel[2];
};

int main(int argc, char** argv) {
	srand(time(NULL));
	
	SDL_Window* window = SDL_CreateWindow(
		TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	
	Player player;
	Wall wall;
	
	bool quit = false;
	
	printf("Press the spacebar to switch lanes to avoid the walls!\n");
	printf("Press r to restart the game and press esc to quit.\n");
	
	while (!quit) {		
		int score = 0;
		bool end = false;
		
		player.init();
		wall.init(score);
		
		while (!quit && !end) {
			end = SDL_GetKeyboardState(NULL)[RESET];
			quit = SDL_GetKeyboardState(NULL)[QUIT];
			
			player.update(display);
			
			if (wall.update(player, &score, display)) {
				printf("Score: %d\n", score);
				
				while (!quit && !end) {
					end = SDL_GetKeyboardState(NULL)[RESET];
					quit = SDL_GetKeyboardState(NULL)[QUIT];
					SDL_PumpEvents();
				}
			}
			
			SDL_UpdateWindowSurface(window);
			SDL_PumpEvents();
			
			SDL_FillRect(display, NULL, SDL_MapRGB(display->format, BG_R, BG_G, BG_B));
		}
		
		while (SDL_GetKeyboardState(NULL)[RESET]) {
			SDL_PumpEvents();
		}
	}
}