#pragma once

#include <ctime>
#include <SDL.h>

const int SURFACE_DEPTH = 32;

const Uint32 SURFACE_MASKS[2][4] = {
	{
		0xff000000,
		0x00ff0000,
		0x0000ff00,
		0x000000ff
	},
	{
		0x000000ff,
		0x0000ff00,
		0x00ff0000,
		0xff000000
	}
};

/* Gives a relative time in seconds
 */
double get_time() {
	return (double)clock() / CLOCKS_PER_SEC;
}

/* Checks for a key press
 */
bool key_press(int key) {
	return SDL_GetKeyboardState(NULL)[key];
}

/* Checks for a key press and waits until its release
 */
bool key_release(int key) {
	// The key press is assumed to be false
	bool press = false;

	// If the key was pressed,
	if (SDL_GetKeyboardState(NULL)[key]) {
		// the release is waited for
		while (SDL_GetKeyboardState(NULL)[key]) {
			SDL_PumpEvents();
		}

		// and the press is set to true
		press = true;
	}

	// The key press status is returned
	return press;
}

/* Returns the button status of the mouse for a given button
 */
bool click(int button) {
	return SDL_GetMouseState(NULL, NULL) & button;
}

/* Returns the button status of the mouse for a given button
   Also modifies the value of the given integers to match
	 the mouse's co-ordinates
 */
bool click(int button, int* x, int* y) {
	return SDL_GetMouseState(x, y) & button;
}

/* A wrapper class for the window and its surface
 */
class Display {
public:
	/* Sets the display mode (display's height and width)
	   Creates a window and stores its surface
	 */
	Display(const char* title) {
		SDL_GetDesktopDisplayMode(0, &display_mode);

		window = SDL_CreateWindow(
			title, 0, 0,
			display_mode.w, display_mode.h, SDL_WINDOW_FULLSCREEN
		);

		window_surface = SDL_GetWindowSurface(window);
	}

	/* Destroys the window
	 */
	~Display() {
		SDL_DestroyWindow(window);
	}

	/* Returns the width of the window
	 */
	int get_width() {
		return window_surface->w;
	}

	/* Returns the height of the window
	 */
	int get_height() {
		return window_surface->h;
	}

	/* Updates the window's surface
	 */
	void update() {
		SDL_UpdateWindowSurface(window);
	}

	/* Returns the window's surface
	 */
	SDL_Surface* get_surface() {
		return window_surface;
	}

	/* Fills the window with a single colour
	 */
	void fill(int r, int g, int b) {
		SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, r, g, b));
	}

private:
	SDL_DisplayMode display_mode; // Display dimensions
	SDL_Window* window; // The window
	SDL_Surface* window_surface; // The window's surface
};

/* A wrapper class for surfaces
 */
class Surface {
public:
	/* Loads the surface and fits it to the given dimenions
	   Initialises a rectangle for the surface
	 */
	Surface(const char* source, int x, int y, int width, int height) {
		SDL_Surface* raw_surface = SDL_LoadBMP(source);

		surface = SDL_CreateRGBSurface(
			0, width, height, SURFACE_DEPTH,
			SURFACE_MASKS[byte_order][0], SURFACE_MASKS[byte_order][1],
			SURFACE_MASKS[byte_order][2], SURFACE_MASKS[byte_order][3]
		);

		SDL_BlitScaled(raw_surface, NULL, surface, NULL);
		SDL_FreeSurface(raw_surface);

		rect.x = x;
		rect.y = y;
		rect.w = width;
		rect.h = height;
	}

	/* Alternative constructor for use with ratios
	   Takes in the display's width and height in addition to the ratios as arguments
	 */
	Surface(const char* source, int dw, int dh, double x, double y, double w, double h) {
		int width = w * dw;
		int height = h * dh;
		int rx = x * dw - width / 2;
		int ry = y * dh - height / 2;

		SDL_Surface* raw_surface = SDL_LoadBMP(source);

		surface = SDL_CreateRGBSurface(
			0, width, height, SURFACE_DEPTH,
			SURFACE_MASKS[byte_order][0], SURFACE_MASKS[byte_order][1],
			SURFACE_MASKS[byte_order][2], SURFACE_MASKS[byte_order][3]
		);

		SDL_BlitScaled(raw_surface, NULL, surface, NULL);
		SDL_FreeSurface(raw_surface);

		rect.x = rx;
		rect.y = ry;
		rect.w = width;
		rect.h = height;
	}

	/* Constructs a surface filled in with a single colour
	 */
	Surface(int x, int y, int width, int height, int r, int g, int b) {
		surface = SDL_CreateRGBSurface(
			0, width, height, SURFACE_DEPTH,
			SURFACE_MASKS[byte_order][0], SURFACE_MASKS[byte_order][1],
			SURFACE_MASKS[byte_order][2], SURFACE_MASKS[byte_order][3]
		);

		rect.x = x;
		rect.y = y;
		rect.w = width;
		rect.h = height;

		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
	}

	/* Constructs a surface filled in with a single colour
	   Uses ratios of the given dimensions
	 */
	Surface(int dw, int dh, double x, double y, double w, double h, int r, int g, int b) {
		int width = w * dw;
		int height = h * dh;
		int rx = x * dw - width / 2;
		int ry = y * dh - height / 2;

		surface = SDL_CreateRGBSurface(
			0, width, height, SURFACE_DEPTH,
			SURFACE_MASKS[byte_order][0], SURFACE_MASKS[byte_order][1],
			SURFACE_MASKS[byte_order][2], SURFACE_MASKS[byte_order][3]
		);

		rect.x = rx;
		rect.y = ry;
		rect.w = width;
		rect.h = height;

		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
	}

	/* Frees the surface associated with the object
	 */
	~Surface() {
		SDL_FreeSurface(surface);
	}

	/* Returns true if the point in the surface's rect
	 */
	bool in_rect(const SDL_Point* point) {
		return SDL_PointInRect(point, &rect);
	}

	/* Blits the surface to another
	 */
	void blit(SDL_Surface* surf) {
		SDL_BlitSurface(surface, NULL, surf, &rect);
	}

	/* Sets the rectangle's co-ordinates and then blits
	 */
	void blit(SDL_Surface* surf, double x, double y) {
		rect.x = x * surf->w - rect.w / 2;
		rect.y = y * surf->h - rect.h / 2;

		blit(surf);
	}

	/* Sets the rectangle's x co-ordinate and then blits
	 */
	void blit_x(SDL_Surface* surf, double x) {
		rect.x = x * surf->w - rect.w / 2;

		blit(surf);
	}

	/* Sets the rectangle's y co-ordinate and then blits
	 */
	void blit_y(SDL_Surface* surf, double y) {
		rect.y = y * surf->h - rect.h / 2;

		blit(surf);
	}

	/* Sets the rectangle's co-ordinates exactly before blitting
	 */
	void blit(SDL_Surface* surf, int x, int y) {
		rect.x = x;
		rect.y = y;
		blit(surf);
	}

	SDL_Surface* data() {
		return surface;
	}

	SDL_Rect get_rect() {
		return rect;
	}

private:
	static const int byte_order = SDL_BYTEORDER != SDL_BIG_ENDIAN; // Byte ordering
	SDL_Surface* surface; // Contains the pixel data for blitting
	SDL_Rect rect; // The rectangle showing the position and size of the surface
};

/* Class that deals with queuing the music
 */
class MusicQueuer {
public:
	/* Loads the music, plays it, and stores the time of playing
	 */
	MusicQueuer(const char* source, int length) {
		SDL_LoadWAV(source, &audio_spec, &audio_buffer, &audio_length);
		audio_device = SDL_OpenAudioDevice(NULL, false, &audio_spec, NULL, 0);
		SDL_PauseAudioDevice(audio_device, false);
		SDL_QueueAudio(audio_device, audio_buffer, audio_length);
		double last_queue = get_time();
		song_length = length;
	}

	/* Closes the audio device and frees the song
	 */
	~MusicQueuer() {
		SDL_CloseAudioDevice(audio_device);
		SDL_FreeWAV(audio_buffer);
	}

	/* Requeues the song if it is time
	 */
	void requeue() {
		if (get_time() > last_queue + song_length) {
			SDL_QueueAudio(audio_device, audio_buffer, audio_length);
			last_queue = get_time();
		}
	}

private:
	SDL_AudioSpec audio_spec;
	Uint8* audio_buffer;
	Uint32 audio_length;
	SDL_AudioDeviceID audio_device;
	double last_queue;
	int song_length;
};