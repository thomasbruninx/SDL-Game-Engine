#include "text.hpp"

namespace Engine {
	namespace Text {
		bool font[256][8][8];
		struct GenerateFont {
  			GenerateFont() {
			    // The full extended ASCII character set, in the form 256 bitmap symbols of 8x8
			    // pixels in one 128x128 PNG, base64-encoded.
			    // The background color is black, not transparent.
   				const std::string font8x8string = "\
					iVBORw0KGgoAAAANSUhEUgAAAIAAAACAAQAAAADrRVxmAAAEjklEQVR4AY2TBYhsyRWG/9hqPcEP\n\
					TLOO24n1u8Bdxd3iWK1VrICOdQ6kcmeDRXGJJ0gch6CxgoGKHV7Qx8A8aWxdOjZ7gaLuVt2RdfnL\n\
					mq//I9eAYfDnu/OYMJ3r7939IfCNqXShgn7vevfBhz8F/PKghK6jJ9wPz7l7d/vZUUro9x7409cd\n\
					P/wE8Ke9EEppQPsZ/PCJrrsUWojS6tNzyPmqllSH7eOfamWBrmtlhTbxh3js3eR2BxARjrQ527uD\n\
					PfQ9EeMumjDeM7gDqYFkbHT9hFLIfU1bSClxGobqILej1TA0x9TXHAN2ZOipJy53TVSr9G7ne0Or\n\
					ciICRkw4FXvP6CxZNF0HiPchecvsGIBpoETtoqWej+IZXmgNS1NGBjdQDF/GsWPO5EenaDlW4DiH\n\
					cFqjVWHwYzjViV9YZJG7LAIQrEC3qn20qjqHKC6zMX6MRpXZZjLI3HVqRpLAHGEIz7I1xSirAaqD\n\
					oaxa/VaJVwwGJGcxIlZWzATLr2sDgXOfS+lVbnl8m1KHJM75hx5yysbZ5x/3uKouus98JlbgbTlM\n\
					FYToRGJmI/bS1Qry7LiorP6hdDEhasthXQXOpeQh2qps71GRx0ur8jplqUM1JS0S5Tzg1OnvZ6DW\n\
					UjeDDVfg9QeWyQNBQ1fBpU7YEiXAXpZFBcXzQ9YQKhCvrPJ84mSva2C7eFwkc0pS5N2C12kCY4MF\n\
					OmyYNquGGBYGvu7H948kiBG79itx/OwogHEadKtrJs9FFQguarbqmIQvNaBONdrgmiM1sP6jrGVr\n\
					Hpf9xyWp4FgjsMKpzmPWgjbro5+MWUx8ucPl9X4I8w3KFcDDqY/HN6hdQ2pA5huk3BwJIVjzIZXi\n\
					wyNHwJrtSGv2yeRaBQXbW17uZJZgMeiGUTcNG2WoYg/gtiGBGRHSi0io26pbCaCq1xljolNlYhWI\n\
					5ntCCHHIuQEFaftTg42xgpxhBrl3GIbrWqJeVCGY1eNEC9wjaDgpdbo9C8CrburoQF73d5B3FbOC\n\
					Do/IPsGaIiKqmjRu8/8GyK7OasCyVoceKdeQx/NVqjkuisgwmE4os+7jRCNAwNkVFh2A3PcMpHTc\n\
					2mKEdwBU6YMKWQFQ7xjY34dzMCw6PntPb3O+57+kH0TgVhOI0Tz8aaoObeDyMGg0F//V1xyDyKAK\n\
					CPCDn/d4lW59DwG446NXiGgJLJd1VvKt33311WB2jEuMh8tyuBxfdtB1y+uuO3GM42GpjsNSxvHE\n\
					saxzCYCa49XgdQ6qE41gHm8Kbl1euPfF6cL04nTqYAZ4vqJpavPCvfXv2YHZQ3OCtr0D0Ca1RZiw\n\
					PTe9Aajz1lvr8SoH1eMETNN076231jbH2s72HABattUu4h2DqgIgd90C1/UCSCkObs3eM4xVrDV5\n\
					HtxlSYmGISouj9GTOtKSwsFBVvxNo+cGkteDg2OH00DivQ5DyxGjL2KJu+cFtlcgAm3LR0cVWzpL\n\
					jA44JwIgM/MO8Rc9YLxBI2R3CD+ZQdcfOYgyOqrA9kc5iPBFED3rQ3MAoH3+CQAPNEfOuYJXf6q0\n\
					QtOibS8BEX/cffjo+7IAAAAASUVORK5CYII=";

    			std::vector<unsigned char> png, image;
    			decodeBase64(png, font8x8string);
    			unsigned long w, h;
    			PicoPNG::decodePNG(image, w, h, &png[0], png.size());
    			for(size_t c = 0; c < 256; c++)
    				for(size_t y = 0; y < 8; y++)
    					for(size_t x = 0; x < 8; x++)
      						font[c][x][y] = image[4 * 128 * (8 * (c / 16) + y) + 4 * (8 * (c % 16) + x)] != 0;

 			}
		}; 
		GenerateFont generateFont;

		/*************************************************
		* TEXT FUNCTIONS                                 *
		*************************************************/

		// Draws character n at (x, y) in a certain color and if 
		// enabled a background color
		void drawLetter(unsigned char n, int x, int y, const Graphics::ColorRGB& color, bool bg, const Graphics::ColorRGB& color2) {
			for (int v = 0; v < 8; v++) {
				for (int u = 0; u < 8; u++) {
					if (font[n][u][v]) setPixel(x + u, y + v, color);
					else if (bg) setPixel(x + u, y + v, color2);
				}
			}
		}

		// Draw a string of text
		int printString(const std::string& text, int x, int y, const Graphics::ColorRGB& color, bool bg, const Graphics::ColorRGB& color2, int forceLength) {
			int amount = 0;

			for (size_t i = 0; i < text.size(); i++) {
				amount++;
				drawLetter(text[i], x, y, color, bg, color2);
				x += 8;
				if (x > screenWidth - 8) {
					x %= 8;
					y += 8;
				}
				if (y > screenHeight - 8) y %= 8;
			}

			while (amount < forceLength) {
				amount++;
				drawLetter(' ', x, y, color, bg, color2);
				x += 8;
				if (x > screenWidth - 8) {
					x %= 8;
					y += 8;
				}
				if (y > screenHeight - 8) y %= 8;
			}

			return screenHeight * x + y;
		}

		/*************************************************
		* TEXT FUNCTIONS                                 *
		*************************************************/

		// Get user input (single character)
		uint8_t getInputChar() {
			int ascii = 0;
			static int prevChar = 0;

			if (event.type == SDL_TEXTINPUT) {
				ascii = (int)event.text.text[0];
			}

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_BACKSPACE) ascii = ASCII_BACKSPACE;
				else if (event.key.keysym.sym == SDLK_RETURN) ascii = ASCII_ENTER;
			}

			if (ascii != prevChar) prevChar = ascii;
			else ascii = 0;

			return ascii;
		}

		// Get user input (string) also able to print message before getting input
		void getInputString(std::string& text, const std::string& message, bool clear, int x, int y, const Graphics::ColorRGB& color, bool bg, const Graphics::ColorRGB& color2) {
			std::vector<uint32_t> screenBuffer;
			Graphics::getScreenBuffer(screenBuffer);
			
			bool enter = false;
			bool change = true;
			text.clear();

			while (!enter) {
				if (done()) end();
				uint8_t temp = getInputChar();

				if (temp >= ASCII_SPACE) {
					text.push_back(temp);
					change = true;
				}

				if (temp == ASCII_BACKSPACE && text.size() > 0) {
					text.resize(text.size() - 1);
					change = true;
				}

				if (change) {
					Graphics::drawScreenBuffer(&screenBuffer[0]);
					int pos = print(message, x, y, color, bg, color2);
					int x2 = pos / screenHeight, y2 = pos % screenHeight;
					print(text, x2, y2, color, bg, color2);
					Graphics::updateScreen();
				}

				if (temp == ASCII_ENTER) enter = true;
			}

			// Remove input stuff from the screen again so there is
			// room for possible next input
			if (clear) {
				Graphics::drawScreenBuffer(&screenBuffer[0]);
				Graphics::updateScreen();
			}
		}

		/*************************************************
		* BASE64 ENCODING                                *
		*************************************************/

		void encodeBase64(const std::vector<unsigned char>& in, std::string& out) {
			const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			unsigned long bit24 = 0;
			unsigned long sextet[4] = {0, 0, 0, 0};
			unsigned long octet[3] = {0, 0, 0};

			out.clear();
			out.reserve((4 * in.size()) / 3);

			for (size_t i = 0; i < in.size(); i += 3) {
				octet[0] = in[i + 0];
				octet[1] = (i + 1 < in.size()) ? in[i + 1] : 0;
				octet[2] = (i + 2 < in.size()) ? in[i + 2] : 0;

				bit24 = 256 * 256 * octet[0];
				bit24 += 256 * octet[1];
				bit24 += octet[2];

				sextet[0] = (bit24 / (64 * 64 * 64)) % 64;
				sextet[1] = (bit24 / (64 * 64)) % 64;
				sextet[2] = (bit24 / 64) % 64;
				sextet[3] = (bit24 / 1) % 64;

				for (size_t j = 0; j < 4; j++) {
					if (i + j - 1 < in.size()) out.push_back(chars[sextet[j]]);
					else out.push_back('=');
				}

				// Put a newline char ever 76 chars (57 = 3/4th of 76)
				if (i % 57 == 0 && i != 0) out.push_back(10);
			}
		}

		void decodeBase64(std::vector<unsigned char>& out, const std::string& in) {
			unsigned long bit24 = 0;
			unsigned long sextet[4] = {0, 0, 0, 0};
			unsigned long octet[3] = {0, 0, 0};

			out.clear();
			out.reserve((3 * in.size()) / 4);

			for (size_t i = 0; i < in.size(); i += 4) {
				for (size_t j = 0; j < 4; j++) {
					unsigned long c = in[i + j];

					if (c >= 65 && c <= 90) sextet[j] = c - 65;
					else if (c >= 97 && c <= 122) sextet[j] = c - 71;
					else if (c >= 48 && c <= 57) sextet[j] = c + 4;
					else if (c == '+') sextet[j] = 62;
					else if (c == '/') sextet[j] = 63;
					else if (c == '=') sextet[j] = 0; // Value Doesn't matter
					else {	// Unknown char, (whitespace, newline, ...)
						i++;
						if (i > in.size() - 3) return;
						j--;
					}
				}

				bit24 = 64 * 64 * 64 * sextet[0];
				bit24 += 64 * 64 * sextet[1];
				bit24 += 64 * sextet[2];
				bit24 += sextet[3];

				octet[0] = (bit24 / (256 * 256)) % 256;
				octet[1] = (bit24 / 256) % 256;
				octet[2] = (bit24 / 1) % 256;

				for (size_t j = 0; j < 3; j++)
					if (in[i + 1 + j] != '=') out.push_back(octet[j]);
			}
		}

		/*************************************************
		* TRIM FUNCTIONS                                 *
		*************************************************/

		// Trims leading whitespace
		std::string& ltrim(std::string& s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(),
				std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
		}

		// Trims trailing whitespace
		std::string& rtrim(std::string& s) {
			s.erase(std::find_if(s.rbegin(), s.rend(),
				std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    		return s;
		}

		// Trims both leading and trailing whitespace
		std::string& trim(std::string& s) {
			return ltrim(rtrim(s));
		}

	}
}

