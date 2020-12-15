#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

#define TITLE "Rocket Trip by Chigozie Agomo"
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800
#define QUIT SDL_SCANCODE_ESCAPE
#define RESET SDL_SCANCODE_R
#define MOVE SDL_SCANCODE_SPACE
#define BG_R 0
#define BG_G 0
#define BG_B 0
#define ROCKET "rocket.bmp"
#define ROCKET_WIDTH 50
#define ROCKET_HEIGHT 100
#define ROCKET_SHIFT 50
#define ASTER "asteroid.bmp"
#define ASTER_WIDTH 100
#define ASTER_HEIGHT 100
#define BASE_VEL 0.5
#define VEL_GRAD 0.05

int coin_flip() {
	return 2 * rand() / (RAND_MAX + 1);
}

class Rocket {
	public:
		Rocket() {
			surface = SDL_LoadBMP(ROCKET);
			rect.y = WINDOW_HEIGHT - ROCKET_HEIGHT - ROCKET_SHIFT;
			rect.w = ROCKET_WIDTH;
			rect.h = ROCKET_HEIGHT;
			press = false;
		}
		
		void init() {
			rect.x = WINDOW_WIDTH / 4 - ROCKET_WIDTH / 2 + coin_flip() * WINDOW_WIDTH / 2;
		}
		
		void update(SDL_Surface* display) {
			if (SDL_GetKeyboardState(NULL)[MOVE]) {
				if (!press) {
					if (rect.x - (WINDOW_WIDTH / 4 - ROCKET_WIDTH / 2)) {
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
			
			SDL_BlitSurface(surface, NULL, display, &rect);
		}
		
		SDL_Rect* get_rect() {
			return &rect;
		}
			
	private:
		SDL_Surface* surface;
		SDL_Rect rect;
		bool press;
};

class Aster {
	public:
		Aster() {
			surface = SDL_LoadBMP(ASTER);
			rect.w = ASTER_WIDTH;
			rect.h = ASTER_HEIGHT;
		}
		
		void init(int score) {
			pos[0] = WINDOW_WIDTH / 4 - ASTER_WIDTH / 2 + coin_flip() * WINDOW_WIDTH / 2;
			pos[1] = -ASTER_HEIGHT;
			set_rect();
			
			vel = get_vel(score);
		}
		
		bool update(Rocket rocket, int* score, SDL_Surface* display) {
			if (pos[1] >= WINDOW_HEIGHT) {
				init(++*score);
			}
			
			pos[1] += vel;
			set_rect();
			
			SDL_BlitSurface(surface, NULL, display, &rect);
			
			return SDL_HasIntersection(rocket.get_rect(), &rect);
		}
	
	private:
		void set_rect() {
			rect.x = pos[0];
			rect.y = pos[1];
		}
		
		double get_vel(int score) {
			return BASE_VEL + VEL_GRAD * score;
		}
		
		SDL_Surface* surface;
		SDL_Rect rect;
		double pos[2];
		double vel;
};

int main(int argc, char** argv) {
	srand(time(NULL));
	
	SDL_Window* window = SDL_CreateWindow(
		TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	
	Rocket rocket;
	Aster aster;
	
	bool quit = false;
	
	printf("Space to move, r to reset, esc to quit.\n");
	
	while (!quit) {
		int score = 0;
		bool end = false;
		
		rocket.init();
		aster.init(score);
		
		while (!quit && !end) {
			quit = SDL_GetKeyboardState(NULL)[QUIT];
			end = SDL_GetKeyboardState(NULL)[RESET];
			
			rocket.update(display);
			
			if (aster.update(rocket, &score, display)) {
				printf("Score: %d\n", score);
				
				while (!quit && !end) {
					quit = SDL_GetKeyboardState(NULL)[QUIT];
					end = SDL_GetKeyboardState(NULL)[RESET];
					SDL_PumpEvents();
				}
			}
			
			SDL_UpdateWindowSurface(window);
			SDL_PumpEvents();
			
			SDL_FillRect(display, NULL, SDL_MapRGB(display->format, BG_R, BG_G, BG_B));;
		}
		
		while (SDL_GetKeyboardState(NULL)[RESET]) {
			SDL_PumpEvents();
		}
	}
}