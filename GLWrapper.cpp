#include "GLWrapper.hpp"

#include <iostream>

GL* GL::get() {
    static GL instance;
    return &instance;
}

GL::GL() {
    std::cout << "Initializing OpenGL\n";
}

GL::~GL() {
    std::cout << "Uninitializing OpenGL\n";
}
