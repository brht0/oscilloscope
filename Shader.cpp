#include "Shader.hpp"

#include "OpenGL.hpp"
#include <iostream>

void CheckShaderErrors(unsigned int shader, std::string name){
    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << name << "\n" << infoLog << "\n";
    }
}

void CheckProgramErrors(unsigned int shader, std::string name){
    int success;
    char infoLog[1024];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << name << "\n" << infoLog << "\n";
    }
}

unsigned CreateComputeShader(std::string code, std::string name){
    unsigned program;

    const char* code_cstr = code.c_str();

    unsigned int shader;
    shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader, 1, &code_cstr, NULL);
    glCompileShader(shader);
    CheckShaderErrors(shader, name + " compute");

    program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);

    CheckProgramErrors(program, name + " program");
    glDeleteShader(shader);
    
    return program;
}

unsigned CreateShader(std::string vertexCode, std::string fragmentCode, std::string name){
    unsigned program;

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckShaderErrors(vertex, name + " vertex");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckShaderErrors(fragment, name + " fragment");

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    CheckProgramErrors(program, name + " program");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    return program;
}
