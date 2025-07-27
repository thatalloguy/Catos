#pragma once



#include <fstream>
#include "spdlog/spdlog.h"
#include "typeinfo.h"





namespace catos {


    typedef unsigned long long Ref;

    //Core system :)_
    /// The registry is the core system and provides reflection to the rest of the engine
    class Registry {

    public:

        static Registry& get();

        void clean_up();

        template<typename A>
        /// With this function you register a class to the Registry
        TypeInfo& register_class(const std::string& class_name) {


            // This means the user is trying to register a new type!
            if (_register.find(class_name) == _register.end()) {
                _register.insert(std::pair<std::string, TypeInfo>(class_name, TypeInfo{.type_hash = typeid(A).hash_code(), .name=  class_name  }));
                _hash_register.insert(std::pair<size_t, TypeInfo*>(typeid(A).hash_code(), &_register.at(class_name)));
                _register.at(class_name)._constructor.initialize<A>(class_name.c_str(), typeid(A).hash_code());
            }


            return _register[class_name];
        };


        /// Returns the registered Type
        template<typename A>
        TypeInfo& get_type() {
            return get_type(typeid(A).hash_code());
        }

        TypeInfo& get_type(size_t hash) {

            if (_hash_register.find(hash) == _hash_register.end()) {
                spdlog::error("[Reflection] Could not find type: HASH {}", hash);
                throw std::exception("KeyNotFound");
            }

            return *_hash_register[hash];
        }


        const TypeInfo& get_type(const std::string& name) {
            if (_register.find(name) == _register.end()) {
                spdlog::error("[Reflection] Could not find type: {}", name.c_str());
                throw std::exception("KeyNotFound");
            }
            return (_register[name]);
        }

        const std::unordered_map<std::string, TypeInfo>& entries() {
            return _register;
        }

        template<typename T>
        bool is_type_registered() {
            return is_type_registered(typeid(T).hash_code());
        }

        bool is_type_registered(size_t hash) {
            return _hash_register.find(hash) != _hash_register.end();
        }

        bool is_type_registered(const std::string& type_name) {
            return _register.find(type_name) != _register.end();
        }

        Ref get_ref(void* ptr) {
            if (_ptr_register.find(ptr) != _ptr_register.end()) {
                return _ptr_register.at(ptr);
            }


            lastId++;
            _ptr_register.insert({ptr, lastId});

            return lastId;
        };

        bool is_ref_registered(void* ptr) {
            return _ptr_register.find(ptr) != _ptr_register.end();
        }


    private:
        Ref lastId = 0;

        std::unordered_map<std::string, TypeInfo> _register;
        std::unordered_map<size_t, TypeInfo*> _hash_register;
        std::unordered_map<void*, Ref> _ptr_register;
    };
}
