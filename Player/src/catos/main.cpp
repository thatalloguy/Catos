// engine includes
#pragma once

#include <core/window.h>


int main() {

    catos::Window window{catos::WindowCreationInfo{
        {1280, 720},
        {0.0f, 0.0f},
        "Hello SDL CATOS!",

    }};

    while (!window.should_window_close()) {
        window.update();


    }

    return 0;
}

