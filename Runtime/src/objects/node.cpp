//
// Created by allos on 9/29/2024.
//

#include "node.h"

#include <string>

#include "spdlog/spdlog.h"
#include "stl/vector.h"


void catos::Node::initialize(const string& name) {
    _name = name;
}

void catos::Node::update() {
    for (auto child: _children | std::views::values) {
        child->update();
    }
}

void catos::Node::render() {
    for (auto child: _children | std::views::values) {
        child->render();
    }


}

void catos::Node::destroy() {
    for (auto child: _children | std::views::values) {
        child->destroy();
        if (_manage_memory) {
            delete child;
        }
    }
}

void catos::Node::set_parent(Node *parent) {

    if (parent == nullptr)
        return;

    if (parent->has_child(_name)) {
        spdlog::warn("Parent already has this child");
        return;
    }

    if (_parent != nullptr ) {
        _parent->remove_child(_name);
    }


    _parent = parent;
    parent->_children.insert({_name, this});
}

bool catos::Node::has_child(const string &name) {
    return _children.find(name) != _children.end();
}


catos::Node* catos::Node::find_node(const string &name, bool recursive) {
    auto it = _children.find(name);

    if (it != _children.end()) {
        return it->second;
    }
    else if (recursive && it == _children.end()) {
        for (auto pair : _children) {
            Node* node = pair.second->find_node(name, true);

            if (node != nullptr) {
                return node;
            }
        }
    }

    spdlog::warn("Could not find node: {}", name.c_str());
    return nullptr;
}

catos::Node * catos::Node::get_child(const string &name) {
    auto it = _children.find(name);

    if (it != _children.end()) {
        return it->second;
    }


    return nullptr;
}

catos::Node * catos::Node::get_parent() {
    return _parent;
}

int catos::Node::num_children() {
    return (int) _children.size();
}

bool catos::Node::is_root() {
    return _parent == nullptr;
}

const catos::string& catos::Node::path() {

    Node* super_parent = _parent;
    vector<string> paths;

    while (super_parent != nullptr) {
        paths.push_back(super_parent->name());

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
    _path += _name;

    return _path;
}

const catos::string& catos::Node::name() const {
    return _name;
}

void catos::Node::change_name(const string &new_name) {
    if (_parent != nullptr) {
        // take in account siblings
        _parent->change_child_name(_name, new_name);
    } else {
        _name = new_name;
    }
}

void catos::Node::change_child_name(const string &name,const string& new_name) {
    auto it = _children.find(name);
    if (it == _children.end()) {
        spdlog::warn("Could not rename node {}", name.c_str());
        return;
    }

    Node* node = it->second;
    node->_name = new_name;

    _children.erase(it);

    _children.insert({new_name, node});
}

void catos::Node::remove_child(const string &child) {
    auto it = _children.find(child);
    if (it == _children.end()) {
        spdlog::warn("Could not remove child {}", child.c_str());
        return;
    }



    _children.erase(it);
}
