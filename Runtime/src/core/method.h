//
// Created by allos on 3/19/2025.
//
#pragma once

#include <any>
#include "types.h"


#ifdef CATOS_SCRIPTING_ENABLED
#include "scripting/ScriptingEngine.h"
#endif

namespace catos {
    class MethodHolder {
    public:

        virtual void registerToPy(const char* name) = 0;
    };

    template<typename ReturnType, class ClassType, typename... Args>
    class MethodHolderImpl : public MethodHolder {
    private:
        ReturnType(ClassType::* _ptr)(Args...);

    public:
        MethodHolderImpl(ReturnType(ClassType::* memberPtr)(Args...)) : _ptr(memberPtr) {

        }

        void registerToPy(const char* name) override {
#ifdef CATOS_SCRIPTING_ENABLED
            auto& inst = catos::ScriptingEngine::getInstance();

            inst.registerMethod<ClassType>(name, _ptr);
#endif
        }
    };


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




    template<typename... Args>
    std::string getNames() {
        std::string str;
        int argC = 0;
        (str.append(std::string(typeid(Args).name()) + std::string(" arg") + std::to_string(argC++) + ","), ...);

        return str;
    }

    template<typename... Args>
    std::string getArgNames() {
        std::string str =",";
        int argC = 0;

        argC = sizeof...(Args);

        for (int i=0; i < argC; i++) {
            str += "arg" + std::to_string(i);
            str += ",";
        }

        return str;
    }



    /// Stores a function pointer for running it.
    class Method {

    public:
        template<typename ReturnType, class ClassType, typename... Args>
        Method(ReturnType(ClassType::* method)(Args...)) {
            _mFunc = MethodInvoker<ReturnType, ClassType, Args...>(method);

            holder = new MethodHolderImpl<ReturnType, ClassType, Args...>(method);

            ptr = &MethodInvoker<ReturnType, ClassType, Args...>::callFunction;


            returnName = typeid(ReturnType).name();


            if (getNames<Args...>() != "") {

                parameters = getNames<Args...>();


                std::string search = "char const * __ptr64";
                std::string replace = "string";

                size_t pos = 0;
                // replace cstr to string
                while((pos = parameters.find(search, pos)) != std::string::npos) {
                    parameters.replace(pos, search.length(), replace);
                    pos += replace.length();
                }
                search = "class catos:: ";
                replace = "ref ";
                pos = 0;

                // Change class catos::  to ref for c#
                while((pos = parameters.find(search, pos)) != std::string::npos) {
                    parameters.replace(pos, search.length(), replace);
                    pos += replace.length();
                }

                // remove ","
                parameters.erase(parameters.size() - 1, 1);
                parameterNames = getArgNames<Args...>();
                parameterNames.erase(parameterNames.size() - 1, 1);
            }

        };

        ~Method() {
            delete holder;
        }

        template<typename R, typename... Args>
        R invoke_function(void* instance, Args... args) {
            return std::any_cast<R(*)(void*, void*, Args...)>(ptr)(&_mFunc, instance, args...);
        };

        template<typename... Args>
        void invoke_function(void* instance, Args... args) {
            std::any_cast<void(*)(void*, void*, Args...)>(ptr)(&_mFunc, instance, args...);
        };

        void registerToPy(const char* name) {
            holder->registerToPy(name);
        }


        cstr desc = "NONE";
        std::string returnName = "void";

        std::string parameters;
        std::string parameterNames;
    private:

        std::any ptr;
        std::any _mFunc;
        MethodHolder* holder;
    };

}