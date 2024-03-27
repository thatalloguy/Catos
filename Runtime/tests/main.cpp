
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>


namespace catos::tests {

    TEST_CASE("TEST::TEST") {
        CHECK(1 == 1);
        CHECK(2 == 2);
    }

}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

