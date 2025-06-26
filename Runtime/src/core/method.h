//
// Created by allos on 3/19/2025.
//
#pragma once

#include <any>
#include "types.h"


namespace catos {
    class MethodHolder {

    };

    template<typename ReturnType, class ClassType, typename... Args>
    class MethodHolderImpl : public MethodHolder {
    private:
        ReturnType(ClassType::* _ptr)(Args...);

    public:
        MethodHolderImpl(ReturnType(ClassType::* memberPtr)(Args...)) : _ptr(memberPtr) {

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