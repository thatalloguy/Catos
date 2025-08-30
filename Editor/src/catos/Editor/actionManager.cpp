//
// Created by allos on 30/08/2025.
//

#include "actionManager.h"

// globals
namespace {
    catos::Action* present_stack[CATOS_MAX_ACTION_STACK_SIZE];

    catos::Action* past_stack[CATOS_MAX_ACTION_STACK_SIZE];
}

namespace catos {


    void ActionManager::undo() {

    }
    void ActionManager::redo() {

    }

    bool ActionManager::push_present_stack(Action* action){
        return true;
    }
    bool ActionManager::push_past_stack(Action* action){
        return true;
    }

    void ActionManager::clear_stacks(){

    }

    void ActionManager::clear_present_stack(){

    }

    void ActionManager::clear_past_stack(){

    }

}