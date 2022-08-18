#ifndef __UNIFORMIMGUIHELPER_H__
#define __UNIFORMIMGUIHELPER_H__

#include <map>
#include <string>
#include <vector>

class ComputeProgramStack{
public:
    void Dispatch();
    void AddProgram(unsigned program, int x, int y, int z);

    void BindUniforms(unsigned program);
    void BindSSBOs(unsigned program);
    void BindTextures(unsigned program);

    void SetFloat(std::string key, float value);
    void SetInt(std::string key, int value);
    float GetFloat(std::string key);
    int GetInt(std::string key);

    void AddTexture(std::string key, unsigned texture, int binding);
    void AddSSBO(std::string key, unsigned ssbo, int base);

    ComputeProgramStack();
    ~ComputeProgramStack();

    unsigned CreateSSBO(std::string key, int base);
    void UploadSSBO(unsigned ssbo, void* data, size_t datasize);

private:
    struct UniformInt{
        int value;
    };
    std::map<std::string, UniformInt> int_uniforms;

    struct UniformFloat{
        float value;
    };
    std::map<std::string, UniformFloat> float_uniforms;

    struct SSBO{
        std::string key;
        int base;
    };
    std::map<unsigned, SSBO> ssbos;

    struct Texture{
        std::string key;
        int binding;
    };
    std::map<unsigned, Texture> textures;

    struct Program{
        unsigned program;
        int x, y, z;
    };
    std::vector<Program> programs;
};

#endif // __UNIFORMIMGUIHELPER_H__