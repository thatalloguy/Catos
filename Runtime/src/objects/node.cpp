//
// Created by allos on 9/29/2024.
//

#include "node.h"

#include <ranges>
#include <string>

#include "spdlog/spdlog.h"


void catos::Node::initialize() {
    for (auto child: _children | std::views::values) {
        child->initialize();
    }
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
    _parent = parent;
}

catos::Node * catos::Node::get_root() const {
    return _root;
}


catos::Node* catos::Node::find_node(const string &path, bool recursive) const {

    std::string temp = path.c_str();

    auto pos = temp.find('/');
    if (pos != std::string::npos) {
        temp = temp.substr(pos + 1);

        string name = temp.c_str();

        auto it = _children.find(name);
        if (it != _children.end()) {
            Node* child = it->second;

            pos = temp.find('/');
            if (pos != std::string::npos && recursive) {
                return child->find_node(temp.c_str(), recursive);
            }


            return child;
        }
    } else {
        spdlog::warn("Could not find node: {}", path.c_str());
        return nullptr;
    }


    return nullptr;
}

catos::Node * catos::Node::get_child(const string &name) const {
    auto it = _children.find(name);

    if (it != _children.end()) {
        return it->second;
    }


    return nullptr;
}

catos::Node * catos::Node::get_parent() const {
    return _parent;
}

int catos::Node::num_children() const {
    return (int) _children.size();
}

bool catos::Node::is_root() const {
    return _parent == nullptr;
}

const catos::string& catos::Node::path() const {
    return _path;
}

const catos::string& catos::Node::name() const {
    return _name;
}
