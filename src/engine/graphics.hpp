#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include <stdint.h>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include "../picopng/picopng.hpp"

#include "engine.hpp"
#include "fileio.hpp"

namespace Engine {
	namespace Graphics {
		/*************************************************
		* COLOR STRUCTS                                  *
		*************************************************/

		struct ColorRGB8bit;
		typedef struct ColorRGB {
			int r;
			int g;
			int b;

			ColorRGB(uint8_t r, uint8_t g, uint8_t b);
			ColorRGB(const ColorRGB8bit& color);
			ColorRGB();
		} ColorRGB_t;

		ColorRGB operator+(const ColorRGB& c1, const ColorRGB& c2);
		ColorRGB operator-(const ColorRGB& c1, const ColorRGB& c2);
		ColorRGB operator*(const ColorRGB& c, int a);
		ColorRGB operator*(int a, const ColorRGB& c);
		ColorRGB operator/(const ColorRGB& c, int a);
		bool operator==(const ColorRGB& c1, const ColorRGB& c2);
		bool operator!=(const ColorRGB& c1, const ColorRGB& c2);

		static const ColorRGB RGB_Black     (  0,   0,   0);
		static const ColorRGB RGB_Red       (255,   0,   0);
		static const ColorRGB RGB_Green     (  0, 255,   0);
		static const ColorRGB RGB_Blue      (  0,   0, 255);
		static const ColorRGB RGB_Cyan      (  0, 255, 255);
		static const ColorRGB RGB_Magenta   (255,   0, 255);
		static const ColorRGB RGB_Yellow    (255, 255,   0);
		static const ColorRGB RGB_White     (255, 255, 255);
		static const ColorRGB RGB_Grey      (128, 128, 128);
		static const ColorRGB RGB_DarkGrey  (192, 192, 192);
		static const ColorRGB RGB_Maroon    (128,   0,   0);
		static const ColorRGB RGB_Darkgreen (  0, 128,   0);
		static const ColorRGB RGB_Navy      (  0,   0, 128);
		static const ColorRGB RGB_Teal      (  0, 128, 128);
		static const ColorRGB RGB_Purple    (128,   0, 128);
		static const ColorRGB RGB_Olive     (128, 128,   0);

		typedef struct ColorRGB8bit {
			uint8_t r;
			uint8_t g;
			uint8_t b;

			ColorRGB8bit(uint8_t r, uint8_t g, uint8_t b);
			ColorRGB8bit(const ColorRGB& color);
			ColorRGB8bit();
		} ColorRGB8bit_t;

		typedef struct ColorHSL {
			int h;
			int s;
			int l;

			ColorHSL(uint8_t h, uint8_t s, uint8_t l);
			ColorHSL();
		} ColorHSL_t;

		typedef struct ColorHSV {
			int h;
			int s;
			int v;

			ColorHSV(uint8_t h, uint8_t s, uint8_t v);
			ColorHSV();
		} ColorHSV_t;

		/*************************************************
		* COLOR CONVERSION FUNCTIONS                     *
		*************************************************/

		ColorHSL RGBtoHSL(const ColorRGB& colorRGB);
		ColorRGB HSLtoRGB(const ColorHSL& colorHSL);
		ColorHSV RGBtoHSV(const ColorRGB& colorRGB);
		ColorRGB HSVtoRGB(const ColorHSV& colorHVL);
		uint32_t RGBtoINT(const ColorRGB& colorRGB);
		ColorRGB INTtoRGB(uint32_t colorInt);

		/*************************************************
		* GRAPHICS FUNCTIONS                             *
		*************************************************/

		void updateScreen();
		void clearScreen(const ColorRGB& color = RGB_Black);
		void setPixel(int x, int y, const ColorRGB& color);
		ColorRGB getPixel(int x, int y);
		void drawScreenBuffer(uint32_t* buffer);
		void getScreenBuffer(std::vector<uint32_t>& buffer);
		bool onScreen(int x, int y);

		/*************************************************
		* 2D GRAPHICS FUNCTIONS                          *
		*************************************************/

		bool horiLine(int y, int x1, int x2, const ColorRGB& color);
		bool vertLine(int x, int y1, int y2, const ColorRGB& color);
		bool drawLine(int x1, int y1, int x2, int y2, const ColorRGB& color);
		bool drawCircle(int xc, int yc, int radius, const ColorRGB& color, bool fill = false);
		bool drawRect(int x1, int y1, int x2, int y2, const ColorRGB& color);
		bool clipLine(int x1, int y1, int x2, int y2, int& x3, int& y3, int& x4, int& y4);
		int findRegion(int x, int y);

		/*************************************************
		* IMAGE FUNCTIONS                                *
		*************************************************/

		bool loadImage(std::vector<ColorRGB>& out, unsigned long& w, unsigned long& h, const std::string& filename);
		bool loadImage(std::vector<Uint32>& out, unsigned long& w, unsigned long& h, const std::string& filename);
		
	}
}

#endif

