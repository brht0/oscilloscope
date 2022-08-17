#include "GLWrapper.hpp"

#include <iostream>

GL* GL::get() {
    static GL instance;
    return &instance;
}

GL::GL() {
    InitializeGLFW();
}

GL::~GL() {
    UninitializeGLFW();
}

GLFWwindow* GL::CreateWindow(const char* title, int width, int height) {
    if(window){
        std::cout << "GL: Could not create window. Window already created.\n";
        return window;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CreateDefaultPrograms();
    CreateDefaultVAO();

    return window;
}

void GL::InitializeGLFW() {
    std::cout << "GL: Initializing OpenGL\n";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GL::UninitializeGLFW(){
    std::cout << "GL: Uninitializing OpenGL\n";
    // todo 
}

bool GL::ShouldQuit() {
    return window ? glfwWindowShouldClose(window) : true;
}

unsigned GL::CreateTexture(int width, int height, int format) {
    if(!window){
        std::cout << "GL: Could not create texture.\n";
        return 0;
    }

    unsigned texture;
    glGenTextures(1, &texture);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;    
}

#include "Shader.hpp"
#include "Utils.hpp"

void GL::CreateDefaultPrograms() {
    const char* const program_texture_to_screen_frag_filename = "texture_to_screen.frag";
    const char* const program_texture_to_screen_vert_filename = "texture_to_screen.vert";

    program_texture_to_screen = CreateShader(
        LoadFile(program_texture_to_screen_vert_filename),
        LoadFile(program_texture_to_screen_frag_filename), "program_texture_to_screen");
}

GLFWwindow* GL::Window() const {
    return window;    
}

void GL::ClearTexture(float r, float g, float b, float a, unsigned fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GL::RenderTexture(unsigned texture, float x0, float y0, float x1, float y1, float tx0, float ty0, float tx1, float ty1, unsigned fbo) {
    float vertices[] = {
        x0, y0, tx0, ty0,
        x1, y0, tx1, ty0,
        x0, y1, tx0, ty1,
        x0, y1, tx0, ty1,
        x1, y0, tx1, ty0,
        x1, y1, tx1, ty1,
    };

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glUseProgram(program_texture_to_screen);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);
    glUniform1i(glGetUniformLocation(program_texture_to_screen, "src1"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned GL::CreateTextureFBO(unsigned texture) {
    unsigned texture_fbo;
    glGenFramebuffers(1, &texture_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, texture_fbo);
    glBindTexture(GL_TEXTURE_2D, texture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_fbo;
}

void GL::CreateDefaultVAO() {
    const float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}
