#ifndef _FILEIO_HPP_
#define _FILEIO_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "engine.hpp"

namespace Engine {
	namespace FileIO {

		/*************************************************
		* FILE INPUT/OUTPUT FUNCTIONS                    *
		*************************************************/

		void loadFile(std::vector<unsigned char>& buffer, const std::string& filename);
		void saveFile(const std::vector<unsigned char>& buffer, const std::string& filename);
	
	}
}

#endif

