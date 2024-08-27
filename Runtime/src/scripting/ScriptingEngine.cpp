//
// Created by allos on 8/27/2024.
//

#include "ScriptingEngine.h"
#include "spdlog/spdlog.h"

PYBIND11_EMBEDDED_MODULE(catos, m) {

    py::class_<Script>(m, "Script")
            .def(py::init<>())
            .def("update", &Script::update)
            .def("end", &Script::end);
}

catos::ScriptingEngine &catos::ScriptingEngine::getInstance() {
    static catos::ScriptingEngine instance{};
    return instance;
}

catos::ScriptingEngine::ScriptingEngine() {

}

catos::ScriptingEngine::~ScriptingEngine() {

}

void catos::ScriptingEngine::registerNewScript(catos::string &pathToPythonFile) {


    try {

        /// First read the contents of the file given to us and validate it.
        std::ifstream file(pathToPythonFile.c_str());


        if(!file.is_open()){
            std::cerr << "Could not open file" << std::endl;
            throw -405;
        }


        std::stringstream buffer;
        buffer << file.rdbuf();

        /// Create a scriptInfo
        ScriptInfo scriptInfo;
        scriptInfo.src = buffer.str().c_str();



        /// Find the name of the user defined script object
        std::string srcCode = buffer.str();

        auto end = srcCode.find("(catos.Script");
        auto start = srcCode.find("class ");

        if (end != srcCode.npos && start != srcCode.npos) {
            scriptInfo.className = srcCode.substr(start + 6, end - (start + 6)).c_str();
            spdlog::debug("Script found {}", scriptInfo.className.c_str());

        } else {
            spdlog::error("Could not Find script class in {}", pathToPythonFile.c_str());

            throw -406;
        }




        /// Do a nullptr here cuz we allocate the mem for a script obj in the ScriptingEngine::startScripts();
        _scripts.push_back({nullptr, scriptInfo});



    } catch (int e) {
        spdlog::error("{}", e);
    }


}

void ScriptingEngine::startScripts() {


    for (int i = 0; i<_scripts.length(); i++) {
        auto& pair = _scripts[i];
        /// execute the script;
        py::exec(pair.second.src.c_str());

        if (pair.first == nullptr) {

            auto t = (pair.second.className + catos::string("()"));

            pair.first = new py::object(py::eval(t.c_str()));
        }
    }
}

void ScriptingEngine::updateScripts() {

    for (int i = 0; i<_scripts.length(); i++) {
        auto& pair = _scripts[i];
        auto obj = pair.first;

        if (obj != nullptr) {
            obj->attr("update")();
        }
    }
}

void ScriptingEngine::endScripts() {

    py::scoped_interpreter guard{};
    for (int i = 0; i<_scripts.length(); i++) {
        auto obj = _scripts[i].first;

        if (obj != nullptr) {
            obj->attr("end")();
            delete obj;
        }
    }
}