#include <iostream>
#include <limits>
#include <cmath>
#include <SDL.h>

const char* TITLE = "Radial Gravity Simulator by Chigozie Agomo";
const int WINDOW_W = 800;
const int WINDOW_H = 800;
const int PARTICLE_W = 1;
const int PARTICLE_H = 1;
const int QUIT = SDL_SCANCODE_ESCAPE;
const int R1 = 255;
const int G1 = 0;
const int B1 = 0;
const int R2 = 63;
const int G2 = 63;
const int B2 = 63;
const int R3 = 0;
const int G3 = 0;
const int B3 = 255;
const double GRAVITY = 6.674e-11;

struct Particle {
	Particle(double pos_x, double pos_y, double vel_x, double vel_y, double mass) {
		rect.w = PARTICLE_W;
		rect.h = PARTICLE_H;
		this->pos_x = WINDOW_W / 2 + pos_x;
		this->pos_y = WINDOW_H / 2 - pos_y;
		this->vel_x = vel_x;
		this->vel_y = -vel_y;
		this->mass = mass;
		fix_rect();
	}
	
	void fix_rect() {
		rect.x = pos_x - rect.w / 2;
		rect.y = pos_y - rect.h / 2;
	}
	
	void move(SDL_Window* window, SDL_Surface* display) {
		double acc = GRAVITY * mass / (pow(WINDOW_W / 2 - pos_x, 2) + pow(WINDOW_H / 2 - pos_y, 2));
		double ang = atan2(WINDOW_H / 2 - pos_y, WINDOW_W / 2 - pos_x);
		vel_x += acc * cos(ang);
		vel_y += acc * sin(ang);
		pos_x += vel_x;
		pos_y += vel_y;
		fix_rect();
		SDL_FillRect(display, &rect, SDL_MapRGB(display->format, R1, G1, B1));
		SDL_UpdateWindowSurface(window);
		SDL_FillRect(display, &rect, SDL_MapRGB(display->format, R2, G2, B2));
	}
	
	SDL_Rect rect;
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	double mass;
};

int main(int argc, char** argv) {
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	double mass;
	
	std::cout << "Co-ordinate Displacement: ";
	std::cin >> pos_x >> pos_y;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	std::cout << "Rectangular Velocity: ";
	std::cin >> vel_x >> vel_y;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	std::cout << "Centre's Mass: ";
	std::cin >> mass;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	SDL_Window* window = SDL_CreateWindow(
		TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	SDL_Rect rect;
	rect.x = WINDOW_W / 2;
	rect.y = WINDOW_H / 2;
	rect.w = PARTICLE_W;
	rect.h = PARTICLE_H;
	
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0, 0, 0));
	SDL_FillRect(display, &rect, SDL_MapRGB(display->format, R3, G3, B3));
	
	Particle particle (pos_x, pos_y, vel_x, vel_y, mass);
	
	while (true) {
		particle.move(window, display);
		
		if (SDL_GetKeyboardState(NULL)[QUIT]) {
			break;
		}
		
		SDL_PumpEvents();
	}
}