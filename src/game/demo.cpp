#include "demo.hpp"

namespace Game {

	void Demo::draw(const float frameTime) { 
		if (i >= 255) inc = false;
		else if (i <= 0) inc = true;
		
		if (inc) i++;
		else i--;
		
		for (int x = 0; x < screenWidth; x++) {
			for (int y = 0; y < screenHeight; y++) {
				setPixel(x, y, Graphics::ColorRGB(x / ceil(screenWidth/256.0f), y / ceil(screenHeight/256.0f), i));
			}
		}

		if (disp) Text::print("Hello World!", 0, 10);
	}

	void Demo::update(const float frameTime) {
		Input::readKeys();

		if (Input::keyPressed(SDL_SCANCODE_RETURN)) {
			disp = !disp;
		} else if (Input::keyPressed(SDL_SCANCODE_ESCAPE)) {
			GameState* st = popState();
			delete st;
		}
	}

	Demo::Demo() {
		i = 0;
		inc = disp = true;
	}

	Demo::~Demo() {

	}
			
}
