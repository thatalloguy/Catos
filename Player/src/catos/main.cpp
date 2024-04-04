// engine includes
#include <registry.h>


using namespace catos;


struct Foo {
    float data = 2;

    float get_float(float in) {
        return in  + 1.2f;
    };
};

int main() {


    Registry registry;

    Foo foo;


    foo.data = 4;

    registry.register_class<Foo>()
             .property("data", &Foo::data);


    registry.bind_instance<Foo>(&foo);

    auto* test = registry.get_instance<Foo>();



    registry.print_current_register();

    return 0;
}