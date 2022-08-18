#include "AudioPlayer.hpp"

#include "AL/al.h"
#include "AL/alext.h"

#include <iostream>

AudioPlayer::AudioPlayer()
{
    // create AL buffer and source
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, (ALint)buffer);

    if(alGetError() != AL_NO_ERROR){
        std::cout << "Failed to setup sound source\n";
    }
}

AudioPlayer::~AudioPlayer() {
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}

void AudioPlayer::SetFile(SoundFile* file) {
    if(file){
        LoadFile(file, source, buffer);
    }

    auto err = alGetError();
    if(err != AL_NO_ERROR){
        fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
        if(buffer && alIsBuffer(buffer)){
            alDeleteBuffers(1, &buffer);
        }
    }

    m_File = file;
}

void AudioPlayer::SetTime(float time) {
    alSourcePause(source);
    alSourcef(source, AL_SEC_OFFSET, time);
    alSourcePlay(source);
}

float AudioPlayer::GetTime() {
    float time;
    alGetSourcef(source, AL_SEC_OFFSET, &time);
    return time;
}

void AudioPlayer::TogglePause() {
    int paused;
    alGetSourcei(source, AL_PAUSED, &paused);

    if(paused){
        alSourcePlay(source);
    }
    else{
        alSourcePause(source);
    }
}

void AudioPlayer::LoadFile(SoundFile* file, unsigned source, unsigned buffer) {
    int format = AL_NONE;
    int channels = file->channels;
    float* data = file->data;
    int size_in_bytes = file->size_in_bytes;
    int samplerate = file->samplerate;

    if(channels == 1){
        format = AL_FORMAT_MONO_FLOAT32;
    }
    else if(channels == 2){
        format = AL_FORMAT_STEREO_FLOAT32;
    }

    // create AL buffer and source again
    // this is a kind of hacky that I only reserve for special occasions
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, data, size_in_bytes, samplerate);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, (ALint)buffer);

    if(alGetError() != AL_NO_ERROR){
        std::cout << "Failed to setup sound source\n";
    }
}
