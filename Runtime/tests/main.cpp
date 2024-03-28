
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <type_utils.h>
#include <TINYSTL/string.h>

namespace catos::tests {

    TEST_CASE("REGISTRY::GET_TYPE_NAME") {
        CHECK((tinystl::string) "int" == catos::type_utils::get_type_name<int>());
    }


}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

