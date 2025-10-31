//
// Created by allos on 26/06/2025.
//
// Note: Both credits to Nyx and Skore for the whole DLL loading idea.
// Extra note: Nyx is a private engine developed by both me, daethalus and chukobyte.
#pragma once
#include <stl/string.h>

#ifdef _WIN64
#include <Windows.h>
#elif __linux___
#include <dlfcn.h>
#endif

namespace catos {

    class Registry;

    typedef void(* PluginEntryPointFn)(Registry* registry);
    typedef void(* PluginUpdatePointFn)(float delta_time);
    typedef void(* PluginRenderPointFn)();
    typedef void(* PluginRenderPointFn)();


    class Platform {
    public:
        Platform() = default;
        ~Platform() = default;

        void* load_shared_library(const string& path);
        void free_shared_library(void* library);
        void* get_proc_adress(void* library, const string& name);
    };

#ifdef _WIN64


    inline void* Platform::load_shared_library(const string &path) {
        return LoadLibraryA(path.c_str());
    }

    inline void Platform::free_shared_library(void *library) {
        FreeLibrary((HMODULE) library);
    }

    inline void *Platform::get_proc_adress(void *library, const string &name) {
        return (void*) GetProcAddress((HMODULE) library, name.c_str());
    }

#elif __linux__

    inline void* Platform::load_shared_library(const string &path) {
        return dlopen(path.c_str(), RTLD_NOW);
    }

    inline void Platform::free_shared_library(void *library) {
        dlclose(library);
    }

    inline void *Platform::get_proc_adress(void *library, const string &name) {
        return dlsym(library, name.c_str());
    }

#else


    inline void* Platform::load_shared_library(const string &path) {
        return nullptr;
    }

    inline void Platform::free_shared_library(void *library) {

    }

    inline void *Platform::get_proc_adress(void *library, const string &name) {
        return nullptr;
    }
#endif


}
