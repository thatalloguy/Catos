// engine includes
#include <registry.h>


using namespace catos;


struct Foo {
    float data = 2;


    void tester(int test) {
        std::cout << "HEYYY " <<  "\n";
    }
};

struct Dummy {
    int f(double d, int x) {

        std::cout << "Hello world from non-static function!\n";
        return x + d;
    }

    void print() {
        std::cout << "Hello world from non-static function!\n";
    }
};


template<typename ReturnType, class ClassType, typename... Args>
ReturnType callFunction(ReturnType(ClassType::*  function)(Args...), ClassType& instance, const Args&... args) {
    return (instance.*function)(args...);
}

template<typename ReturnType, class ClassType, typename... Args>
void callFunctionNoReturn(ReturnType(ClassType::*  function)(Args...), ClassType& instance, const Args&... args) {
    (instance.*function)(args...);
}

class BaseFunction {
};


template<typename ReturnType, class ClassType, typename... Args>
class Function_ : public BaseFunction {

public:

    ReturnType (ClassType::* memPtr)(Args...);
    Function_(ReturnType (ClassType::* ptr)(Args...)) {
        memPtr = ptr;
    };

    static ReturnType callFunction(void* FuncInst, void* instance, Args... args) {
        return (static_cast<ClassType*>(instance)->*static_cast<Function_<ReturnType, ClassType, Args...>*>(FuncInst)->memPtr)(args...);
    }
};



class Meth {

public:
    template<typename ReturnType, class ClassType, typename... Args>
    void new_function(ReturnType(ClassType::* method)(Args...)) {
        _mFunc = Function_<ReturnType, ClassType, Args...>(method);

        ptr = &Function_<ReturnType, ClassType, Args...>::callFunction;
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




int main() {

/*
    Registry registry;

    Foo foo;


    foo.data = 4;

    auto foo_info = registry.register_class<Foo>()
             .property("data", &Foo::data)
             .method("tester", &Foo::tester);


    registry.bind<Foo>(&foo);

    auto* test = registry.get<Foo>();


    Method* test_func = foo_info.get_method("tester");
    if (!foo_info.is_valid(test_func)) {
        exit(-3);
    }

    //foo_info.execute_method(&foo, test_func);


    registry.print_current_register();*/



    Dummy instance;


    Meth md;
    md.new_function(&Dummy::print);

    md.invoke_function(&instance);

    //std::cout << callFunction((&Dummy::f), dum, 1.0, 3) << std::endl;
    //callFunctionNoReturn((&Dummy::print), dum);

    //auto func = Function_<int, Dummy, double, int>((&Dummy::f));

    //auto(*ptr) = &Function_<int, Dummy, double, int>::callFunction;

    //std::cout << (ptr)(&func, &instance, 2.0, 1.0f) << std::endl;

    return 0;
}