#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

unsigned CreateComputeShader(std::string code, std::string name);
unsigned CreateShader(std::string vertexCode, std::string fragmentCode, std::string name);

#endif // __SHADER_H__