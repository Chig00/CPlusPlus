#include <iostream>
#include <string>
#include <SDL.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900
#define DELAY 5000

int main(int argc, char** argv) {
	std::cout << "Image name: ";
	std::string name;
	std::cin >> name;
	
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow(
		"Image Displayer by Chigozie Agomo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	SDL_Surface* image = SDL_LoadBMP(name.c_str());

	SDL_BlitSurface(image, NULL, display, NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(DELAY);

	SDL_FreeSurface(display);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}