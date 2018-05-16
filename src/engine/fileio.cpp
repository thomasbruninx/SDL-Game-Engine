#include "fileio.hpp"

namespace Engine {
	namespace FileIO {

		/*************************************************
		* FILE INPUT/OUTPUT FUNCTIONS                    *
		*************************************************/

		// Loads a file in an std::vector
		void loadFile(std::vector<unsigned char>& buffer, const std::string& filename) {
			std::ifstream file(filename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

			// Get file size
			std::streamsize size = 0;
			if (file.seekg(0, std::ios::end).good()) size = file.tellg();
			if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

			// Read contents of file into vector
			buffer.resize(size_t(size));
			if (size > 0) file.read((char*)(&buffer[0]), size);
		}

		// Writes a buffer (std::vector) to a file
		// Overwrties, doesn't append
		void saveFile(const std::vector<unsigned char>& buffer, const std::string& filename) {
			std::ofstream file(filename.c_str(), std::ios::out|std::ios::binary);
			file.write(buffer.size() ? (char*)&buffer[0] : 0, std::streamsize(buffer.size()));
		}

	}
}

