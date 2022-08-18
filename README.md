# Oscillator
Inspired by Jerobeam Fenderson's videos: https://www.youtube.com/watch?v=19jv0HM92kw

### Notes
- Only works on some file formats (e.g. ogg)

### Tested on:
- Ubuntu 22.04

### Dependencies
- OpenGL (GLFW 3)
- OpenAL (openal-soft)
- sndfile

### How to use:
```
git clone git@github.com:brht0/oscilloscope.git && cd oscilloscope
make
./oscilloscope <path_to_song>
```
### Todo:
- Some code (e.g. ComputeProgramStack) are loose copy/pastes with some modifications from my other projects, should be simplified
- OpenAL errors
- Deallocation of GLFW/OpenAL, pretty much everything
- oscilloscope.comp needs a linedraw function with thickness
- Random constants in source files
- Naming variables consistantly to avoid future headaches
- Windows support
