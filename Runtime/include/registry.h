#pragma once
#include <TINYSTL/unordered_map.h>
#include <TINYSTL/string.h>
#include <TINYSTL/string_view.h>
#include <iostream>
#include <any>
#include "type_utils.h"

using namespace catos;


using namespace tinystl;

namespace catos {


    class Property {

    public:
        virtual ~Property() {};
        virtual void* get_value(const void* obj_ptr) = 0;
    };

    template<typename T, typename U>
    class PropertyImpl : public Property {
    private:
        U T::* memberPtr;

    public:

        constexpr PropertyImpl(U T::* memPtr) : memberPtr(memPtr) {};
        
        void* get_value(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);
            return const_cast<void*>(reinterpret_cast<const void*>(&(obj->*memberPtr)));
        }
    };


    class TypeInfo {

    public:
        size_t type_hash;
        string name;
        bool is_deleted = false;


        template<typename T, typename U>
        constexpr TypeInfo& property(const char*  property_name, U T::* member) {

            properties[property_name] =  new PropertyImpl<T, U>(member);


            // Return itself so that we can keep adding properties without having to write the instance again.
            return *this;
        }

        Property* get_property(const char* property_name) {
          auto it = properties.find(property_name);


          if (it != properties.end()) {
              return it->second;
          }

          //TODO replace with logger
          std::cerr << "Could not find property\n";

          return nullptr;
        };

        unordered_map<string , Property* > properties;
    };


    class Registry {

    public:


        template<typename A>
        constexpr TypeInfo& register_class() {

            size_t hash = type_utils::get_type_hash<A>();

            // This means the user is trying to register a new type!
            if (_register.find(hash) == _register.end()) {
                _register.insert(pair<size_t, TypeInfo>(hash, TypeInfo{.type_hash = hash, .name=  type_utils::get_type_name<A>()  }));
            }


            return _register[hash];
        };



        //TODO Dummy function!!!
        void print_current_register() {
            for (auto val : _register) {
                TypeInfo& info = val.second;
                std::cout << "Type Name: " << info.name.c_str() << "\n";
                std::cout << "Type Hash: " << info.type_hash << "\n";

                for (auto& prop : info.properties) {

                    std::cout << "Type: " << info.name.c_str() << "  | Property name: " << prop.first.c_str() << "\n";
                    std::cout << "Type: " << info.name.c_str() << "  | Property Pointer: " << prop.second << "\n";
                }

            }
        }


    private:
        unordered_map<size_t, TypeInfo> _register;

    };


}



