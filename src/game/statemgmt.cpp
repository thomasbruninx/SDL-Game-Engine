#include "statemgmt.hpp"

namespace Game {
	std::stack<GameState*> states;

	/*************************************************
	* GAME STATE MANAGEMENT                          *
	*************************************************/

	void pushState(GameState* state) {
		states.push(state);
	}

	GameState* popState() {
		GameState* gsp = peekState();
		states.pop();
		return gsp;
	}

	GameState* swapState(GameState* state) {
		GameState* gsp = nullptr;
		if (!states.empty())
			gsp = popState();
		pushState(state);

		return gsp;
	}

	GameState* peekState() {
		if (states.empty()) return nullptr;
		return states.top();
	}

}

