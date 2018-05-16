#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include "engine.hpp"
#include "graphics.hpp"
#include "input.hpp"

namespace Engine {
	namespace Text {
		extern bool font[256][8][8];

		const int ASCII_ENTER = 13;
		const int ASCII_BACKSPACE = 8;
		const int ASCII_SPACE = 32;
		const int ASCII_ESCAPE = 27;

		/*************************************************
		* TEXT FUNCTIONS                                 *
		*************************************************/

		void drawLetter(unsigned char n, int x, int y, const Graphics::ColorRGB& color = Graphics::RGB_White, bool bg = false, const Graphics::ColorRGB& color2 = Graphics::RGB_Black);
		int printString(const std::string& text, int x, int y, const Graphics::ColorRGB& color = Graphics::RGB_White, bool bg = false, const Graphics::ColorRGB& color2 = Graphics::RGB_Black, int forceLength = 0);

		/*************************************************
		* TEXT FUNCTIONS                                 *
		*************************************************/

		uint8_t getInputChar();
		void getInputString(std::string& text, const std::string& message = "", bool clear = false, int x = 0, int y = 0, const Graphics::ColorRGB& color = Graphics::RGB_White, bool bg = false, const Graphics::ColorRGB& color2 = Graphics::RGB_Black);

		/*************************************************
		* BASE64 ENCODING                                *
		*************************************************/

		void encodeBase64(const std::vector<unsigned char>& in, std::string& out);
		void decodeBase64(std::vector<unsigned char>& out, const std::string& in);

		/*************************************************
		* TRIM FUNCTIONS                                 *
		*************************************************/

		std::string& ltrim(std::string& s);
		std::string& rtrim(std::string& s);
		std::string& trim(std::string& s);

		/*************************************************
		* TEMPLATES                                      *
		*************************************************/

		// Converts numerical value to string
		// usage: std::string s = valToStr(123.456f);
		template<typename T> std::string valToStr(const T& val) {
			std::ostringstream sstream;
			sstream << val;
			return sstream.str();
		}

		// Converts numerical value to string
		// (specified decimal precision)
		template<typename T> std::string valToStr(const T& val, int length, bool fixed = true) {
			std::ostringstream sstream;
			if (fixed) sstream << std::fixed;
			sstream << std::setprecision(length) << val;
			return sstream.str();
		}

		// Converts string to numerical value
		// usage: double d = strToVal<double>("123.256");
		template<typename T> T strToVal(const std::string& s) {
			std::istringstream sstream(s);
			T val;
			sstream >> val;
			return val;
		}

		// Prints to the screen (string, float, int, ...)
		template<typename T> int print(const T& val, int x = 0, int y = 0, const Graphics::ColorRGB& color = Graphics::RGB_White, bool bg = false, const Graphics::ColorRGB& color2 = Graphics::RGB_Black, int forceLength = 0) {
			std::string text = valToStr(val);
			return printString(text, x, y, color, bg, color2, forceLength);
		}

		// Prints a floating point number (specified decimal precision) to the screen
		template<typename T> int printFloat(const T& val, int length, int x = 0, int y = 0, const Graphics::ColorRGB& color = Graphics::RGB_White, bool bg = false, const Graphics::ColorRGB& color2 = Graphics::RGB_Black, int forceLength = 0) {
			std::string text = valToStr(val, length, true);
			return printString(text, x, y, color, bg, color2, forceLength);
		}

		// Gets input from user in a specified type
		template<typename T> T getInput(const std::string& message = "", bool clear = false, int x = 0, int y = 0, const Graphics::ColorRGB& color = Graphics::RGB_White, bool bg = false, const Graphics::ColorRGB& color2 = Graphics::RGB_Black) {
			std::string text;
			getInputString(text, message, clear, x, y, color, bg, color2);
			return strToVal<T>(text);
		}

	}
}

#endif

