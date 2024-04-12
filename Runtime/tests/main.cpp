
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <type_utils.h>
#include <TINYSTL/string.h>
#include <registry.h>

struct Foo {
    float data = 2;

    float get_data() {
        return data;
    }
};

namespace catos::tests {

    TEST_CASE("REGISTRY::GET_TYPE_NAME") {
        CHECK((tinystl::string) "int" == catos::type_utils::get_type_name<int>());
    }

    TEST_CASE("REGISTRY::FIELDS") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        auto& field = registry.register_class<Foo>().property("data", &Foo::data);


        Property* test = field.get_property("data");

        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(foo.data == *testFloat);
    }

    TEST_CASE("REGISTRY::INSTANCES") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        registry.bind<Foo>(&foo);


        auto* test = registry.get<Foo>();

        CHECK(test->data == foo.data);
    }

    TEST_CASE("REGISTRY::METHODS") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        auto& field = registry.register_class<Foo>()
                .property("data", &Foo::data)
                .method("get_data", &Foo::get_data);




        Property* test = field.get_property("data");
        Method* meth = field.get_method("get_data");
        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(*testFloat == meth->invoke_function<float>(&foo));
    }
}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

