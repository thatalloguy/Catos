//
// Created by allos on 5/5/2024.
//

#include "core/application.h"
#include "core/game.h"
#include "core/registry.h"


catos::App::App(AppCreationInfo* creationInfo) {

    _info = creationInfo;

    init_registry();

    _is_alive = true;
}

catos::App::~App() {
    auto registry = get<Registry>();

    delete registry;

}

void catos::App::init_registry() {



    bind<Registry>(new Registry);

    auto registry = *get<Registry>();



    registry.gen_cs_bindings_file();
}


bool catos::App::is_alive() {
    return _is_alive;
}

catos::AppCreationInfo *catos::App::getAppInfo() {
    return _info;
}


