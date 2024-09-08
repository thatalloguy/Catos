// engine includes
#pragma once


#include "world/world.h"
#include "spdlog/spdlog.h"
#include "stl/string.h"

struct Foo {
    int data = 0;
};

void test(const catos::string& test) {
    spdlog::info("te {}", test.c_str());
}

int main() {

    test("hello");

    return 0;
}

