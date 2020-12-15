#include <SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define DELAY 5000

int main(int argc, char** argv) {
	SDL_Window* window = SDL_CreateWindow(
		"SDL Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
	);
	SDL_Surface* display = SDL_GetWindowSurface(window);
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(DELAY);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}