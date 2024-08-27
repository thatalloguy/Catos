//
// Created by allos on 8/27/2024.
//
#pragma once

#include <stl/string.h>
#include "stl/vector.h"
#include "world/world.h"

namespace catos {

    class ScriptingEngine {

    public:
        static ScriptingEngine& getInstance();

        ScriptingEngine();
        ~ScriptingEngine();


        void registerNewScript(catos::string& pathToPythonFile, catos::string& scriptName);

        std::vector<catos::Script>& getScripts();

    private:

        catos::vector<catos::Script> _scripts;

    };
}

