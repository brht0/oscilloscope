#ifndef __APP_H__
#define __APP_H__

#include "GLWrapper.hpp"

#include "ComputeProgramStack.hpp"
#include "Shader.hpp"
#include "Utils.hpp"

#include "SoundFile.hpp"
#include "AudioPlayer.hpp"

class App{
public:
    App(int w, int h);
    ~App();

    void LoadSoundFile(const char* filename);

    void Render();
    void Update();

    bool ShouldClose();

private:
    const int num_drawn_frames = 2048; // audio frames in oscilloscope

    SoundFile* soundfile = nullptr;
    AudioPlayer player;
    ComputeProgramStack computeStack;

    unsigned texture;
    unsigned texture_fbo;

    unsigned ampSSBO;
    unsigned freqSSBO;
};

#endif // __APP_H__