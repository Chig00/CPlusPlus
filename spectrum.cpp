#include <iostream>
#include "sdlandnet.hpp"

// Used to calculate the drawn square's size.
constexpr int RATIO = 5;

// The colours used and their order.
constexpr Sprite::Colour COLOURS[] = {
	Sprite::RED,
	Sprite::YELLOW,
	Sprite::GREEN,
	Sprite::CYAN,
	Sprite::BLUE,
	Sprite::MAGENTA
};

// The number of colours used.
constexpr int COLOUR_COUNT = 6;

/**
 * A simple program that allows the user to
 *   colour in the display in different colours.
 */
int main(int argc, char** argv) {
	// The system is initialised for video.
	System::initialise();
	
	// The version of the SDL and Net utilities library is printed.
	std::cout
		<< "\nPowered by:\n"
		<< System::info()
		<< std::endl
	;
	
	{
		// A fullscreen display is initialised and filled in black.
		Display display;
		display.get_sprite().fill();
		display.update();
		
		// The size of the drawn square.
		int size =
			display.get_sprite().get_width()
			< display.get_sprite().get_height()
			? display.get_sprite().get_width() / RATIO
			: display.get_sprite().get_height() / RATIO
		;
		
		// Stores the position of the mouse.
		Point mouse;
		
		// Determines which colour should be used.
		int index = 0;
		
		// The program ends when the user presses escape.
		while (!Events::press(Events::ESCAPE)) {
			// A mouse click draws to the display.
			if (Events::click()) {
				// The colour changes when the mouse click is released.
				while (mouse.click()) {
					display.get_sprite().fill(
						Rectangle(
							mouse.get_x() - size / 2,
							mouse.get_y() - size / 2,
							size,
							size
						),
						COLOURS[index]
					);
					display.update();
					Events::update();
				}
				
				index = (index + 1) % COLOUR_COUNT;
			}
			
			Events::update();
		}
	}
	
	// The system is terminated.
	System::terminate();
	return 0;
}