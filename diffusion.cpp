#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <SDL.h>

#define TITLE "Diffusion by Chigozie Agomo"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define BACKGROUND_R 0
#define BACKGROUND_G 0
#define BACKGROUND_B 0
#define PARTICLE_COUNT 5000
#define PARTICLE_WIDTH 1
#define PARTICLE_HEIGHT 1
#define PARTICLE_SPEED 0.2
#define PARTICLE_A_SIDE 0
#define PARTICLE_A_COLOUR_R 255
#define PARTICLE_A_COLOUR_G 0
#define PARTICLE_A_COLOUR_B 0
#define PARTICLE_B_SIDE 1
#define PARTICLE_B_COLOUR_R 0
#define PARTICLE_B_COLOUR_G 0
#define PARTICLE_B_COLOUR_B 255

int rand_int(int low, int high) {
	return low + (high - low + 1) * rand() / (RAND_MAX + 1);
}

class Particle {
	public:
		void update(SDL_Surface* display) {
			position[0] += velocity[0];
			position[1] += velocity[1];
			rect.x = position[0];
			rect.y = position[1];

			SDL_FillRect(display, &rect, SDL_MapRGB(display->format, colour[0], colour[1], colour[2]));

			if (rect.x < 0 || rect.x + rect.w > WINDOW_WIDTH) {
				velocity[0] = -velocity[0];
			}
			if (rect.y < 0 || rect.y + rect.h > WINDOW_HEIGHT) {
				velocity[1] = -velocity[1];
			}
		}
		
		int get_side() {
			return rect.x / (WINDOW_WIDTH / 2);
		}

	protected:
		void construct(int r, int g, int b, int side) {
			rect.x = side * WINDOW_WIDTH / 2 + rand_int(0, WINDOW_WIDTH / 2 - 1);
			rect.y = rand_int(0, WINDOW_HEIGHT);
			rect.w = PARTICLE_WIDTH;
			rect.h = PARTICLE_HEIGHT;
			colour[0] = r;
			colour[1] = g;
			colour[2] = b;
			position[0] = rect.x;
			position[1] = rect.y;
			double angle = get_angle();
			velocity[0] = PARTICLE_SPEED * cos(angle);
			velocity[1] = PARTICLE_SPEED * sin(angle);
		}

	private:
		double get_angle() {
			return 2 * acos(-1) * rand() / (RAND_MAX + 1);
		}
	
		SDL_Rect rect;
		int colour[3];
		double position[2];
		double velocity[2];
};

class ParticleA: public Particle {
	public:
		ParticleA() {
			construct(PARTICLE_A_COLOUR_R, PARTICLE_A_COLOUR_G, PARTICLE_A_COLOUR_B, PARTICLE_A_SIDE);
		}
};

class ParticleB: public Particle {
	public:
		ParticleB() {
			construct(PARTICLE_B_COLOUR_R, PARTICLE_B_COLOUR_G, PARTICLE_B_COLOUR_B, PARTICLE_B_SIDE);
		}
};

class ParticleCollection {
	public:
		void update(SDL_Surface* display) {
			for (int i = 0; i < PARTICLE_COUNT / 2; i++) {
				particle_a_array[i].update(display);
				particle_b_array[i].update(display);
			}
		}

		void tally() {
			int al = 0;
			int ar = 0;
			int bl = 0;
			int br = 0;
			for (int i = 0; i < PARTICLE_COUNT / 2; i++) {
				if (particle_a_array[i].get_side()) {
					ar++;
				}
				else {
					al++;
				}

				if (particle_b_array[i].get_side()) {
					br++;
				}
				else {
					bl++;
				}
			}

			printf("Left:\n%d Particle As\n%d Particle Bs\n\n", al, bl);
			printf("Right:\n%d Particle As\n%d Particle Bs\n\n\n", ar, br);
		}

	private:
		ParticleA particle_a_array[PARTICLE_COUNT / 2];
		ParticleB particle_b_array[PARTICLE_COUNT / 2];
};

int main(int argc, char** argv) {
	srand(time(NULL));

	SDL_Window* window = SDL_CreateWindow(
		TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);

	bool quit = false;
	bool r = false;
	
	while (!quit) {
		ParticleCollection particles;
		particles.tally();

		bool space = false;

		while (true) {
			SDL_FillRect(display, NULL, SDL_MapRGB(display->format, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));
			particles.update(display);

			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]) {
				if (!space) {
					particles.tally();
					space = true;
				}
			}
			else if (space) {
				space = false;
			}
			
			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_R]) {
				if (!r) {
					r = true;
					break;
				}
			}
			else if (r) {
				r = false;
			}
			
			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE]) {
				quit = true;
				break;
			}

			SDL_UpdateWindowSurface(window);
			SDL_PumpEvents();
		}
	}
}