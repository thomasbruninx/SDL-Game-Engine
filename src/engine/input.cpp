#include "input.hpp"

namespace Engine {
	namespace Input {
		std::map<int, bool> keysPressed;
		uint8_t* keysIn;

		/*************************************************
		* KEYBOARD FUNCTIONS                             *
		*************************************************/

		// Check of key is held down, returns true as long as 
		// the key is down
		bool keyDown(int key) {
			return (keysIn[key] != 0);
		}

		// Check if key is pressed, returns true once until key 
		// has been up and is pressed again
		bool keyPressed(int key) {
			if (keysPressed.find(key) == keysPressed.end()) keysPressed[key] = false;
			if (keysIn[key]) {
				if (keysPressed[key] == false) {
					keysPressed[key] = true;
					return true;
				}
			} else {
				keysPressed[key] = false;
			}
			return false;
		}

		// Gives value of pressed key to keysIn, this variable
		// can be used anywhere to check input
		void readKeys() {
			SDL_PollEvent(&event);
			keysIn = (uint8_t*)SDL_GetKeyboardState(NULL);
		}

		/*************************************************
		* MOUSE FUNCTIONS                                *
		*************************************************/

		// Gets mouse position
		void getMouseState(int& mouseX, int& mouseY) {
			SDL_GetMouseState(&mouseX, &mouseY);
		}

		// Get mouse position and state of mouse buttons
		void getMouseState(int& mouseX, int& mouseY, bool& LMB, bool& RMB) {
			uint8_t mouse = SDL_GetMouseState(&mouseX, &mouseY);

			if (mouse & 1) LMB = true;
			else LMB = false;
			if (mouse & 4) RMB = true;
			else RMB = false;
		}


	}
}

