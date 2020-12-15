#include <iostream>
#include "sdlandnet.hpp"

#define TOTAL 4

struct Data {
	Display* display;
	int index;
	int total;
};

int fill(void* d) {
	Data data = *static_cast<Data*>(d);
	Sprite& sprite = data.display->get_sprite();
	int width = sprite.get_width();
	int height = sprite.get_height();
	
	for (int i = 0; i < width; i++) {
		if (i % data.total == data.index) {
			for (int j = 0; j < height; j++) {
				Rectangle rectangle(i, j, 1, 1);
				sprite.fill(rectangle, 0x7f * i / width + 0x7f * j / height);
			}
		}
	}
	
	return 0;
}

int main(int argc, char** argv) {
	System::initialise(SDL_INIT_VIDEO, false);
	
	{
		Display display(0, 0);
		display.get_sprite().fill(BLACK);
		display.update();
		
		Data data[TOTAL];
		
		for (int i = 0; i < TOTAL; i++) {
			data[i].display = &display;
			data[i].index = i;
			data[i].total = TOTAL;
		}
		
		std::unique_ptr<Thread> threads[TOTAL];
		
		double start = Timer::time();
		
		for (int i = 0; i < TOTAL; i++) {
			threads[i] = std::make_unique<Thread>(fill, data + i);
		}
		
		for (int i = 0; i < TOTAL; i++) {
			threads[i]->wait();
		}
		
		display.update();
		
		std::cout << "Time: " << Timer::time() - start << "s\n";
		
		while (!Events::press(SDL_SCANCODE_ESCAPE)) {
			Events::update();
		}
	}
	
	System::terminate();
	
	return 0;
}