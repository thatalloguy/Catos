// engine includes
#include <registry.h>


using namespace catos;


struct Foo {
    float data = 2;


    void tester() {
        std::cout << "HEYYY " <<  "\n";
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

    //foo_info.execute_method(&foo, test_func);

    Method* method = registry.get_type<Foo>().get_method("tester");
    method->invoke_function(test);
    registry.print_current_register();




    return 0;
}