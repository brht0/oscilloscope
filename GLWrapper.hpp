#ifndef __GLWRAPPER_H__
#define __GLWRAPPER_H__

#include "OpenGL.hpp"

#include <vector>

class GL{
public:
    static GL* get();
    GLFWwindow* Window() const;

    bool ShouldQuit();
    GLFWwindow* CreateWindow(const char* title, int width, int height);

    void ClearTexture(float r, float g, float b, float a, unsigned fbo = 0);
    unsigned CreateTexture(int width, int height, int format);
    unsigned CreateTextureFBO(unsigned texture);

    void RenderTexture(unsigned texture, float x0, float y0, float x1, float y1, float tx0, float ty0, float tx1, float ty1, unsigned fbo = 0);

private:
    static void InitializeGLFW();
    static void UninitializeGLFW();

    void CreateDefaultVAO();
    void CreateDefaultPrograms();

    GL();
    ~GL();

private:
    GLFWwindow* window = nullptr;

    unsigned vbo, vao;

    unsigned program_texture_to_screen;
};

#endif // __GLWRAPPER_H__