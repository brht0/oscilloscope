#ifndef __SOUNDFILE_H__
#define __SOUNDFILE_H__

class SoundFile{
public:
    SoundFile(const char* filename);
    ~SoundFile();

    float* data = nullptr;
    int channels;
    int samplerate;
    int frames;
    int size_in_bytes;
};

#endif // __SOUNDFILE_H__