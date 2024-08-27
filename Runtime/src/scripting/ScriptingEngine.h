//
// Created by allos on 8/27/2024.
//
#pragma once

#include <core/registry.h>
#include <stl/string.h>
#include "stl/vector.h"
#include "world/world.h"
#include "pybind11/internal/class.h"
#include "stl/pair.h"

#include <pybind11/pybind11.h>

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

        void registerNewScript(catos::string& pathToPythonFile);

        void startScripts();
        void updateScripts();
        void endScripts();


    private:




        catos::vector<catos::Pair<py::object* , ScriptInfo>> _scripts;

    };
}




