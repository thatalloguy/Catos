//
// Created by allos on 4/20/2025.
//
#pragma once

#include <any>
#include "stl/string.h"
#include "types.h"

namespace catos {

    static int cal = 0;

    class Instance {
    public:
        Instance() = default;
        ~Instance() = default;

        Instance(void* ptr, size_t hash, const catos::string& name) {
            _ptr = ptr;
            _type_hash = hash;
            _name = name;
        }

        void* data() const { return _ptr; };
        size_t hash() const { return _type_hash; };
        const catos::string& get_name() const { return _name; };


    private:
        void* _ptr = nullptr;
        size_t _type_hash = 0;
        catos::string _name = "";
    };

    struct ParameterInfo {
        size_t type_hash;
        const catos::string& name;
    };



    template<typename T,typename ...Args>
    class ConstructorInvoker {

    public:

        ConstructorInvoker() = default;

        static void* construct(Args... args) {
            cal++;
            return new T{args...};
        }



    };




    /// Stores a function pointer for running it.
    class Constructor {

    public:

        Constructor() = default;

        template<typename ClassType, typename ... Args>
        void initialize(const catos::string& name, size_t hash) {
            _name = name;
            type_hash = hash;
            ptr = &ConstructorInvoker<ClassType, Args...>::construct;
        };

        ~Constructor() = default;

        template<typename... Args>
        Instance* construct(Args... args) const {
            void* data = std::any_cast<void*(*)(Args...)>(ptr)(args...);
            cal++;
            return new Instance{
                data,
                type_hash,
                _name
            };
        };

        Instance* construct() const {
            void* data = std::any_cast<void*(*)()>(ptr)();
            cal++;
            return new Instance{
                    data,
                    type_hash,
                    _name
            };
        };

        void registerToPy(const char* name) {

        }


        cstr desc = "NONE";
    private:

        std::any ptr;
        catos::string _name = "";
        size_t type_hash = 0;
    };



}

template<typename T>
T* instance_cast(catos::Instance* instance) {
    void* ptr = instance->data();
    delete instance;
    instance = nullptr;

    return (T*) ptr;
}