// engine includes
#include <registry.h>


using namespace catos;


struct Foo {
    float data = 2;


    float tester(float bob) {
        return bob + 1.2f;
    }
};

int main() {


    Registry registry;

    Foo foo;


    foo.data = 4;

    registry.register_class<Foo>()
             .property("data", &Foo::data)
             .method("tester", &Foo::tester);


    registry.bind<Foo>(&foo);

    auto* test = registry.get<Foo>();




    auto ptr2 = (&Foo::tester);

    auto tester = (foo.*ptr2)(1);

    std::cout << "te " << tester << "\n";

    registry.print_current_register();

    return 0;
}