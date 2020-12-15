#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <SDL.h>

const int WIN_W = 800;
const int WIN_H = 800;
const double FULL_TURN = acos(-1) * 2;
const int MARKER_W = 1;
const int MARKER_H = 1;
const char* TITLE = "Spiral Maker by Chigozie Agomo";
const int QUIT = SDL_SCANCODE_ESCAPE;

struct Marker {
	Marker(double direction, int count) {
		rect.w = MARKER_W;
		rect.h = MARKER_H;
		pos_x = WIN_W / 2;
		pos_y = WIN_H / 2;
		vel_x = cos(direction * FULL_TURN);
		vel_y = sin(direction * FULL_TURN);
		fix_rect();
		set_colour(count % 6);
	}
	
	void fix_rect() {
		rect.x = pos_x;
		rect.y = pos_y;
	}
	
	void set_colour(int code) {
		if (code == 1) {
			r = 255;
			g = 0;
			b = 0;
		}
		
		else if (code == 2) {
			r = 255;
			g = 255;
			b = 0;
		}
		
		else if (code == 3) {
			r = 0;
			g = 255;
			b = 0;
		}
		
		else if (code == 4) {
			r = 0;
			g = 255;
			b = 255;
		}
		
		else if (code == 5) {
			r = 0;
			g = 0;
			b = 255;
		}
		
		else {
			r = 255;
			g = 0;
			b = 255;
		}
	}
	
	void move(SDL_Surface* display) {
		pos_x += vel_x;
		pos_y += vel_y;
		fix_rect();
		
		SDL_FillRect(display, &rect, SDL_MapRGB(display->format, r, g, b));
	}
	
	SDL_Rect rect;
	double pos_x;
	double pos_y;
	double vel_x;
	double vel_y;
	int r;
	int g;
	int b;
};

int main(int argc, char** argv) {
	std::cout << "Seed (number from 0 to 1): ";
	double seed;
	std::cin >> seed;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	std::vector<Marker> markers;
	SDL_Window* window = SDL_CreateWindow(
		TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_W, WIN_H, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	bool quit = false;
	int count = 0;
	
	while (!quit) {
		markers.push_back(Marker (markers.size() * seed, count));
		count++;
		
		SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0, 0, 0));
		
		for (int j = 0; j < markers.size(); j++) {
			markers[j].move(display);
			
			if (SDL_GetKeyboardState(NULL)[QUIT]) {
				quit = true;
			}
		}
		
		SDL_UpdateWindowSurface(window);
		SDL_PumpEvents();
	}
}