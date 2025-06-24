// engine includes
#pragma once
//

#include <iostream>
#include <stl/string.h>

#include "objects/node.h"
#include "spdlog/spdlog.h"

int main() {

    catos::Node root{false};
    catos::Node parent{false};
    catos::Node child{false};

    root.initialize("root");

    parent.initialize("parent");
    parent.set_parent(&root);

    child.initialize("child");
    child.set_parent(&parent);

    spdlog::info("path: {} | {}", root.name().c_str(), root.path().c_str());
    spdlog::info("path: {} | {}", parent.name().c_str(), parent.path().c_str());
    spdlog::info("path: {} | {}", child.name().c_str(), child.path().c_str());

    child.change_name("child2");

    spdlog::info("---------------------");

    spdlog::info("path: {} | {}", root.name().c_str(), root.path().c_str());
    spdlog::info("path: {} | {}", parent.name().c_str(), parent.path().c_str());
    spdlog::info("path: {} | {}", child.name().c_str(), child.path().c_str());

    spdlog::info("---------------------");

    spdlog::info("parent has child2: {}", parent.has_child("child2"));
    spdlog::info("parent has child3: {}", parent.has_child("child3"));
    spdlog::info("parent has child: {}", parent.has_child("child"));

    spdlog::info("---------------------");

    catos::Node* found_child = parent.find_node("child2");
    spdlog::info("found child via find_node: {}", found_child != nullptr);

    found_child = parent.get_child("child2");
    spdlog::info("found child via get_child: {}", found_child != nullptr);

    found_child = root.find_node("child2");
    spdlog::info("found child via the root: {}", found_child != nullptr);

}

