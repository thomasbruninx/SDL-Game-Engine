#include "engine.hpp"

namespace Engine {
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Event event = {0};

	int screenWidth = 0;
	int screenHeight = 0;
	bool screenFullscreen = false;

	// Initializes SDL and other engine components
	bool engineInit(int width, int height, const char* title, bool fullscreen) {
		screenWidth = width;
		screenHeight = height;
		gScreenSurface = NULL;
		gWindow = NULL;

		// Init SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

		// Create window
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) return false;

		if (fullscreen) {
			SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
			screenFullscreen = true;
		}

		gScreenSurface = SDL_GetWindowSurface(gWindow);

		return true;
	}

	// Shut down SDL, clean up memory
	void engineClose() {
		SDL_Quit();
	}

	/*************************************************
	* MISC ENGINE FUNCTIONS                          *
	*************************************************/

	// Pause execution until key is pressed
	void sleep() {
		bool done = false;
		SDL_PollEvent(&event);
		while (done == 0) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) end();
				if (event.type == SDL_KEYDOWN) done = true;
			}
			SDL_Delay(5); // Consumes less CPU power
		}
	}

	// Pause execution for set amount of time
	void sleep(double sec) {
		SDL_Delay(int(sec * 1000));
	}

	// (In seconds)
	void waitFrame(double oldTime, double duration) {
		float time = getTime();
		while (time - oldTime < duration) {
			time = getTime();
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT) end();
			/* CUT LATER */
			//Input::keysIn = SDL_GetKeyboardState(NULL);
			//if  (Input::keysIn[SDLK_ESCAPE]) end();
			/*************/
			SDL_Delay(5); // Consumes less CPU power
		}
	}

	// Returns true when window is closed or escape pressed,
	// Also handles everything that's needed per frame
	// (Warning! Don't put input code right before done(), SDL
	// may see the key as SDL_QUIT)
	bool done(bool quitIfEsc, bool delay) {
		if (delay) SDL_Delay(5); // Consumes less CPU power
		bool done = false;
		if (!SDL_PollEvent(&event)) return false;
		Input::readKeys();
		if (quitIfEsc && Input::keysIn[SDL_SCANCODE_ESCAPE]) done = true;
		if (event.type == SDL_QUIT) done = true;
		return done;
	}

	// End program execution
	void end() {
		engineClose();
		std::exit(1);
	}

	// 
	unsigned long getTicks() {
		return SDL_GetTicks();
	}

	// Get ticks in seconds
	inline double getTime() { 
		return getTicks() / 1000.0; 
	}

	// Change window resolution and set windowed or fullscreen
	void changeResolution(int w, int h, bool fullscreen) {
		// Set window resolution
		if (w > 0 && h > 0) {
			screenWidth = w;
			screenHeight = h;
			SDL_SetWindowSize(gWindow, screenWidth, screenHeight);
		}
		// Set fullscreen/windowed mode
		if (fullscreen) {
			SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
			screenFullscreen = true;
		} else {
			SDL_SetWindowFullscreen(gWindow, 0);
			screenFullscreen = false;
		}
		
		// Update surface
		gScreenSurface = SDL_GetWindowSurface(gWindow);
	}
}

