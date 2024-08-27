// engine includes
#pragma once


#include "scripting/ScriptingEngine.h"

using namespace catos;


int main() {

    py::scoped_interpreter guard{};


    ScriptingEngine& engine = ScriptingEngine::getInstance();

    catos::string str = "../../../Resources/Catos/script_test.py";
    catos::string str2 = "../../../Resources/Catos/another_test.py";

    engine.registerNewScript(str);
    engine.registerNewScript(str2);

    engine.startScripts();
    engine.updateScripts();
    engine.endScripts();


    return 0;
}