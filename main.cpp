#include "GLWrapper.hpp"
#include <iostream>

int main(){
    auto gl = GL::get();

    auto window = gl->CreateWindow("Audio stuff", 512, 512);

    unsigned texture = gl->CreateTexture(128, 128, GL_RGBA);
    unsigned texture2 = gl->CreateTexture(128, 128, GL_RGBA);
    unsigned texture_fbo = gl->CreateTextureFBO(texture);
    unsigned texture_fbo2 = gl->CreateTextureFBO(texture2);

    while(!gl->ShouldQuit() && (glfwGetKey(gl->Window(), GLFW_KEY_ESCAPE) != GLFW_PRESS)){
        gl->ClearTexture(0.0, 0.0, 1.0, 1.0);

        gl->ClearTexture(0.0, 1.0, 0.0, 1.0, texture_fbo);
        gl->ClearTexture(1.0, 1.0, 1.0, 1.0, texture_fbo2);
        gl->RenderTexture(texture2, 0.1, 0.1, 0.2, 0.2, 0.0, 0.0, 1.0, 1.0, 0);
        gl->RenderTexture(texture, 0.5, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0);

        glfwSwapBuffers(gl->Window());
        glfwPollEvents();
    }
}
