//
// Created by allos on 30/08/2025.
//

#include "actionManager.h"

#include "spdlog/spdlog.h"
#include "stl/vector.h"

// globals
namespace {
    catos::vector<catos::Action*> present;
    catos::vector<catos::Action*> past;
}

namespace catos {


    void ActionManager::undo() {
        if (present.length() <= 0) {
            spdlog::warn("No undo history");
            return;
        }

        spdlog::debug("Undid action");

        Action* action = present.back();

        action->revoke();

        present.pop_back();
        past.push_back(action);

    }
    void ActionManager::redo() {

        if (past.length() <= 0) {
            spdlog::warn("No redo history");
            return;
        }

        spdlog::debug("Redid action");


        Action* action = past.back();
        action->execute();

        past.pop_back();

        present.push_back(action);

    }

    bool ActionManager::push_present_stack(Action* action) {
        present.push_back(action);
        return true;
    }
    bool ActionManager::push_past_stack(Action* action) {
        past.push_back(action);
        return true;
    }

    void ActionManager::clear_stacks() {
        for (Action* action : present) {
            delete action;
        }

        for (Action* action : past) {
            delete action;
        }
    }


}