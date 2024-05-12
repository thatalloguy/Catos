// engine includes
#pragma once
#include "core/registry.h"
#include "core/application.h"
#include <fstream>

using namespace catos;


class Foo {
public:

    float data;


    void init(float _data) {
        data = _data;
    }


    void tester() {
        std::cout << "HEYYY " <<  "\n";
    }



};

template<typename T>
class ConstructorInvoker {
public:
    template<typename... Args>
    T operator()(Args... args)const {
        return T(std::forward<Args>(args)...);
    }
};

template<typename Fn, typename... Args>
auto invoke(Fn f, Args... args) {
    return f(args...);
}

int main() {


    AppCreationInfo info{};

    App app{&info};




    return 0;
}