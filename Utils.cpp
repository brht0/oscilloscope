#include "Utils.hpp"

#include <fstream>

std::string LoadFile(std::string filename) {
    std::ifstream file(filename);

    return std::string(
        std::istreambuf_iterator<char>( file.rdbuf() ),
        std::istreambuf_iterator<char>()
    );
}
