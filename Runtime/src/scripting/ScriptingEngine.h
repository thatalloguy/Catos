//
// Created by allos on 8/27/2024.
//
#pragma once

#include <stl/string.h>
#include "stl/vector.h"
#include "stl/pair.h"


#include "stl/hashmap.h"
#include <pocketpy/pocketpy.h>
#include <pybind11.h>

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

        };

        template<class T, typename U>
        void registerProperty(const char* name, T::U* ptr) {

        }

        template<class T, typename U>
        void registerMethod(const char* name, T::U* ptr) {

        }

    private:

        py::scoped_interpreter* interpreter = nullptr;


        catos::hashmap<size_t, void*> _pythonClassInstances;
        catos::vector<catos::Pair<py::object* , ScriptInfo>> _scripts;

    };
}




