// engine includes
#include <registry.h>


using namespace catos;


struct Foo {
    float data = 2;
};

int main() {


    Registry registry;

    Foo foo;


    foo.data = 4;

    auto& field = registry.register_class<Foo>().property("data", &Foo::data);


    Property* test = field.get_property("data");

    float* testFloat = (float*) (test->get_value(&foo));

    std::cout << "TEST: " << *testFloat << "\n";

    return 0;
}