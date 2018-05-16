#ifndef _AUDIO_HPP_
#define _AUDIO_HPP_

#include <vector>

#include "engine.hpp"
#include "threading.hpp"

namespace Engine {
	namespace Audio {

		/*************************************************
		* AUDIO FUNCTIONS                                *
		*************************************************/

		int audioOpen(int samplerate, int framesize);
		void audioClose();
		int audioReOpen();

		void audioPushSamples(const std::vector<double>& samples, size_t pos, size_t end);
		size_t audioSamplesShortage();
		size_t audioSamplesOverflow();
		void audioSetBufferSamplesRange(size_t min_samples, size_t max_samples);

		void audioPlay(const std::vector<double>& samples);

		void audioSetMode(int mode);
		void audioSetVolume(double volume);

	}
}

#endif

