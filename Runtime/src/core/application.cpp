//
// Created by allos on 5/5/2024.
//

#include "core/application.h"
#include "core/registry.h"


catos::App::App() {

}

catos::App::~App() {
    auto registry = get<Registry>();

    delete registry;

}

