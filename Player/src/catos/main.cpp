// engine includes
#pragma once


#include "scripting/ScriptingEngine.h"
#include "spdlog/spdlog.h"
#include "stl/hashmap.h"

using namespace catos;

struct Foo {
    int data = 0;
};

int main() {

    catos::hashmap<int, const char*> map;

    int i =0;
    while (true) {
        map.put(i, "world");
        i++;
    }

    auto val = map.get(50);

    spdlog::info("out {}", val);

    return 0;
}

