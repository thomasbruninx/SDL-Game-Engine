#ifndef _DEMO_HPP_
#define _DEMO_HPP_

#include "../engine/engine_include.hpp"
#include "statemgmt.hpp"

namespace Game {

	class Demo : public GameState {
		int i;
		bool inc, disp;

	public:
		virtual void draw(const float frameTime);
		virtual void update(const float frameTime);

		Demo();
		~Demo();
	};
	
}

#endif
