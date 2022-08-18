#ifndef __AUDIOPLAYER_H__
#define __AUDIOPLAYER_H__

#include "SoundFile.hpp"

class AudioPlayer{
public:
    AudioPlayer();
    ~AudioPlayer();

    void SetFile(SoundFile* newFile);

    void SetTime(float time);
    float GetTime();

    void TogglePause();

private:
    unsigned buffer = 0;
    unsigned source = 0;

    SoundFile* m_File = nullptr;

private:
    static void LoadFile(SoundFile* file, unsigned source, unsigned buffer);
};

#endif // __AUDIOPLAYER_H__