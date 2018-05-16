#include "util.hpp"

namespace Engine {
	namespace Util {

         // Calculates FPS and prints it to the screen (top left)
         void drawFpsCounter (float frameTime, const Graphics::ColorRGB& color) {
              float fps = 1.0 / frameTime;
              Text::printFloat(fps, 1, 0, 0, color);      
         }

    }
}
