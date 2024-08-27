// engine includes
#pragma once


#include <pybind11/pybind11.h>
#include <fstream>
#include "spdlog/spdlog.h"
#include "core/window.h"


namespace py = pybind11;
using namespace catos;


class Script {

public:

    Script() {};
    void update() {};
    void end() {};

};


void registerPython(py::module_& m) {


    py::class_<math::Vector2>(m, "Vector2")
            .def(py::init<float, float>())
            .def_readwrite("x", &math::Vector2::x)
            .def_readwrite("y", &math::Vector2::y);

    py::class_<WindowCreationInfo>(m, "WindowCreationInfo")
            .def(py::init<>())
            .def_readwrite("size", &WindowCreationInfo::size)
            .def_readwrite("position", &WindowCreationInfo::size)
            .def_readwrite("title", &WindowCreationInfo::title)
            .def_readwrite("is_fullscreen", &WindowCreationInfo::is_fullscreen)
            .def_readwrite("borderless", &WindowCreationInfo::borderless)
            .def_readwrite("enable_darktheme", &WindowCreationInfo::enable_darktheme);

    py::class_<Window>(m, "Window")
            .def(py::init<WindowCreationInfo&>())
            .def("update", &Window::update)
            .def("shouldClose", &Window::should_window_close);

    py::class_<Script>(m, "Script")
            .def(py::init<>())
            .def("update", &Script::update)
            .def("end", &Script::end);


}


PYBIND11_EMBEDDED_MODULE(catos, m) {
    registerPython(m);
}


int main() {
    py::scoped_interpreter guard{};


    try {
        std::ifstream file("../../../catos.py");
        if(!file.is_open()){
            std::cerr << "Could not open file" << std::endl;
            return 1;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string script = buffer.str();

        try{

            py::exec(script);

            auto script = new py::object(py::eval("ScriptTest()"));

            script->attr("update")();
            script->attr("end")();

            delete script;

        }catch(py::error_already_set& e){
            std::cerr << e.summary() << std::endl;
        }

    } catch (py::error_already_set& e) {
        spdlog::error("{}", e.summary());
    }


    return 0;
}