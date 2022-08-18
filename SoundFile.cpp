#include "SoundFile.hpp"

#include "sndfile.h"
#include "AL/al.h"

#include <bits/stdc++.h>

SoundFile::SoundFile(const char* filename) {
    ALenum err, format;
    ALuint buffer;
    SNDFILE *sndfile;
    SF_INFO sfinfo;

    // Open audio file and check for errors
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if(!sndfile){
        fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
    }
    if(sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX/sizeof(short))/sfinfo.channels)
    {
        fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
        sf_close(sndfile);
    }

    // Load data and number of frames
    data = new float[sfinfo.frames * sfinfo.channels];
    frames  = sf_readf_float(sndfile, data, sfinfo.frames);
    channels = sfinfo.channels;
    samplerate = sfinfo.samplerate;
    size_in_bytes = sfinfo.frames * sfinfo.channels * sizeof(float);

    if(frames < 1)
    {
        sf_close(sndfile);
        std::cout << "error loading file\n";
    }

    // Free memory
    sf_close(sndfile);
}

SoundFile::~SoundFile() {
    if(data){
        delete[] data;
        data = nullptr;
    }
}
