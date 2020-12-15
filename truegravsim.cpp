#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <SDL.h>

const char* TITLE = "True Gravity Simulator by Chigozie Agomo";
const int WINDOW_W = 800;
const int WINDOW_H = 800;
const int BG_R = 0;
const int BG_G = 0;
const int BG_B = 0;
const int PARTICLE_W = 1;
const int PARTICLE_H = 1;
const double GRAVITY = 6.674e-11;
const double TRACE_MOD = 0.2;
const int QUIT = SDL_SCANCODE_ESCAPE;

struct Particle {
	Particle() {
		rect.w = PARTICLE_W;
		rect.h = PARTICLE_H;
		set_colour();
		count++;
	}
	
	void set_colour() {
		r = 0;
		g = 0;
		b = 0;
		
		switch (count % 6) {
			case 0:
				r = 255;
				break;
				
			case 1:
				b = 255;
				break;
				
			case 2:
				g = 255;
				break;
				
			case 3:
				r = 255;
				g = 255;
				break;
				
			case 4:
				r = 255;
				b = 255;
				break;
				
			case 5:
				g = 255;
				b = 255;
				break;
		}
	}
	
	set(double a, double b, double c, double d, double e) {
		pos_x = WINDOW_W / 2 + a;
		pos_y = WINDOW_H / 2 - b;
		vel_x = c;
		vel_y = -d;
		mass = e;
		fix_rect();
	}
	
	void fix_rect() {
		rect.x = pos_x - rect.w / 2;
		rect.y = pos_y - rect.h / 2;
	}
	
	void accelerate(std::vector<Particle> particles, int self, int count) {
		for (int i = 0; i < count; i++) {
			if (i == self) {
				continue;
			}
			
			double acc = GRAVITY * particles[i].mass / (pow(particles[i].pos_x - pos_x, 2) + pow(particles[i].pos_y - pos_y, 2));
			double ang = atan2(particles[i].pos_y - pos_y, particles[i].pos_y - pos_x);
			vel_x += acc * cos(ang);
			vel_y += acc * sin(ang);
		}
	}
	
	void move(SDL_Surface* display) {
		pos_x += vel_x;
		pos_y += vel_y;
		fix_rect();
		SDL_FillRect(display, &rect, SDL_MapRGB(display->format, r, g, b));
	}
	
	void trace(SDL_Surface* display) {
		SDL_FillRect(display, &rect, SDL_MapRGB(display->format, r * TRACE_MOD, g * TRACE_MOD, b * TRACE_MOD));
	}
	
	static int count;
	
	SDL_Rect rect;
	int r;
	int g;
	int b;
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	double mass;
};

int Particle::count = 0;

int main(int argc, char** argv) {
	int count = 0;
	std::cout << "Number of particles: ";
	std::cin >> count;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	if (count < 1) {
		std::cout << "Invalid particle count\n";
		return -1;
	}
	
	std::vector<double> values (5 * count);
	
	for (int i = 0; i < count; i++) {
		std::cout << "\nParticle " << i + 1 << '\n'
		          << "    Co-ordinates: ";
		std::cin >> values[5 * i] >> values[5 * i + 1];
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "    Rectangular Velocity: ";
		std::cin >> values[5 * i + 2] >> values[5 * i + 3];
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "    Mass: ";
		std::cin >> values[5 * i + 4];
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	SDL_Window* window = SDL_CreateWindow(
		TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, BG_R, BG_G, BG_B));
	
	std::vector<Particle> particles (count);
	
	for (int i = 0; i < count; i++) {
		particles[i].set(values[5 * i], values[5 * i + 1], values[5 * i + 2], values[5 * i + 3], values[5 * i + 4]);
	}
	
	while (!SDL_GetKeyboardState(NULL)[QUIT]) {
		for (int i = 0; i < count; i++) {
			particles[i].accelerate(particles, i, count);
		}
		
		for (int i = 0; i < count; i++) {
			particles[i].move(display);
		}
		
		SDL_UpdateWindowSurface(window);
		
		for (int i = 0; i < count; i++) {
			particles[i].trace(display);
		}
		
		SDL_PumpEvents();
	}
}