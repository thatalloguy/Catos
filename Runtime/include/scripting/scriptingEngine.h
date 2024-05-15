//
// Created by allos on 5/5/2024.
//

/// Note when calling a onUpdate function please use Unmanaged Method Thunks.!!!

#pragma once

#include "mono/jit/jit.h"


namespace catos {

    enum class FieldAccessibility : uint8_t  {
        None = 0,
        Private = (1 << 0),
        Internal = (1 << 1),
        Protected = (1 << 2),
        Public = (1 << 3)
    };


    struct ScriptContext {
        MonoDomain* _rootDomain = nullptr;
        MonoDomain*  _appDomain = nullptr;

        MonoAssembly* _mainAssembly = nullptr;
    };

    struct Cpp {
        int name;
        void printCpp(int age) {
            std::cout << "My name is: " << name << "\n";
            std::cout << "My Age is: " << age << "\n";
        };
    };

    class ScriptingEngine {
    public:

        void init();
        void run();
        void clean_up();


        ///Test




        template<typename T, auto Func, typename... Args>
        static void static_function(T& instance, Args... args) {
            (instance.*Func)(args...);
        }


        ///TODO intergrate this with the reflection system
        template<typename T, auto Func, typename... Args>
        static void embed_function(const char* name) {
            mono_add_internal_call(std::string(std::string("catos.LibNative::") + name + std::string("_native")).c_str(), reinterpret_cast<void(*)(Args...)>(static_function<T, Func, Args...>));
        }

        static bool check_mono_error(MonoError& error);
        static  std::string mono_string_to_string(MonoString* monoString);


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

        //Fields
        uint8_t get_field_accessibility(MonoClassField* field);
        uint8_t get_property_accessbility(MonoProperty* property);


        ///Test


    };


}// catos