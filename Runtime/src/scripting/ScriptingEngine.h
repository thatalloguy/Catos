//
// Created by allos on 8/27/2024.
//
#pragma once

#include <stl/string.h>
#include "stl/vector.h"
#include "stl/pair.h"


#include "stl/hashmap.h"
#include <pocketpy.h>
#include <pybind11/pybind11.h>

#include <any>

namespace py = pybind11;



namespace catos {

    /// Object that holds info about a Script.
    struct ScriptInfo {
        catos::string src;
        catos::string className;

    };



    class ScriptingEngine {

    public:

        friend class Registry;

        /// singleton :D
        static ScriptingEngine& getInstance();

        ScriptingEngine();
        ~ScriptingEngine();

        void registerNewScript(const catos::string& pathToPythonFile);

        void startScripts();
        void updateScripts();
        void endScripts();


        template<class T>
        void registerClass(const char* name) {

            py::class_<T> pyClass = py::class_<T>(catosPyMod, name).def(py::init<>());
            auto hash = typeid(T).hash_code();

            _pythonClasses.put(hash, pyClass);
        };

        template<typename T, typename U>
        void registerProperty(const char* name, U T::* ptr) {
            auto hash = typeid(T).hash_code();

            auto obj = _pythonClasses.get(hash);

            auto pyClass = std::any_cast<py::class_<T>>(obj);


            pyClass.def_readwrite(name, ptr);
        }

        template<class T, typename U>
        void registerMethod(const char* name, U T::* ptr) {
            auto hash = typeid(T).hash_code();

            auto obj = _pythonClasses.get(hash);

            auto pyClass = std::any_cast<py::class_<T>>(obj);

            pyClass.def(name, ptr);
        }

    private:

        py::scoped_interpreter* interpreter = nullptr;
        py::module catosPyMod;

        catos::hashmap<size_t, std::any> _pythonClasses;
        catos::vector<catos::Pair<py::object* , ScriptInfo>> _scripts;

    };
}




