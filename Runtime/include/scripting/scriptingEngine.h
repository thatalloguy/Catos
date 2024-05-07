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

        //loading assemblies
        char* read_bytes(const std::string& filepath, uint32_t* outSize);
        MonoAssembly* load_assembly(const std::string& assemblyPath);

        //Util
        void print_assembly_types(MonoAssembly* assembly);
    };


}// catos