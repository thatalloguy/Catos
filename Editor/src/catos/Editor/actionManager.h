//
// Created by allos on 30/08/2025.
//
#pragma once
#include "stl/vector.h"

#ifndef CATOS_MAX_ACTION_STACK_SIZE
#define CATOS_MAX_ACTION_STACK_SIZE 50
#endif

namespace catos {

    // An Action class is meant to represent an action that is redo/undoable in the editor.
    class Action {
    public:

        Action() = default;
        virtual ~Action() = default;

        //undo
        virtual void execute();

        //redo
        virtual void revoke();

    protected: // unused
    private: // unused
    };

    //We use a namespace instead of class because its easier to write an singleton this way.
    namespace ActionManager {
        // There are 2 stacks: Present and Pasts
        // The stacks are named from the perspective of an action
        // So if it gets preformed it goes onto the present stack
        // if it gets undone it goes to the past.
        void undo();
        void redo();

        bool push_present_stack(Action* action);
        bool push_past_stack(Action* action);

        void clear_stacks();
        void clear_present_stack();
        void clear_past_stack();
    }


}
