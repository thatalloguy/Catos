//
// Created by allos on 5/5/2024.
//

#include <iostream>
#include "scripting/scriptingEngine.h"
#include "mono/metadata/assembly.h"

void catos::ScriptingEngine::init() {

    _context = new ScriptContext;


    init_mono();
}

void catos::ScriptingEngine::clean_up() {




    delete _context;
}

void catos::ScriptingEngine::init_mono() {
    mono_set_assemblies_path("../../Thirdparty/Mono/lib/");

    MonoDomain* rootDomain = mono_jit_init("CatosSharpRuntime");
    if (rootDomain == nullptr) {
        std::cerr << "Could not initialize CatosSharpRuntime.\n";
        return;
    }

    _context->_rootDomain = rootDomain;

    //Create an App domain;                                         /// Mono is a little cry baby so we have to use strdup here.
    _context->_appDomain = mono_domain_create_appdomain(strdup("MyAppDomain"), nullptr);
    mono_domain_set(_context->_appDomain, true);
}
