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

    // Properties :)
    /// See PropertyImpl for details.
    class Property {

    public:
        ///Stores an member pointer to a field of an type.
        /// NOTE see the PropertyImpl for further documentation

        virtual ~Property() {};

        virtual void* get_value(const void* obj_ptr) = 0;
        virtual const char* get_name() = 0;
        virtual const char* get_type_name() = 0;
        virtual size_t& get_type_hash() = 0;

        virtual void set_name(const char* name) = 0;
    };

    /// PropertyImpl implements Property and holds an member function pointer. Used to get an value of an field of an Type's instance.
    template<typename T, typename U>
    class PropertyImpl : public Property {


    private:
        U T::* memberPtr;
        const char* name;


        string type_name;
        size_t type_hash;


    public:
        ///PropertyImpl exist in order to avoid having to deal with templates at the user-side.

        PropertyImpl(U T::* memPtr) : memberPtr(memPtr) {
                type_name = type_utils::get_type_name<U>();
                type_hash = type_utils::get_type_hash<U>();
        };

        /// Set the name of the property
        void set_name(const char* new_name) override {
            name = new_name;
        }




        /// Use Get value (which can be cased to the desired type) to return an value of an instance.
        void* get_value(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);
            return const_cast<void*>(reinterpret_cast<const void*>(&(obj->*memberPtr)));
        }


        /// Get the name of the property
        const char* get_name() override{
            return name;
        }

        /// Returns the name of the fields type.
        const char* get_type_name() override {
            return type_name.c_str();
        };

        /// Returns (a reference of) the type's hash
        size_t& get_type_hash() override {
            return type_hash;
        };
    };

    //Method ;-; | I DID IT RAHHHHHHH



    template<typename ReturnType, class ClassType, typename... Args>
    /// MethodInvoker invokes the method (with args) given at creation.
    class MethodInvoker{

    public:

        ReturnType (ClassType::* memPtr)(Args...);
        MethodInvoker(ReturnType (ClassType::* ptr)(Args...)) {
            memPtr = ptr;
        };
        /// Runs the function
        static ReturnType callFunction(void* FuncInst, void* instance, Args... args) {
            return (static_cast<ClassType*>(instance)->*static_cast<MethodInvoker<ReturnType, ClassType, Args...>*>(FuncInst)->memPtr)(args...);
        }
    };


    /// Stores a function pointer for running it.
    class Method {

    public:
        template<typename ReturnType, class ClassType, typename... Args>
        Method(ReturnType(ClassType::* method)(Args...)) {
            _mFunc = MethodInvoker<ReturnType, ClassType, Args...>(method);

            ptr = &MethodInvoker<ReturnType, ClassType, Args...>::callFunction;
        };


        template<typename R, typename... Args>
        R invoke_function(void* instance, Args... args) {
            return std::any_cast<R(*)(void*, void*, Args...)>(ptr)(&_mFunc, instance, args...);
        };

        template<typename... Args>
        void invoke_function(void* instance, Args... args) {
            std::any_cast<void(*)(void*, void*, Args...)>(ptr)(&_mFunc, instance, args...);
        };

    private:
        std::any ptr;
        std::any _mFunc;
    };






    //Type
    /// Typeinfo is an object that holds all information about a specific type.
    class Type {

    public:


        size_t type_hash;
        string name;


        template<typename T, typename U>
        /// Registers a property with a name and a member pointer (Returns itself).
        Type& property(const char*  property_name, U T::* member) {



            properties[property_name] = new PropertyImpl<T, U>(member);
            properties[property_name]->set_name(property_name);


            // Return itself so that we can keep adding properties without having to write the instance again.
            return *this;
        }

        /// Registers a method with a name and a member function pointer (returns the Type object again).
        template<typename ClassT, typename ReturnV, typename... Args>
        constexpr Type& method(const char* method_name, ReturnV(ClassT::* ptr)(Args...)) {
            methods[method_name] = new Method{ptr};

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


        ///Checks wether or not the ptr is a nullptr;
        static bool is_valid(Property* ptr) { return ptr != nullptr; };
        static bool is_valid(Method*   ptr) { return ptr != nullptr; };

        unordered_map<string , Property* > properties;
        unordered_map<string , Method* > methods;
    };

    //Core system :)_
    /// The registry is the core system and provides reflection to the rest of the engine
    class Registry {

    public:

        template<typename A>
        /// With this function you register a class to the Registry
        Type& register_class() {

            size_t hash = type_utils::get_type_hash<A>();

            // This means the user is trying to register a new type!
            if (_register.find(hash) == _register.end()) {
                _register.insert(pair<size_t, Type>(hash, Type{.type_hash = hash, .name=  type_utils::get_type_name<A>()  }));
            }


            return _register[hash];
        };

        //TODO add more util funcs

        /// Used to bind an instance to an type
        template<typename A>
        void bind(const void* instance) {
            _instance_register[type_utils::get_type_hash<A>()] = instance;
        };

        /// Returns the registered instance
        template<typename A>
         A* get() {
            A* obj = (A*) (_instance_register[type_utils::get_type_hash<A>()]);
            return obj;
        }

        /// Returns the registered Type
        template<typename A>
        Type& get_type() {
            return (_register[type_utils::get_type_hash<A>()]);
        }

        //TODO Dummy function!!!
        /// Prints out the items in the Registry
        void print_current_register() {
            for (auto val : _register) {
                Type& info = val.second;
                std::cout <<  info.name.c_str() << " { \n";

                for (auto& prop : info.properties) {

                    std::cout << "     " << prop.second->get_type_name() << " " << prop.second->get_name() << ";\n";
                }
                std::cout << "}\n";
            }
        }




    private:
        unordered_map<size_t, Type> _register;
        unordered_map<size_t, const void* > _instance_register;
    };
}



