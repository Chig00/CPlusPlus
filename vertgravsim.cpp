#include <iostream>
#include <limits>
#include <cmath>
#include <SDL.h>

const char* TITLE = "Vertical Gravity Simulator by Chigozie Agomo";
const int WINDOW_W = 800;
const int WINDOW_H = 800;
const int PARTICLE_W = 1;
const int PARTICLE_H = 1;
const int R = 255;
const int G = 255;
const int B = 255;
const int QUIT = SDL_SCANCODE_ESCAPE;
const double PI = acos(-1);

struct Particle {
	Particle(double v, double a, double g) {
		rect.w = PARTICLE_W;
		rect.h = PARTICLE_H;
		pos_x = WINDOW_W / 2;
		pos_y = WINDOW_H / 2;
		vel_x = v * cos(radian_conv(a));
		vel_y = -v * sin(radian_conv(a));
		grav_acc = g;
		fix_rect();
	}
	
	void fix_rect() {
		rect.x = pos_x - rect.w / 2;
		rect.y = pos_y - rect.h / 2;
	}
	
	bool onscreen() {
		return !(rect.x + rect.w < 0 || rect.x > WINDOW_W || rect.y + rect.h < 0 || rect.y > WINDOW_H);
	}
	
	void move(SDL_Window* window, SDL_Surface* display) {
		pos_x += vel_x;
		pos_y += vel_y;
		vel_y += grav_acc;
		fix_rect();
		SDL_FillRect(display, &rect, SDL_MapRGB(display->format, R, G, B));
		SDL_UpdateWindowSurface(window);
	}

	static double radian_conv(double angle) {
		return angle * PI / 180;
	}
	
	SDL_Rect rect;
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	double grav_acc;
};

int main(int argc, char** argv) {
	double v;
	double a;
	double g;
	
	std::cout << "Initial Velocity: ";
	std::cin >> v;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	std::cout << "Initial Angle: ";
	std::cin >> a;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	std::cout << "Gravitational Acceleration: ";
	std::cin >> g;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	SDL_Window* window = SDL_CreateWindow(
		TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0, 0, 0));
	
	Particle particle (v, a, g);
	
	while (particle.onscreen()) {
		particle.move(window, display);
	}
	
	while (!SDL_GetKeyboardState(NULL)[QUIT]) {
		SDL_PumpEvents();
	}
}