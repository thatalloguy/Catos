#pragma once
#include <TINYSTL/unordered_map.h>
#include <TINYSTL/string.h>
#include <TINYSTL/string_view.h>
#include <iostream>
#include "type_utils.h"

using namespace catos;


using namespace tinystl;

namespace catos {

    class TypeInfo {

    public:
        size_t type_hash;
        string name;


        template<typename U>
        constexpr void property(const char* property_name, U value) {
            //TODO this might not be the way
            properties.emplace(pair<const char* , size_t>(property_name, type_utils::get_type_hash<U>()));
        };


        template<typename A>
        constexpr A get_property(const char*  name) {
            return properties[name];
        };

    //private:
        unordered_map<const char* , size_t> properties;


    };

    struct property {
        string name;
    };


    class Registry {

    public:
        template<typename T>
        constexpr TypeInfo& register_class() {

            size_t hash = type_utils::get_type_hash<T>();

            // This means the user is trying to register a new type!
            if (_register.find(hash) == _register.end()) {
                //TODO check if this is suppose to work like this //update
                _register.insert(pair<size_t, TypeInfo>(hash,
                                 TypeInfo{
                                            .type_hash = hash,
                                            .name = type_utils::get_type_name<T>().c_str()
                                 }
                ));
            }
            return _register[hash];
        };

        //TODO temove this dummy / test function
        // Dummy function!!!
        void print_current_register() {
            for (auto val : _register) {
                TypeInfo& info = val.second;
                std::cout << "Type Name: " << info.name.c_str() << "\n";
                std::cout << "Type Hash: " << info.type_hash << "\n";
                for (auto prop : info.properties) {
                    std::cout << "Type: " << info.name.c_str() << "  | Property name: " << prop.first << "\n";
                    std::cout << "Type: " << info.name.c_str() << "  | Property Hash: " << prop.second << "\n";
                }
            }
        }


    private:
        unordered_map<size_t, TypeInfo> _register;

    };


}



