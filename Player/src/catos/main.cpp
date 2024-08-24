// engine includes
#pragma once
#include <core/application.h>
#include <core/window.h>
#include "world/world.h"

#include <pybind11/pybind11.h>


using namespace catos;

namespace py = pybind11;



int main() {

/*

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

*/


    py::scoped_interpreter guard{};

    py::exec("print('Hello World')");


    return 0;
}