#pragma once


#include <unordered_map>
#include <iostream>
#include <any>
#include "type_utils.h"
#include "types.h"
#include "mono/metadata/loader.h"
#include <functional>
#include <deque>
#include <fstream>

using namespace catos;




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

        cstr desc = "NONE";
    };

    /// PropertyImpl implements Property and holds an member function pointer. Used to get an value of an field of an Type's instance.
    template<typename T, typename U>
    class PropertyImpl : public Property {


    public:
        U T::* memberPtr;
        const char* name;


        std::string type_name;
        size_t type_hash;

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
        Method(ReturnType(ClassType::* method)(Args...), bool doCoolShit = false) {
            _mFunc = MethodInvoker<ReturnType, ClassType, Args...>(method);


            ptr = &MethodInvoker<ReturnType, ClassType, Args...>::callFunction;


            returnName = type_utils::get_type_name<ReturnType>();
        };


        template<typename R, typename... Args>
        R invoke_function(void* instance, Args... args) {
            return std::any_cast<R(*)(void*, void*, Args...)>(ptr)(&_mFunc, instance, args...);
        };

        template<typename... Args>
        void invoke_function(void* instance, Args... args) {
            std::any_cast<void(*)(void*, void*, Args...)>(ptr)(&_mFunc, instance, args...);
        };


        cstr desc = "NONE";
        std::string returnName = "void";
    private:

        std::any ptr;
        std::any _mFunc;
    };






    //Type
    /// Typeinfo is an object that holds all information about a specific type.
    class TypeInfo {

    public:

        size_t type_hash;
        std::string name;


        template<typename T, typename U>
        /// Registers a property with a name and a member pointer (Returns itself).
        TypeInfo& property(const char*  property_name, U T::* member, cstr description) {



            properties[property_name] = new PropertyImpl<T, U>(member);
            properties[property_name]->set_name(property_name);
            properties[property_name]->desc = description;



            // Return itself so that we can keep adding properties without having to write the instance again.
            return *this;
        }

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


        ///Checks wether or not the ptr is a nullptr;
        static bool is_valid(Property* ptr) { return ptr != nullptr; };
        static bool is_valid(Method*   ptr) { return ptr != nullptr; };

        std::unordered_map<std::string , Property* > properties;
        std::unordered_map<std::string , Method* > methods;
    };

    //Core system :)_
    /// The registry is the core system and provides reflection to the rest of the engine
    class Registry {

    public:



        template<typename A>
        /// With this function you register a class to the Registry
        TypeInfo& register_class() {

            size_t hash = type_utils::get_type_hash<A>();

            // This means the user is trying to register a new type!
            if (_register.find(hash) == _register.end()) {
                _register.insert(std::pair<size_t, TypeInfo>(hash, TypeInfo{.type_hash = hash, .name=  type_utils::get_type_name<A>()  }));
            }


            return _register[hash];
        };


        /// Deprecated!!!
        void gen_python_bindings_file() {
            std::ofstream out("../../catos.py");

            out << R"(""")" << "\n";

            out << "The Python version of The Catos Game engine\n"
                << "The python api is automatically generated by Catos\n"
                << "NOTE: This API is only for scripting. \n";

            out << R"(""")" << "\n";
            for (auto type : _register) {

                auto namespacePos = type.second.name.find("::");
                auto structPos = type.second.name.find("struct");



                if (namespacePos != std::string::npos) {
                    out << "class " << type.second.name.substr(namespacePos + 2) << ":\n";
                } else {
                    out << "class " << type.second.name.substr(structPos + 7) <<  ":\n";
                }

                for (auto prop : type.second.properties) {
                    out << R"(      """ )" << prop.second->desc <<  R"( """ )" << std::endl;
                    out << "      " << prop.first << " = None\n";
                }

                for (auto meth : type.second.methods) {



                    if (meth.first == "init" || meth.first == "Init") {
                        out << R"(      """ )" << meth.second->desc <<   R"(    """ )" << std::endl;
                        out << "      def __init__(self):\n            pass\n";
                    } else {
                        out << "      def " << meth.first << "(self)";
                        if (meth.second->returnName != "void") { out << " -> " << meth.second->returnName << ":\n"; } else { out << ":\n"; }
                        out << R"(          """ )" << meth.second->desc <<   R"( """ )" << std::endl;
                        out << "          pass\n";
                    }
                }
            }

            out.close();
        }

        void gen_cs_bindings_file() {
            std::ofstream out("../../catos.cs");

            out << "///Catos Lib (auto generated)\n";
            out << "namespace catos {\n \n";
            for (auto& type : _register) {

                auto namespacePos = type.second.name.find("::");
                auto structPos = type.second.name.find("struct");



                if (namespacePos != std::string::npos) {
                    out << "struct " << type.second.name.substr(namespacePos + 2) << " {\n";
                } else {
                    out << "struct " << type.second.name.substr(structPos + 7) <<  " {\n";
                }

                for (auto& prop : type.second.properties) {
                    out << "      /*" << prop.second->desc <<  "*/\n";
                    out << "      public " << prop.second->get_type_name() << " " <<  prop.second->get_name() << ";\n" ;
                }

                for (auto meth : type.second.methods) {

                    auto nPos = meth.second->returnName.find("::");
                    auto sPos = meth.second->returnName.find("struct");

                    if (nPos != std::string::npos || sPos != std::string::npos) {
                        out << "      public void " << meth.first << "() {\n";
                        out << "            LibNative." << meth.first << "_native(ref this);\n";
                        out << "      }\n";
                    } else {
                        out << "      public " << meth.second->returnName << " " << meth.first << "() {\n";
                        out << "            LibNative." << meth.first << "_native(ref this);\n";
                        out << "      }\n";
                    }


                }

                out << "}\n \n";
            }

            out << "class LibNative {\n\n";

            for (auto& type : _register) {

                auto namespacePos = type.second.name.find("::");
                auto structPos = type.second.name.find("struct");


                std::string finalName;

                if (namespacePos != std::string::npos) {
                    finalName = type.second.name.substr(namespacePos + 2);
                } else {
                    finalName = type.second.name.substr(structPos + 7);
                }

                out << "      //BEGIN DEF For " << finalName.c_str() << "\n";

                for (auto meth : type.second.methods) {

                    auto nPos = meth.second->returnName.find("::");
                    auto sPos = meth.second->returnName.find("struct");

                    if (nPos != std::string::npos || sPos != std::string::npos) {
                        out << "      [MethodImplAttribute(MethodImplOptions.InternalCall)]\n";
                        out << "      public static extern void " << meth.first << "_native(ref " << finalName << " instance);\n \n";

                    } else {
                        out << "      [MethodImplAttribute(MethodImplOptions.InternalCall)]\n";
                        out << "      public static extern " << meth.second->returnName << " " << meth.first << "_native(ref " << finalName << " instance);\n \n";

                    }

                    }

                out << "      //END DEF For " << finalName.c_str() << "\n \n \n";
            }

            out << "}\n";


            out << "}///NAMESPACE CATOS \n";
            out.close();
        }



        /// Returns the registered Type
        template<typename A>
        TypeInfo& get_type() {
            return (_register[type_utils::get_type_hash<A>()]);
        }

        //TODO Dummy function!!!
        /// Prints out the items in the Registry
        void print_current_register() {
            for (auto val : _register) {
                TypeInfo& info = val.second;
                std::cout <<  info.name.c_str() << " { \n";

                for (auto& prop : info.properties) {

                    std::cout << "     " << prop.second->get_type_name() << " " << prop.second->get_name() << ";\n";
                }
                std::cout << "}\n";
            }
        }




    private:
        std::unordered_map<size_t, TypeInfo> _register;
        std::unordered_map<size_t, const void* > _instance_register;
    };
}