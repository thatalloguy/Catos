// engine includes
#include <registry.h>


using namespace catos;


struct Foo {
    float data = 2;


    void tester() {
        std::cout << "HEYYY\n";
        //return bob + 2.0f;
    }
};

int main() {


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

    auto ptr2 = (&Foo::tester);

    test_func->invoke(&foo);


    (foo.*ptr2)();


    registry.print_current_register();

    return 0;
}