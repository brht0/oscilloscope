#include "GLWrapper.hpp"
#include <iostream>
#include "ComputeProgramStack.hpp"
#include "Shader.hpp"
#include "Utils.hpp"

int main(){
    auto gl = GL::get();

    auto window = gl->CreateWindow("Audio stuff", 512, 512);

    unsigned texture = gl->CreateTexture(512, 512, GL_RGBA32F);
    unsigned texture2 = gl->CreateTexture(128, 128, GL_RGBA32F);
    unsigned texture_fbo = gl->CreateTextureFBO(texture);
    unsigned texture_fbo2 = gl->CreateTextureFBO(texture2);

    unsigned computeProgram = CreateComputeShader(LoadFile("diffusion.comp"), "diffusion");
    ComputeProgramStack stack;
    stack.AddProgram(computeProgram, 512 / 16, 512 / 16, 1);

    stack.AddTexture("screen", texture, 0);
    stack.SetInt("screenW", 512);
    stack.SetInt("screenH", 512);

    while(!gl->ShouldQuit() && (glfwGetKey(gl->Window(), GLFW_KEY_ESCAPE) != GLFW_PRESS)){
        gl->ClearTexture(0.0, 0.0, 1.0, 1.0);

        gl->ClearTexture(0.0, 1.0, 0.0, 1.0, texture_fbo);
        gl->ClearTexture(1.0, 0.0, 0.0, 1.0, texture_fbo2);
        gl->RenderTexture(texture2, 0.1, 0.1, 0.2, 0.2, 0.0, 0.0, 1.0, 1.0, texture_fbo);

        stack.Dispatch();

        gl->RenderTexture(texture, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0);

        glfwSwapBuffers(gl->Window());
        glfwPollEvents();
    }
}
