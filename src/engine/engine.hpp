#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "input.hpp"

namespace Engine {
	// Info: For more information on using SDL2 check: http://lazyfoo.net/tutorials/SDL/ 
	//                                              or http://lodev.org/cgtutor/
	//                                              or http://www.willusher.io/pages/sdl2/

	extern int screenWidth;
	extern int screenHeight;
	extern bool screenFullscreen;
	extern SDL_Window* gWindow;
	extern SDL_Surface* gScreenSurface;
	extern SDL_Event event;

	bool engineInit(int width = 640, int height = 480, const char* title = "", bool fullscreen = false);
	void engineClose();

	/*************************************************
	* MISC ENGINE FUNCTIONS                          *
	*************************************************/

	void sleep();
	void sleep(double sec);
	void waitFrame(double oldTime, double duration);
	bool done(bool quitIfEsc = false, bool delay = true);
	void end();
	unsigned long getTicks();
	inline double getTime();
	void changeResolution(int w, int h, bool fullscreen = false);
}

#endif



