//
// Created by allos on 3/19/2025.
//

#pragma once

#include <unordered_map>

#include "types.h"
#include "method.h"
#include "property.h"
#include "constructor.h"

#ifdef CATOS_SCRIPTING_ENABLED
#include "scripting/ScriptingEngine.h"
#endif



namespace catos {
    /// Typeinfo is an object that holds all information about a specific type.
    class TypeInfo {

    public:

        void destroy() {
            for (auto& pair: properties) {
                delete pair.second;
            }

            for (auto& pair : methods) {
                delete pair.second;
            }

        }

        size_t type_hash;
        std::string name;

        template<typename T, typename U>
        /// Registers a property with a name and a member pointer (Returns itself).
        TypeInfo& property(const char*  property_name, U T::* member, cstr description) {

            if constexpr(!std::is_pointer<U>()) {
                properties[property_name] = new PropertyImpl<T, U>(member);
            } else {
                properties[property_name] = new PointerProperty<T, U>(member);
            }

            properties[property_name]->set_name(property_name);
            properties[property_name]->desc = description;

            // Return itself so that we can keep adding properties without having to write the instance again.
            return *this;
        }


        template<typename U, class T>
        TypeInfo& property(const char* property_name, catos::vector<U> T::* member, cstr description) {
            properties[property_name] = new VectorProperty<T, U>(member);
            properties[property_name]->set_name(property_name);
            properties[property_name]->desc = description;


            return *this;
        }

        template<typename K, typename V, class T>
        TypeInfo& property(const char* property_name, std::unordered_map<K, V> T::* member, cstr description) {
            properties[property_name] = new HashMapProperty<T, K, V>(member);
            properties[property_name]->set_name(property_name);
            properties[property_name]->desc = description;


            return *this;
        }

        template<class T, typename... Args>
        void constructor() {
            _constructor.initialize<T, Args...>(name.c_str(), type_hash);
        }

        TypeInfo& inherits(const std::string& class_name);

        /// Registers a method with a name and a member function pointer (returns the Type object again).
        template<typename ClassT, typename ReturnV, typename... Args>
        constexpr TypeInfo& method(const char* method_name, ReturnV(ClassT::* ptr)(Args...), cstr description) {
            methods[method_name] = new Method{ptr};
            methods[method_name]->desc = description;


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

        ///Returns a method object based on the name given.
        Method* get_method(const char* method_name) {
            auto it = methods.find(method_name);

            if (it != methods.end()) {
                return it->second;
            }

            return nullptr;
        };

        Constructor& get_constructor() {
            return _constructor;
        }


        template<typename T>
        void registerToPython() {
#ifdef CATOS_SCRIPTING_ENABLED
            auto& inst = ScriptingEngine::getInstance();

            auto structPos = name.find("struct");

            if (structPos == std::string::npos) {
                structPos = name.find("class");
            }

            inst.registerClass<T>(name.substr(structPos + 7).c_str());

            for (auto property : properties) {
                property.second->registerToPy();
            }

            for (auto method : methods) {
                method.second->registerToPy(method.first.c_str());
            }
#endif
        };

        ///Checks wether or not the ptr is a nullptr;
        static bool is_valid(Property* ptr) { return ptr != nullptr; };
        static bool is_valid(Method*   ptr) { return ptr != nullptr; };


        catos::Constructor _constructor;
        std::unordered_map<std::string , Property*> properties;
        std::unordered_map<std::string , Method* > methods;

    };
}