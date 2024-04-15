// engine includes
#include <registry.h>


using namespace catos;


class Foo {
public:
    float data;


    Foo(float _data) : data(_data) {}


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

    Registry registry;

    Foo foo{3};


    foo.data = 4;

    auto foo_info = registry.register_class<Foo>()
             .property("data", &Foo::data)
             .method("tester", &Foo::tester);





    return 0;
}