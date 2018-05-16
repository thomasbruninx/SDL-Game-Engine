#include "audio.hpp"

namespace Engine {
	namespace Audio {
		size_t audio_min_samples = 4096;	// Safety buffer to avoid clicking
		size_t audio_max_samples = 8192;	// Avoid too long queue

		double audio_volume = 1.0;
		int audio_mode = 2;					// 0 = off, 1 = full (volume ignored), 2 = volume controlled

		// Avoid the callback function and pushSamples function to be called
		// at the same time, the std:vector can be invalid if 2 threads change
		// it at the same time. This SDL_mutex eliminates that problem.
		SDL_mutex* audio_lock = Threading::mutexFactory.createMutex();

		std::vector<double> audio_data(audio_min_samples, 0);

		SDL_AudioSpec audiospec_wanted, audiospec_obtained;

		/*************************************************
		* AUDIO FUNCTIONS                                *
		*************************************************/

		void audioCallback(void*, uint8_t* stream, int len) {
			Threading::Mutex mutex(audio_lock);

			int dataLengthLeft = audio_data.size();

			// Only play if there's data left
			if (dataLengthLeft <= 0) return;

			// Always 16-bit, so always 2 bytes per sample, 
			// hence the amount of samples being len / 2
			int nsamples = len / 2;
			int fill_len = (nsamples < dataLengthLeft ? nsamples : dataLengthLeft);

			for (int i = 0; i < nsamples; i++) {
				if (i < fill_len) {
					int s = int(audio_data[i] * 32768);
					if (s < -32768) s = -32768;
					if (s > 32767) s = 32767;

					stream[i * 2] = uint8_t(s % 256);
					stream[i * 2 + 1] = uint8_t (s / 256);
				} else stream[i * 2] = stream[i * 2 + 1] = 0;
			}

			audio_data.erase(audio_data.begin(), audio_data.begin() + fill_len);
		}

		int audioOpen(int samplerate, int framesize) {
			// Set audio format
			audiospec_wanted.freq = samplerate;
			audiospec_wanted.format = AUDIO_S16;
			audiospec_wanted.channels = 1; // 1 = mono, 2 = stereo
			audiospec_wanted.samples = framesize;
			audiospec_wanted.callback = audioCallback;
			audiospec_wanted.userdata = NULL;

			// On linux, when using alsa and 44100 samples/second, the framesize (samples)
			// will be 940 instead of 1024. Resampled to 48000Hz, this gives back 1024

			// Open the audio device, forcing the wanted format
			if (SDL_OpenAudio(&audiospec_wanted, &audiospec_obtained) < 0) return 1;

			SDL_PauseAudio(0);

			return 0;
		}

		void audioClose() {
			SDL_CloseAudio();
		}

		// Closes and opens the audio device again with the same parameters
		int audioReOpen() {
			SDL_PauseAudio(1);
			SDL_CloseAudio();
			if (SDL_OpenAudio(&audiospec_wanted, &audiospec_obtained) < 0) return 1;
			SDL_PauseAudio(0);

			return 0;
		}

		void audioPushSamples(const std::vector<double>& samples, size_t pos, size_t end) {
			if (audio_mode == 0) return;

			Threading::Mutex mutex(audio_lock);

			if (audio_mode == 1) {
				audio_data.insert(audio_data.end(), samples.begin() + pos, samples.begin() + end);
			} else if (audio_mode == 2) {
				size_t j = audio_data.size();
				audio_data.resize(j + samples.size());
				for (size_t i = 0; i < samples.size(); i++) 
					audio_data[j + i] = samples[i] * audio_volume;
			}
		}

		size_t audioSamplesShortage() {
			if (audio_data.size() < audio_min_samples) return audio_min_samples - audio_data.size();
			else return 0;
		}

		size_t audioSamplesOverflow() {
			if (audio_data.size() > audio_max_samples) return audio_data.size() - audio_max_samples;
			else return 0;
		}

		void audioSetBufferSamplesRange(size_t min_samples, size_t max_samples) {
			audio_min_samples = min_samples;
			audio_max_samples = max_samples;
		}

		void audioPlay(const std::vector<double>& samples) {
			if (audio_mode == 0) return;

			Threading::Mutex mutex(audio_lock);

			// The *current* time is at the first sample of audio_data,
			// the rest has been played through the soundcard already

			if (samples.size() > audio_data.size()) audio_data.resize(samples.size(), 0.0);

			if (audio_mode == 1)
				for (size_t i = 0; i < samples.size(); i++)
					audio_data[i] += samples[i];
			else if (audio_mode == 2)
				for (size_t i = 0; i < samples.size(); i++)
					audio_data[i] += samples[i] * audio_volume;
		}


		void audioSetMode(int mode) {
			audio_mode = mode;
		}

		void audioSetVolume(double volume) {
			audio_volume = volume;
		}

	}
}


