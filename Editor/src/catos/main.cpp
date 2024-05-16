//
// Created by allos on 5/15/2024.
//
#pragma once
#include "Editor/Editor.h"

int main() {

    catos::Editor::init();

    catos::Editor::run();

    catos::Editor::cleanUp();


    return 0;
}