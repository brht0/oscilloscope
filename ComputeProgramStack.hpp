#ifndef __UNIFORMIMGUIHELPER_H__
#define __UNIFORMIMGUIHELPER_H__

// #include "imgui/imgui.h"
// #include "imgui/backends/imgui_impl_glfw.h"
// #include "imgui/backends/imgui_impl_opengl3.h"

#include <map>
#include <string>
#include <vector>

class ComputeProgramStack{
public:
    void Dispatch();
    void AddProgram(unsigned program, int x, int y, int z);

    void RenderImgui();

    void BindUniforms(unsigned program);
    void BindSSBOs(unsigned program);
    void BindTextures(unsigned program);

    void AddFloat(std::string key, float value, float sliderstart, float sliderEnd, bool show);
    void AddInt(std::string key, int value, int sliderstart, int sliderEnd, bool show);
    void SetFloat(std::string key, float value);
    void SetInt(std::string key, int value);

    void AddTexture(std::string key, unsigned texture, int binding);
    void AddSSBO(std::string key, unsigned ssbo, int base);

    ComputeProgramStack();
    ~ComputeProgramStack();

    unsigned CreateSSBO(std::string key, int base);
    void UploadSSBO(unsigned ssbo, void* data, size_t datasize);

private:
    struct UniformInt{
        bool showImgui;
        int sliderstart, sliderend;
        int value;
    };
    std::map<std::string, UniformInt> int_uniforms;

    struct UniformFloat{
        bool showImgui;
        float sliderstart, sliderend;
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