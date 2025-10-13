//
// Created by allos on 05/10/2025.
//
#pragma once
#include "../actionManager.h"

namespace catos {
    class Node;
}

namespace catos::actions {

    class ReparentNodeAction: public Action {
    public:
        ReparentNodeAction(Node* old_parent, Node* new_parent, Node* child) {
            _old_parent = old_parent;
            _new_parent = new_parent;
            _child = child;
        }

        void execute() override {
            _child->set_parent(_new_parent);
        }

        void revoke() override {
            _child->set_parent(_old_parent);
        }


    private:
        Node* _old_parent{nullptr};
        Node* _new_parent{nullptr};
        Node* _child{nullptr};

    };

}
