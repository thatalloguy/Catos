//
// Created by allos on 5/5/2024.
//

/// Note when calling a onUpdate function please use Unmanaged Method Thunks.!!!

#pragma once

#include "mono/jit/jit.h"

namespace catos {

    struct ScriptContext {
        MonoDomain* _rootDomain = nullptr;
        MonoDomain*  _appDomain = nullptr;

        MonoAssembly* _mainAssembly = nullptr;
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
        void call_print_method(MonoObject* objectInstance);


        //Class
        MonoClass* get_class_in_assembly(MonoAssembly* assembly, const char* namespaceName, const char* className);
        MonoObject* instantiate_class(const char* namespaceName, const char* className);
    };


}// catos