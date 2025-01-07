//
// Created by allos on 5/15/2024.
//
#pragma once
#include <any>

#include "spdlog/spdlog.h"
#include "stl/pair.h"
#include "stl/vector.h"
//#include "Editor/Editor.h"



static catos::vector<catos::Pair<void*, void*>> _undos;

template<typename T>
void changeValue(T* addr,T val) {
    _undos.push_back({addr, new T{val}});

    *addr = val;
}

void undoChange() {
    auto action = _undos.back();

    float* f = (float*) action.first;
    float* v = (float*) action.second;


    **action.first =action.second;
    std::any t;

    //delete action.second;

    _undos.pop_back();
}

int main() {

    float value = 1.5f;

    spdlog::info("Val : {}", value);

    changeValue(&value, 5.0f);

    spdlog::info("Val : {}", value);

    value = 2.0f;

    spdlog::info("Val : {}", value);

    undoChange();

    spdlog::info("Val : {}", value);


    /*
    catos::Editor::init();

    catos::Editor::run();

    catos::Editor::cleanUp();
    */


    return 0;
}