// engine includes
#include <registry.h>


using namespace catos;


struct Foo {
    float data = 2;
    int data2 = 4;
};

struct Bar {
    float my_data;
};


int main() {


    Registry registry;

    registry.register_class<Foo>().property("data", &Foo::data2);
    registry.register_class<Bar>();

    registry.print_current_register();

    return 0;
}
