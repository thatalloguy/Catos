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


    map.put(1, "world");
    map.put(2, "world");
    map.put(3, "world");
    map.put(4, "world");
    map.put(41, "world");
    map.put(54, "world");
    map.put(64, "world");
    map.put(84, "world");
    map.put(5, "world");
    map.put(6, "world");
    map.put(7, "world");
    map.put(8, "world");
    map.put(9, "world");
    map.put(44, "world2");

    auto val = map.get(84);

    spdlog::info("out {}", val);

    return 0;
}

