//
// Created by allos on 5/5/2024.
//
#pragma once

#include "mono/jit/jit.h"

namespace catos {

    struct ScriptContext {
        MonoDomain* _rootDomain = nullptr;
        MonoDomain*  _appDomain = nullptr;
    };


    class ScriptingEngine {
    public:

        void init();

        void clean_up();


    private:


        ScriptContext* _context;

        void init_mono();

    };


}// catos