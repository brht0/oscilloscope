#include "App.hpp"

#include <iostream>

App::App(int w, int h) {
    auto gl = GL::get();
    texture = gl->CreateTexture(w, h, GL_RGBA32F);
    texture_fbo = gl->CreateTextureFBO(texture);

    // add programs
    computeStack.AddProgram(CreateComputeShader(LoadFile("shaders/oscilloscope.comp"), "oscilloscope"), num_drawn_frames, 1, 1);

    // create and add ssbo
    ampSSBO = computeStack.CreateSSBO("amplitudeData", 0);

    // add textures
    computeStack.AddTexture("screen", texture, 0);
    
    // add other uniforms
    computeStack.SetInt("screenW", w);
    computeStack.SetInt("screenH", h);
}

App::~App() {
    
}

void App::LoadSoundFile(const char* filename) {
    if(soundfile){
        delete soundfile;
        soundfile = nullptr;
    }
    soundfile = new SoundFile(filename);

    // Set uniforms
    computeStack.SetInt("channels", soundfile->channels);
    computeStack.SetInt("samplerate", soundfile->samplerate);

    // Upload entire sound data to GPU (might be problematic)
    computeStack.UploadSSBO(ampSSBO, soundfile->data, soundfile->size_in_bytes); 

    // Audio player
    player.SetFile(soundfile);
    player.TogglePause();
}

void App::Render() {
    auto gl = GL::get();

    gl->ClearTexture(0.0, 0.0, 0.0, 1.0, texture_fbo);
    computeStack.Dispatch();
    gl->RenderTexture(texture);
}

void App::Update() {
    double time = player.GetTime();

    computeStack.SetFloat("time", time);
}

bool App::ShouldClose() {
    auto gl = GL::get();
    return glfwWindowShouldClose(gl->GetWindow()) || (glfwGetKey(gl->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS);
}
