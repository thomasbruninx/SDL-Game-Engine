#include <string>
#include <cmath>

#include <SDL2/SDL.h>

#include "engine/engine_include.hpp"
#include "game/statemgmt.hpp"
#include "game/demo.hpp"

using namespace Engine;
using namespace Engine::Graphics;
using namespace Game;

#define DEFAULT_SCREEN_WIDTH 1024
#define DEFAULT_SCREEN_HEIGHT 768

int main(int argc, char** argv) {
	// Default settings
	int scrWidth = DEFAULT_SCREEN_WIDTH;
	int scrHeight = DEFAULT_SCREEN_HEIGHT;
	bool fullscreen = false;
	bool debug = false;
	bool dispFps = false;

	// TODO Read config file

	// Parse commandline arguments
	for (int i = 1; i < argc; i++) {
		if (strcmp("--screen", argv[i]) == 0 || strcmp("-s", argv[i]) == 0) {
			// Check if valid arguments are given
			scrWidth = strtol(argv[++i], NULL, 10);
			scrHeight = strtol(argv[++i], NULL, 10);
			if (scrWidth <= 0 || scrHeight <= 0) {
				scrWidth = DEFAULT_SCREEN_WIDTH;
				scrHeight = DEFAULT_SCREEN_HEIGHT;
			}
		} else if (strcmp("--fullscreen", argv[i]) == 0 || strcmp("-f", argv[i]) == 0) {
			// Fullscreen mode	
			fullscreen = true;
		} else if (strcmp("--windowed", argv[i]) == 0 || strcmp("-w", argv[i]) == 0) {
			// Windowed mode	
			fullscreen = false;
		} else if (strcmp("--debug", argv[i]) == 0 || strcmp("-d", argv[i]) == 0) {
			// Debug mode	
			debug = true;
		} else if (strcmp("--fps", argv[i]) == 0 || strcmp("-c", argv[i]) == 0) {
			// Display fps counter
			dispFps = true;
		}
	}

	// Init engine
	if (!engineInit(scrWidth, scrHeight, "Game", fullscreen)) exit(1);

	/****** INIT AND PUSH FIRST STATE HERE ******/
	pushState(new Game::Demo());
	/********************************************/

	float time = 0, prevTime = 0, frameTime = 0;
	GameState* currentState;

	// Main loop 
	while (!done() && (currentState = peekState()) != nullptr) {
		// Drawing
		clearScreen();
		currentState->draw(frameTime);
		updateScreen();

		// Calculate timing
		// (frametime = time frame drawing has taken in seconds)
		prevTime = time;
		time = getTicks();
		frameTime = (time - prevTime) / 1000.0;

		// Display FPS (if necessary)
		if (dispFps) Util::drawFpsCounter(frameTime);
		updateScreen();

		// Update logic
		currentState->update(frameTime);
	}

	// End of execution
	end();

	return 0;
}

