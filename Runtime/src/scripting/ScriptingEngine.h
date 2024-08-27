//
// Created by allos on 8/27/2024.
//
#pragma once

namespace catos {

    class ScriptingEngine {

    public:
        static ScriptingEngine& getInstance();

        ScriptingEngine();
        ~ScriptingEngine();

    };
}

