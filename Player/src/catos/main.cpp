// engine includes
#pragma once
#include <core/application.h>
#include <core/window.h>


using namespace catos;





int main() {


    AppCreationInfo info{};



    App app{&info};



    // Register all classes for reflection


    WindowCreationInfo window_info = {
            .size = { 500, 500 }
    };

    Window window(window_info);


    while (!window.should_window_close()) {
        window.update();
    }


    return 0;
}