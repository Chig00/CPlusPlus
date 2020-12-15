#include <iostream>
#include "sdlandnet.hpp"

// The number of colours used.
constexpr int COLOUR_COUNT = 9;

// Determines how the multiplier increases over time.
constexpr double MULTIPLIER = 0.25;

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
		
		
		// The initial size of the drawn square.
		double size = 
			display.get_sprite().get_width()
			< display.get_sprite().get_height()
			? display.get_sprite().get_width()
			: display.get_sprite().get_height()
		;
		
		// Stores the position of the mouse, when it is clicked.
		Point initial;
		// Stores the position of the mouse.
		Point mouse;
		
		// Determines which colour should be used.
		int colour = 1;
		
		// The program ends when the user presses escape.
		while (!Events::press(Events::ESCAPE)) {
			// A mouse click draws to the display.
			if (initial.click()) {
				// Increases when the mouse button is held in the same place.
				double multiplier = 0;
				bool held = true;
				double start = Timer::time();
				
				// The colour changes when the mouse click is released.
				while (mouse.click()) {
					// The display is drawn to.
					display.get_sprite().fill(
						Rectangle(
							mouse.get_x() - multiplier * size / 2,
							mouse.get_y() - multiplier * size / 2,
							multiplier * size,
							multiplier * size
						),
						static_cast<Sprite::Colour>(colour)
					);
					
					// The rectangle no longer inflates if the mouse was moved.
					if (mouse != initial) {
						held = false;
					}
					
					// If the mouse hasn't moved since the click,
					//   the rectangle's size increases.
					if (held) {
						multiplier = MULTIPLIER * (Timer::time() - start);
					}
					
					// The display and the events are updated.
					display.update();
					Events::update();
				}
				
				// The next colour is cycled to.
				colour = (colour + 1) % COLOUR_COUNT;
			}
			
			// The events are updated.
			Events::update();
		}
	}
	
	// The system is terminated.
	System::terminate();
	return 0;
}