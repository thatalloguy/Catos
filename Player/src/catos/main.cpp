// engine includes
#pragma once

#include <pybind11/pybind11.h>
#include "spdlog/spdlog.h"


namespace py = pybind11;
struct Point {
    float x;
    float y;

    Point(float x, float y) : x(x), y(y) {}
};

Point& return_point() {
    static Point p{1.0, 2.0};
    return p;
}


void registerPython(py::module_& mod) {
    py::class_<Point>(mod, "Point")
            .def(py::init<float, float>())
            .def_readwrite("x", &Point::x)
            .def_readwrite("y", &Point::y);

    mod.def("return_point", &return_point, py::return_value_policy::reference);

}


PYBIND11_EMBEDDED_MODULE(catos, m) {
    registerPython(m);
}


int main() {
    py::scoped_interpreter guard{};



    try {
        py::exec(R"(

import catos

p = catos.return_point()
p.x = 3.0
p.y = 5.0
print(p.x, p.y)
    )");

        py::print(return_point().x, return_point().y);
    } catch (py::error_already_set& e) {
        spdlog::error("{}", e.summary());
    }

    // => 3.0 4.0

    return 0;
}