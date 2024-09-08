// engine includes
#pragma once


#include "world/world.h"
#include "spdlog/spdlog.h"
#include "stl/string.h"
#include "scripting/ScriptingEngine.h"

struct Foo {
    int data = 0;
};


int main() {

    catos::ScriptingEngine& engine = catos::ScriptingEngine::getInstance();

    engine.registerNewScript("../../../Resources/Catos/script_test.py");

    engine.startScripts();

    engine.updateScripts();

    engine.endScripts();

    return 0;
}

