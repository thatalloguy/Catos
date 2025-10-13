//
// Created by allos on 05/10/2025.
//
#pragma once
#include "../actionManager.h"
#include "objects/node.h"

namespace catos {
    class Node;
}

namespace catos::actions {

    class DeleteNodeAction: public Action {
    public:

        DeleteNodeAction(Node* child) {
            _old_parent = child->get_parent();
            _child = child;
        }

        void execute() override {
            _child->set_parent(&deletion_holder);
        }

        void revoke() override {
            _child->set_parent(_old_parent);
        }


    private:
        inline static Node deletion_holder{};
        Node* _old_parent{nullptr};
        Node* _child{nullptr};

    };

}
