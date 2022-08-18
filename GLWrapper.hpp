#ifndef __GLWRAPPER_H__
#define __GLWRAPPER_H__

#include "OpenGL.hpp"

class GL{
public:
    static GL* get();
    GLFWwindow* Init(const char* title, int width, int height);

    GLFWwindow* GetWindow() const;

    unsigned CreateTexture(int width, int height, int format);
    unsigned CreateTextureFBO(unsigned texture);

    void ClearTexture(float r, float g, float b, float a, unsigned fbo = 0);
    void RenderTexture(unsigned texture, float x0=0.0, float y0=0.0, float x1=1.0, float y1=1.0, float tx0=0.0, float ty0=0.0, float tx1=1.0, float ty1=1.0, unsigned fbo = 0);

private:
    void InitializeGLFW();
    void InitializeAL();

    void UninitializeGLFW();
    void UninitializeAL();

    void CreateDefaultVAO();
    void CreateDefaultPrograms();

    GL();
    ~GL();

private:
    inline static bool initialized = false;

    GLFWwindow* window = nullptr;

    unsigned vbo, vao;
    unsigned program_texture_to_screen;
};

#endif // __GLWRAPPER_H__