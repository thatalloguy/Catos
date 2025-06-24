//
// Created by allos on 5/5/2024.
//

#include "core/application.h"
#include "core/registry.h"


catos::App::App() {

    init_registry();
}

catos::App::~App() {
    auto registry = get<Registry>();

    delete registry;

}

void catos::App::init_registry() {

    bind<Registry>(new Registry);

    auto registry = *get<Registry>();



}




