#ifndef _STATEMGMT_HPP_
#define _STATEMGMT_HPP_

#include <stack>

#include "../engine/engine_include.hpp"

namespace Game {

	/*************************************************
	* GAME STATE MANAGEMENT                          *
	*************************************************/

	class GameState {
	public:
		virtual void draw(const float frameTime) = 0;
		virtual void update(const float frameTime) = 0;

		GameState() {}
		virtual ~GameState() {}
	};

	void pushState(GameState* state);
	GameState* popState();
	GameState* swapState(GameState* state);
	GameState* peekState();

}

#endif

