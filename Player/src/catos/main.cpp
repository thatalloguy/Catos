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

    for (int i=0; i<100; i++) {
        map.put(i, "world");
    }

    auto val = map.get(50);

    spdlog::info("out {}", val);

    return 0;
}

