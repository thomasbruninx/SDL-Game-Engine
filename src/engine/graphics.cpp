#include "graphics.hpp"

namespace Engine {
	namespace Graphics {
		/*************************************************
		* COLOR STRUCTS                                  *
		*************************************************/

		// ColorRGB constructors
		ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}

		ColorRGB::ColorRGB(const ColorRGB8bit& color) {
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
		}

		ColorRGB::ColorRGB() {
			this->r = 0;
			this->g = 0;
			this->b = 0;
		}

		// ColorRGB8bit constructors
		ColorRGB8bit::ColorRGB8bit(uint8_t r, uint8_t g, uint8_t b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}

		ColorRGB8bit::ColorRGB8bit(const ColorRGB& color) {
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
		}

		ColorRGB8bit::ColorRGB8bit() {
			this->r = 0;
			this->g = 0;
			this->b = 0;
		}

		// ColorRGB operators
		ColorRGB operator+(const ColorRGB& c1, const ColorRGB& c2) {
			ColorRGB cr;
			cr.r = c1.r + c2.r;
			cr.g = c1.g + c2.g;
			cr.b = c1.b + c2.b;
			return cr;
		}

		ColorRGB operator-(const ColorRGB& c1, const ColorRGB& c2) {
			ColorRGB cr;
			cr.r = c1.r - c2.r;
			cr.g = c1.g - c2.g;
			cr.b = c1.b - c2.b;
			return cr;
		}

		ColorRGB operator*(const ColorRGB& c, int a) {
			ColorRGB cr;
			cr.r = c.r * a;
			cr.g = c.g * a;
			cr.b = c.b * a;
			return cr;
		}

		ColorRGB operator*(int a, const ColorRGB& c) {
			ColorRGB cr;
			cr.r = c.r * a;
			cr.g = c.g * a;
			cr.b = c.b * a;
			return cr;
		}

		ColorRGB operator/(const ColorRGB& c, int a) {
			ColorRGB cr;
			cr.r = c.r / a;
			cr.g = c.g / a;
			cr.b = c.b / a;
			return cr;
		}

		bool operator==(const ColorRGB& c1, const ColorRGB& c2) {
			return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
		}

		bool operator!=(const ColorRGB& c1, const ColorRGB& c2) {
			return (!(c1.r == c2.r && c1.g == c2.g && c1.b == c2.b));
		}

		// ColorHSL constructors
		ColorHSL::ColorHSL(uint8_t h, uint8_t s, uint8_t l) {
			this->h = h;
			this->s = s;
			this->l = l;
		}

		ColorHSL::ColorHSL() {
			this->h = 0;
			this->s = 0;
			this->l = 0;
		}

		// ColorHSV constructors
		ColorHSV::ColorHSV(uint8_t h, uint8_t s, uint8_t v) {
			this->h = h;
			this->s = s;
			this->v = v;
		}

		ColorHSV::ColorHSV() {
			this->h = 0;
			this->s = 0;
			this->v = 0;
		}

		/*************************************************
		* COLOR CONVERSION FUNCTIONS                     *
		*************************************************/
		// These functions convert colors from one type to another
		// R = Red, G = Green, B = Blue, H = Hue, S = Saturation, L = Lightness, V = Value
		// Color components from the color structs are uint8_t types between 0 and 255
		// Color components used in the calculations are normalized between 0.0 and 1.0

		ColorHSL RGBtoHSL(const ColorRGB& colorRGB) {
			float r, g, b, h = 0, s = 0, l;
			r = colorRGB.r / 256.0;
			g = colorRGB.g / 256.0;
			b = colorRGB.b / 256.0;

			float maxColor = std::max(r, std::max(g, b));
			float minColor = std::min(r, std::min(g, b));

			// if R = G = B, it's a shade of grey
			if (minColor == maxColor) { 
				h = 0; // It doesn't matter what value it has
				s = 0;
				l = r; // Doesn't matter if you pick r, g or b
			} else {
				l = (minColor + maxColor) / 2;

				if (l < 0.5) s = (maxColor - minColor) / (maxColor + minColor);
				if (l >= 0.5) s = (maxColor - minColor) / (2.0 - maxColor - minColor);

				if (r == maxColor) h = (g - b) / (maxColor - minColor);
				if (g == maxColor) h = 2.0 + (b - r) / (maxColor - minColor);
				if (b == maxColor) h = 4.0 + (r - g) / (maxColor - minColor);

				h /= 6; // Bring it to a number between 0 and 1
				if (h < 0) h += 1;
			}

			ColorHSL colorHSL;
			colorHSL.h = int(h * 255.0);
			colorHSL.s = int(s * 255.0);
			colorHSL.l = int(l * 255.0);
			return colorHSL;
		}

		ColorRGB HSLtoRGB(const ColorHSL& colorHSL) {
			float r, g, b, h, s, l;
			float t1, t2, tr, tg, tb;
			h = colorHSL.h / 256.0;
			s = colorHSL.s / 256.0;
			l = colorHSL.h / 256.0;

			// If saturation is 0, it's a shade of grey
			if (s == 0) r = g = b = l;
			// If saturation > 0, calculations is more complex
			else {
				// Set temp values
				if (l < 0.5) t2 = l * (l + s);
				else t2 = (l + s) - (l * s);
				t1 = 2 * l - t2;
				tr = h + 1.0 / 3.0;
				if (tr > 1.0) tr--;
				tg = h;
				tb = h - 1.0 / 3.0;
				if (tb < 0.0) tb++;

				// Red
				if (tr < 1.0 / 6.0) r = t1 + (t2 - t1) * 6.0 * tr;
				else if (tr < 0.5) r = t2; 
				else if (tr < 2.0 / 3.0) r = t1 + (t2 - t1) * ((2.0 / 3.0) - tr) * 6.0;
				else r = t1;

				// Green
				if (tg < 1.0 / 6.0) g = t1 + (t2 - t1) * 6.0 * tg;
				else if (tg < 0.5) g = t2;
				else if (tg < 2.0 / 3.0) g = t1 + (t2 - t1) * ((2.0 / 3.0) - tg) * 6.0;
				else g = t1;

				// Blue
				if (tb < 1.0 / 6.0) b = t1 + (t2 - t1) * 6.0 * tb;
				else if (tb < 0.5) b = t2;
				else if (tb < 2.0 / 3.0) b = t1 + (t2 - t1) * ((2.0 / 3.0) - tb) * 6.0;
				else b = t1;
			}

			ColorRGB colorRGB;
			colorRGB.r = int(r * 255.0);
			colorRGB.g = int(g * 255.0);
			colorRGB.b = int(b * 255.0);
			return colorRGB;
		}

		ColorHSV RGBtoHSV(const ColorRGB& colorRGB) {
			float r, g, b, h = 0.0, s = 0.0 , v;
			r = colorRGB.r / 256.0;
			g = colorRGB.g / 256.0;
			b = colorRGB.b / 256.0;

			float maxColor = std::max(r, std::max(g, b));
			float minColor = std::min(r, std::min(g, b));

			v = maxColor;

			// Avoid division by zero (Black color)
			if (maxColor != 0.0) s = (maxColor - minColor) / maxColor;

			if (s == 0.0) h = 0.0; // Value doesn't matter
			else {
				if (r == maxColor) h = (g - b) / (maxColor - minColor);
				if (g == maxColor) h = 2.0 + (b - r) / (maxColor - minColor);
				if (b == maxColor) h = 4.0 + (r - g) / (maxColor - minColor);

				h /= 6.0; // Bring it to a number between 0 and 1
				if (h < 0.0) h++;
			}

			ColorHSV colorHSV;
			colorHSV.h = int(h * 255.0);
			colorHSV.s = int(s * 255.0);
			colorHSV.v = int(v * 255.0);
			return colorHSV;
		}

		ColorRGB HSVtoRGB(const ColorHSV& colorHSV) {
			float r, g, b, h, s, v;
			h = colorHSV.h / 256.0;
			s = colorHSV.s / 256.0;
			v = colorHSV.v / 256.0;

			// If saturation is 0, it's a shade of grey
			if (s == 0.0) r = g = b = v;
			// If saturation > 0, calculations is more complex
			else {
				float f, p, q, t;
				int i;
				h *= 6.0; // Bring hue to a number between 0 and 6, easier for calculations
				i = int(floor(h));
				f = h - i; // Fractional part of h

				p = v * (1.0 - s);
				q = v * (1.0 - (s * f));
				t = v * (1.0 - (s * (1.0 - f)));

				switch (i) {
					case 0:
						r = v; 
						q = t; 
						b = p; 
						break;
					case 1:
						r = q;
						g = v;
						b = p;
						break;
					case 2:
						r = p;
						g = v;
						b = t;
						break;
					case 3:
						r = p;
						g = q;
						b = v;
						break;
					case 4:
						r = t;
						g = p;
						b = v;
						break;
					case 5:
						r = v;
						g = p;
						b = q;
						break;
					default:
						r = g = b = 0;
						break;
				}
			}

			ColorRGB colorRGB;
			colorRGB.r = int(r * 255.0);
			colorRGB.g = int(g * 255.0);
			colorRGB.b = int(b * 255.0);
			return colorRGB;
		}

		uint32_t RGBtoINT(const ColorRGB& colorRGB) {
			return 65536 * colorRGB.r + 256 * colorRGB.g + colorRGB.b;
		}

		ColorRGB INTtoRGB(uint32_t colorInt) {
			ColorRGB colorRGB;
			colorRGB.r = (colorInt / 65536) % 256;
			colorRGB.g = (colorInt / 256) % 256;
			colorRGB.b = colorInt % 256;
			return colorRGB;
		}

		/*************************************************
		* GRAPHICS FUNCTIONS                             *
		*************************************************/

		// Updates screen, has to be called to show new pixels
		// Only use after drawing the whole screen (SLOW!!!)
		void updateScreen() {
			SDL_UpdateWindowSurface(gWindow);
		}

		// Clear screen
		void clearScreen(const ColorRGB& color) {
			SDL_FillRect(gScreenSurface, NULL, 65536 * color.r + 256 * color.g + color.b);
		}

		// Set pixel at position x,y to specified RGB color
		void setPixel(int x, int y, const ColorRGB& color) {
			if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight) return;
			uint32_t colorSDL = SDL_MapRGB(gScreenSurface->format, color.r, color.g, color.b);
			uint32_t* bufp;
			bufp = (uint32_t*)gScreenSurface->pixels + y * gScreenSurface->pitch / 4 + x;
			*bufp = colorSDL;
		}

		// Get RGB color of pixel at position x,y
		ColorRGB getPixel(int x, int y) {
			if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight) return RGB_Black;
			uint32_t* bufp;
			bufp  = (uint32_t*)gScreenSurface->pixels + y * gScreenSurface->pitch / 4 + x;
			uint32_t colorSDL = *bufp;
			ColorRGB8bit colorRGB;
			SDL_GetRGB(colorSDL, gScreenSurface->format, &colorRGB.r, &colorRGB.g, &colorRGB.b);
			return ColorRGB(colorRGB);
		}

		// Draw a buffer of pixels to screen
		void drawScreenBuffer(uint32_t* buffer) {
			uint32_t* bufp;
			bufp = (uint32_t*)gScreenSurface->pixels;

			for (int y = 0; y < screenHeight; y++) {
				for (int x = 0; x < screenWidth; x++) {
					*bufp = buffer[y * screenWidth + x];
					bufp++;
				}
				bufp += gScreenSurface->pitch / 4;
				bufp -= screenWidth;
			}
		}

		// Save screen contents
		void getScreenBuffer(std::vector<uint32_t>& buffer) {
			uint32_t* bufp;
			bufp = (uint32_t*)gScreenSurface->pixels;

			buffer.resize(screenWidth * screenHeight);

			for (int y = 0; y < screenHeight; y++) {
				for (int x = 0; x < screenWidth; x++) {
					buffer[y * screenWidth + x] = *bufp;
					bufp++;
				}
				bufp += gScreenSurface->pitch / 4;
				bufp -= screenWidth;
			}
		}

		// Check if position x,y is on the screen
		bool onScreen(int x, int y) {
			return (x >= 0 && y >= 0 && x < screenWidth && y < screenHeight);
		}

		/*************************************************
		* 2D GRAPHICS FUNCTIONS                          *
		*************************************************/

		// Draws horizontal line from (x1, y) to (x2, y)
		bool horiLine(int y, int x1, int x2, const ColorRGB& color) {
			// Swap x1 and x2, x1 must be left most
			if (x2 < x1) {
				x1 += x2;
				x2 = x1 - x2;
				x1 -= x2;
			}

			// Check if no single point is on screen
			if (x2 < 0 || x1 >= screenWidth || y < 0 || y >= screenHeight) return false;

			// Clipping
			if (x1 < 0) x1 = 0;
			if (x2 >= screenWidth) x2 = screenWidth - 1;

			uint32_t colorSDL = SDL_MapRGB(gScreenSurface->format, color.r, color.g, color.b);
			uint32_t* bufp;
			bufp = (uint32_t*)gScreenSurface->pixels + y *gScreenSurface->pitch / 4 + x1;
			for (int x = x1; x <= x2; x++) {
				*bufp = colorSDL;
				bufp++;
			}

			return true;
		}

		// Draws vertical line from (x, y1) to (x, y2)
		bool vertLine(int x, int y1, int y2, const ColorRGB& color) {
			// Swap y1 and y2, y1 must be top most
			if (y2 < y1) {
				y1 += y2;
				y2 = y1 - y2;
				y1 -= y2;
			}

			// Check if no single point is on screen
			if (y2 < 0 || y1 >= screenHeight || x < 0 || x >= screenWidth) return false;

			// Clipping
			if (y1 < 0) y1 = 0;
			if (y2 >= screenWidth) y2 = screenHeight - 1;

			uint32_t colorSDL = SDL_MapRGB(gScreenSurface->format, color.r, color.g, color.b);
			uint32_t* bufp;
			bufp = (uint32_t*)gScreenSurface->pixels + y1 * gScreenSurface->pitch / 4 + x;
			for (int y = y1; y <= y2; y++) {
				*bufp = colorSDL;
				bufp += gScreenSurface->pitch / 4;
			}

			return true;
		}

		// Draws a Bresenham line from (x1, y1) to (x2, y2)
		bool drawLine(int x1, int y1, int x2, int y2, const ColorRGB& color) {
			if (x1 < 0 || x1 > screenWidth - 1 || x2 < 0 || x2 > screenWidth - 1 || y1 < 0 || y1 > screenHeight - 1 || y2 < 0 || y2 > screenHeight - 1) return false;

			// Calculat the difference between x's and y's
			int deltaX = std::abs(x2 - x1);
			int deltaY = std::abs(y2 - y2);

			// Start of at the 1st pixel
			int x = x1;
			int y = y1;

			int xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpix;

			// Increasing x values
			if (x2 >= x1) {
				xinc1 = 1;
				xinc2 = 1;
			// Decreasing x values
			} else {
				xinc1 = -1;
				xinc2 = -1;
			}

			// Increasing y values
			if (y2 >= y1) {
				yinc1 = 1;
				yinc2 = 1;
			// Decreasing y values
			} else {
				yinc1 = -1;
				yinc2 = -1;
			}

			// There is at least 1 x value for every y value
			if (deltaX >= deltaY) {
				// Don't change x when numerator >= denominator
				// Don't change y for every iteration
				xinc1 = 0;
				yinc2 = 0;
				den = deltaX;
				num = deltaX / 2;
				numadd = deltaY;
				numpix = deltaX; // More x values than y values
			
			// There is at least 1 y value for every x value
			} else {
				// Don't change x for every iteration
				// Don't change y when numerator >= denominator
				xinc2 = 0;
				yinc1 = 0;
				den = deltaY;
				num = deltaY / 2;
				numadd = deltaX;
				numpix = deltaY; // More y values than x values
			}

			for (int i = 0; i <= numpix; i++) {
				setPixel(x % screenWidth, y % screenHeight, color); // Draw current pixel
				num += numadd; // Increase the numerator by the top of the fraction

				// Check if numerator >= denominator
				if (num >= den) {
					num -= den;	// Calculate the new numerator value
					x += xinc1;
					y += yinc1;
				}

				x += xinc2;
				y += yinc2;
			}

			return true;
		}

		// Draws a Bresenham circle with center at (xc, yc)
		bool drawCircle(int xc, int yc, int radius, const ColorRGB& color, bool fill) {
			// Check if all pixels outside the screen
			if (xc + radius < 0 || xc - radius >= screenWidth || yc + radius < 0 || yc - radius >= screenHeight) return false;

			int x = 0;
			int y = radius;
			int p = 3 - (radius << 1);
			int a, b, c, d, e, f, g, h;

			// Only used when filling
			// These are previous values, to avoid drawing
			// horizontal lines multiple times
			int pb, pd;
			if (fill) {
				pb = yc + radius + 1;
				pd = yc + radius + 1;
			}


			while (x <= y) {
				// 8 pixels can be calculated at once, cause of symmetry
				a = xc + x;
				b = yc + y;
				c = xc - x;
				d = yc - y;
				e = xc + y;
				f = yc + x;
				g = xc - y;
				h = yc - x;
				if (fill) {
					if (b != pb) horiLine(b, a, c, color);
					if (d != pd) horiLine(d, a, c, color);
					if (f != b) horiLine(f, e, g, color);
					if (h != d && h != f) horiLine(h, e, g, color);
					pb = b;
					pd = d;
				} else {
					setPixel(a, b, color);
					setPixel(c, d, color);
					setPixel(e, f, color);
					setPixel(g, f, color);
					// Avoid drawing pixels at same position as other ones
					if (x > 0) {
						setPixel(a, d, color);
						setPixel(c, b, color);
						setPixel(e, h, color);
						setPixel(g, h, color);
					}
				}
				if (p < 0) p += (x++ << 2) + 6;
				else p += ((x++ - y--) << 2) + 10;
			}

			return true;
		}

		// Draws a rectangle with corners (x1, y1) and (x2, y2)
		bool drawRect(int x1, int y1, int x2, int y2, const ColorRGB& color) {
			// Check if all pixels outside the screen
			if (x1 < 0 || x1 > screenWidth - 1 || x2 < 0 || x2 > screenWidth - 1 || y1 < 0 || y1 > screenHeight -1 || y2 < 0 || y2 > screenHeight - 1) return false;
		
			SDL_Rect rect;
			rect.x = x1;
			rect.y = y1;
			rect.w = x2 - x1 + 1;
			rect.h = y2 - y1 + 1;

			uint32_t colorSDL = SDL_MapRGB(gScreenSurface->format, color.r, color.g, color.b);

			SDL_FillRect(gScreenSurface, &rect, colorSDL);

			return true;
		}

		// Clips a 2D line to the screen (a rectangle (0,0)-(screenWidth, screenHeight))
		// Uses the Cohen-Sutherland clipping algorithm
		// Each of the 9 regions gets an outcode based on if it's at
		// the top, bottom, left of right of the screen
		// 1001 1000 1010  9 8 10
		// 0001 0000 0010  1 0 2
		// 0101 0100 0110  5 4 6
		bool clipLine(int x1, int y1, int x2, int y2, int& x3, int& y3, int& x4, int& y4) {
			int code1, code2, codeout;
			bool accept = false, done = false;

			// Get region outcodes for endpoints
			code1 = findRegion(x1, y1);
			code2 = findRegion(x2, y2);

			// In theory, this can never end up in an infinite loop, 
			// it'll always come in one of the trivial cases eventually
			do {
				if (!(code1 | code2)) accept = done = true;	// Accept, both endpoints are in the screen or on the border (trivial accept)
				else if (code1 & code2) done = 1; 			// Refuse, line isn't visuble on screen (trivial reject)
				else {										// Continue loop, more calculation needed
					int x, y;
					codeout = code1 ? code1 : code2;
					if (codeout & 1) {			// Top
						x = x1 + (x2 - x1) * (screenHeight - y1) / (y2 - y1);
						y = screenHeight - 1;
					} else if (codeout & 2) {	// Bottom
						x = x1 + (x2 - x1) * -y1 / (y2 - y1);
						y = 0;
					} else if (codeout & 4) { 	// Right
						y = y1 + (y2 - y1) * (screenWidth - x1) / (x2 - x1);
						x = screenWidth - 1;
					} else {					// Left
						y = y1 + (y2 - y1) * -x1 / (x2 - x1);
						x = 0;
					}

					// First endpoint clipped
					if (codeout == code1) {
						x1 = x; 
						y1 = y;
						code1 = findRegion(x1, y1);
					// Second endpoint clipped
					} else {
						x2 = x;
						y2 = y;
						code2 = findRegion(x2, y2);
					}
				}
			} while (!done);

			if (accept) {
				x3 = x1;
				x4 = x2;
				y3 = y1;
				y4 = y2;
				return true;
			} else {
				x3 = x4 = y3 = y4 = 0;
				return false;
			}
		}

		// Returns which of the 9 regions a point is int
		// Used for clipping
		int findRegion(int x, int y) {
			int code = 0;

			if (y >= screenHeight) code |= 1;	// Top
			else if (y < 0) code |= 2;			// Bottom

			if (x >= screenWidth) code |= 4;	// Right
			else if (x < 0) code |= 8;			// Left

			return code;
		}

		/*************************************************
		* IMAGE FUNCTIONS                                *
		*************************************************/

		bool loadImage(std::vector<ColorRGB>& out, unsigned long& w, unsigned long& h, const std::string& filename) {
			std::vector<unsigned char> file, image;
			FileIO::loadFile(file, filename);

			if(PicoPNG::decodePNG(image, w, h, file)) return true;

			out.resize(image.size() / 4);

			for (size_t i = 0; i < out.size(); i++) {
				out[i].r = image[i * 4 + 0];
				out[i].g = image[i * 4 + 1];
				out[i].b = image[i * 4 + 2];
			}

			return false;
		}

		bool loadImage(std::vector<uint32_t>& out, unsigned long& w, unsigned long& h, const std::string& filename) {
			std::vector<unsigned char> file, image;
			FileIO::loadFile(file, filename);

			if(PicoPNG::decodePNG(image, w, h, file)) return true;

			out.resize(image.size() / 4);

			for (size_t i = 0; i < out.size(); i++)
				out[i] = 0x1000000 * image[i * 4 + 3] + 0x10000 * image[i * 4 + 0] + 0x100 * image[i * 4 + 1] + image[i * 4 + 2];

			return false;
		}

	}
}


