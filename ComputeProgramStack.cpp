#include "ComputeProgramStack.hpp"

#include "OpenGL.hpp"

void ComputeProgramStack::BindUniforms(unsigned program) {
    for(auto[str, i] : int_uniforms){
        int location = glGetUniformLocation(program, str.c_str());
        if(location < 0)
            continue;
        glUniform1i(location, i.value);
    }
    for(auto[str, i] : float_uniforms){
        int location = glGetUniformLocation(program, str.c_str());
        if(location < 0)
            continue;
        glUniform1f(location, i.value);
    }
}

void ComputeProgramStack::RenderImgui() {
    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();
    // ImGui::NewFrame();
    // ImGui::Begin("uniforms");
    //     for(auto&[key, uniform] : int_uniforms){
    //         if(uniform.showImgui){
    //             ImGui::SliderInt(key.c_str(), &uniform.value, uniform.sliderstart, uniform.sliderend);
    //         }
    //     }
    //     for(auto&[key, uniform] : float_uniforms){
    //         if(uniform.showImgui){
    //             ImGui::SliderFloat(key.c_str(), &uniform.value, uniform.sliderstart, uniform.sliderend);
    //         }
    //     }
    // ImGui::End();
    // ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ComputeProgramStack::SetFloat(std::string key, float value) {
    if(float_uniforms.find(key) == float_uniforms.end()){
        AddFloat(key, value, 0.0, 1.0, true);
    }
    else{
        float_uniforms[key].value = value;
    }
}

void ComputeProgramStack::SetInt(std::string key, int value) {
    if(int_uniforms.find(key) == int_uniforms.end()){
        AddInt(key, value, 0, 10, true);
    }
    else{
        int_uniforms[key].value = value;
    }
}

ComputeProgramStack::ComputeProgramStack() {
    
}

ComputeProgramStack::~ComputeProgramStack() {
    
}

void ComputeProgramStack::AddFloat(std::string key, float value, float sliderstart, float sliderEnd, bool show) {
    UniformFloat uniform;
    uniform.value = value;
    uniform.sliderstart = sliderstart;
    uniform.sliderend = sliderEnd;
    uniform.showImgui = show;
    float_uniforms[key] = uniform;
}

void ComputeProgramStack::AddInt(std::string key, int value, int sliderstart, int sliderEnd, bool show) {
    UniformInt uniform;
    uniform.value = value;
    uniform.sliderstart = sliderstart;
    uniform.sliderend = sliderEnd;
    uniform.showImgui = show;
    int_uniforms[key] = uniform;
}

unsigned ComputeProgramStack::CreateSSBO(std::string key, int base){
    unsigned ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, base, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    AddSSBO(key, ssbo, base);

    return ssbo;
}

void ComputeProgramStack::UploadSSBO(unsigned ssbo, void* data, size_t datasize){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, datasize, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ComputeProgramStack::Dispatch(){
    for(auto& [program, x, y, z] : programs){
        glUseProgram(program);

        BindSSBOs(program);
        BindUniforms(program);
        BindTextures(program);
        
        glDispatchCompute(x, y, z);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        glUseProgram(0);
    }
}

void ComputeProgramStack::BindSSBOs(unsigned program) {
    for(auto[ssbo, obj] : ssbos){
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, obj.base, ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    }
}

void ComputeProgramStack::BindTextures(unsigned program) {
    for(auto[texture, obj] : textures){
        glBindImageTexture(obj.binding, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    }
}

void ComputeProgramStack::AddProgram(unsigned program, int x, int y, int z) {
    Program prog;
    prog.program = program;
    prog.x = x;
    prog.y = y;
    prog.z = z;
    programs.push_back(prog);
}

void ComputeProgramStack::AddSSBO(std::string key, unsigned ssbo, int base) {
    SSBO obj;
    obj.key = key;
    obj.base = base;
    ssbos.emplace(ssbo, obj);
}

void ComputeProgramStack::AddTexture(std::string key, unsigned texture, int binding) {
    Texture obj;
    obj.key = key;
    obj.binding = binding;
    textures.emplace(texture, obj);
}
