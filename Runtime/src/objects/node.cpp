//
// Created by allos on 9/29/2024.
//

#include "node.h"

#include <string>

#include "spdlog/spdlog.h"
#include "stl/vector.h"


void catos::Node::initialize(const string& name) {
    this->name = name;
}

void catos::Node::update() {
    for (auto child: _children) {
        child->update();
    }
}

void catos::Node::render() {
    for (auto child: _children) {
        child->render();
    }


}

void catos::Node::destroy(bool bin_children) {

    for (auto child: _children) {
        child->destroy();
        if (bin_children) {
            delete child;
        }
    }

    if (_parent) {
        _parent->remove_child(name);
    }
}

size_t catos::Node::get_node_type_hash() {
    return typeid(Node).hash_code();
}

void catos::Node::set_parent(Node *parent) {

    if (parent == nullptr)
        return;

    if (parent->has_child(name)) {
        spdlog::warn("Parent already has this child");
        return;
    }

    if (_parent != nullptr ) {
        _parent->remove_child(name);
    }


    _parent = parent;
    parent->_children.push_back({this});
}

bool catos::Node::has_child(const string &name) {
    for (int i=0; i<_children.length(); i++) {
        if (_children[i]->name == name) {
            return true;
        }
    }

    return false;
}


catos::Node* catos::Node::find_node(const string &name, bool recursive) {
    for (int i=0; i<_children.length(); i++) {
        if (_children[i]->name == name) {
            return _children[i];
        }
    }
    if (recursive) {
        for (auto child : _children) {
            Node* node = child->find_node(name, true);

            if (node != nullptr) {
                return node;
            }
        }
    }

    spdlog::warn("Could not find node: {}", name.c_str());
    return nullptr;
}

catos::Node * catos::Node::get_child(const string &name) {
    for (int i=0; i<_children.length(); i++) {
        if (_children[i]->name == name) {
            return _children[i];
        }
    }

    spdlog::info("Could not find child: {}", name.c_str());

    return nullptr;
}

catos::Node * catos::Node::get_parent() {
    return _parent;
}

int catos::Node::num_children() {
    return (int) _children.length();
}

bool catos::Node::is_root() {
    return _parent == nullptr;
}

const catos::string& catos::Node::path() {

    Node* super_parent = _parent;
    vector<string> paths;

    while (super_parent != nullptr) {
        paths.push_back(super_parent->name);

        super_parent = super_parent->get_parent();
    }

    if (_parent == nullptr) {
        _path = "/";
        return _path;
    }
    _path = "";

    for (int i=paths.length(); i>0; i--) {
        _path += paths[i-1];
        _path += "/";
    }
    _path += name;

    return _path;
}



void catos::Node::remove_child(const string &child) {
    for (int i=0; i<_children.length(); i++) {
        if (_children[i]->name == child) {
            _children.remove(i);
            return;
        }
    }

    spdlog::warn("Could not find child: {}", child.c_str());
}
