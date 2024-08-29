// engine includes
#pragma once


#include "scripting/ScriptingEngine.h"
#include "spdlog/spdlog.h"

using namespace catos;

struct Foo {
    int data = 0;
};

int main() {

    catos::vector<int> foos = {1, 2, 3, 4, 5};


    for (const auto& foo : foos) {
        spdlog::info("test {}", foo);
    }

    return 0;
}

