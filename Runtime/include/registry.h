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
        ///Stores an member pointer to a field of an type.
        /// NOTE see the PropertyImpl for further documentation

        virtual ~Property() {};

        virtual void* get_value(const void* obj_ptr) = 0;
        virtual const char* get_name() = 0;
        virtual void set_name(const char* name) = 0;
    };

    template<typename T, typename U>
    class PropertyImpl : public Property {
    private:
        U T::* memberPtr;
        const char* name;
    public:
        ///PropertyImpl exist in order to avoid having to deal with templates at the user-side.

        constexpr PropertyImpl(U T::* memPtr) : memberPtr(memPtr) {};

        /// Use Get value (which can be cased to the desired type) to return an value of an instance.
        void* get_value(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);
            return const_cast<void*>(reinterpret_cast<const void*>(&(obj->*memberPtr)));
        }

        /// Set the name of the property
        void set_name(const char* new_name) override {
            name = new_name;
        }

        /// Get the name of the property
        const char* get_name() override{
            return name;
        }
    };


    /// Typeinfo is an object that holds all information about a specific type.
    class TypeInfo {

    public:


        size_t type_hash;
        string name;
        bool is_deleted = false;


        template<typename T, typename U>
        /// Registers a property with a name and a member pointer (Returns itself).
        constexpr TypeInfo& property(const char*  property_name, U T::* member) {

            properties[property_name] =  new PropertyImpl<T, U>(member);
            properties[property_name]->set_name(property_name);


            // Return itself so that we can keep adding properties without having to write the instance again.
            return *this;
        }

        /// Returns a property object based on the name given.
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


    /// The registry is the core system and provides reflection to the rest of the engine
    class Registry {

    public:

        template<typename A>
        /// With this function you register a class to the Registry
        constexpr TypeInfo& register_class() {

            size_t hash = type_utils::get_type_hash<A>();

            // This means the user is trying to register a new type!
            if (_register.find(hash) == _register.end()) {
                _register.insert(pair<size_t, TypeInfo>(hash, TypeInfo{.type_hash = hash, .name=  type_utils::get_type_name<A>()  }));
            }


            return _register[hash];
        };



        //TODO Dummy function!!!
        /// Prints out the items in the Registry
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



