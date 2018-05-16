#ifndef _THREADING_HPP_
#define _THREADING_HPP_

#include <vector>

#include "engine.hpp"

namespace Engine {
	namespace Threading {

		/*************************************************
		* HANDLING SDL MUTEXES                           *
		*************************************************/

		// Creates SDL mutexes, makes sure they're destoryed at the end
		typedef struct MutexFactory {
			SDL_mutex* createMutex() {
				mutexes.push_back(SDL_CreateMutex());
				return mutexes.back();
			}

			~MutexFactory() {
				for (size_t i = 0; i < mutexes.size(); i++)
					SDL_DestroyMutex(mutexes[i]);
			}

			private:

			std::vector<SDL_mutex*> mutexes;
		} MutexFactory_t;

		extern MutexFactory mutexFactory;

		typedef struct Mutex {
			SDL_mutex** m;

			Mutex(SDL_mutex*& mutex) {
				m = &mutex;
				SDL_mutexP(*m);
			}

			~Mutex() {
				SDL_mutexV(*m);
			}
		} Mutex_t;

	}
}

#endif

