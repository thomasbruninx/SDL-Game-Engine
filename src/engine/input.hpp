#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include <map>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "engine.hpp"

namespace Engine {
	namespace Input {
		extern std::map<int, bool> keysPressed;
		extern uint8_t* keysIn;

		/*************************************************
		* KEYBOARD FUNCTIONS                             *
		*************************************************/
		// Warning! use SDL_SCANCODE's not SDL_KEYCODE's https://wiki.libsdl.org/SDL_Scancode

		bool keyDown(int key);
		bool keyPressed(int key);
		void readKeys();
	
		/*************************************************
		* MOUSE FUNCTIONS                                *
		*************************************************/

		void getMouseState(int& mouseX, int& mouseY);
		void getMouseState(int& mouseX, int& mouseY, bool& LMB, bool& RMB);

	}
}

#endif

