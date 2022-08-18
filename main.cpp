#include "GLWrapper.hpp"
#include "App.hpp"

#include <iostream>
#include <unistd.h>

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Usage: " << argv[0] << " <song_file>" << std::endl;
        exit(0);
    }

    auto gl = GL::get();
    const char* songfile = argv[1];

    const int w = 512;
    const int h = 512;

    auto window = gl->Init("Oscilloscope", w, h);
    App* app = new App(w, h);
    app->LoadSoundFile(argv[1]);

    while(!app->ShouldClose()){
        app->Update();
        app->Render();
        
        glfwSwapBuffers(gl->GetWindow());
        glfwPollEvents();

        usleep(1000);
    }

    delete app;
    return 0;
}
