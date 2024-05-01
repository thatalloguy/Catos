//
// Created by allos on 4/30/2024.
//
#pragma once


#include <unordered_map>
#include <vector>
#include <memory>
#include "types.h"
#include "type_utils.h"

namespace catos {


    struct Component {
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void destroy() = 0;
    };

    class Entity {

    public:
        Entity() = default;
        ~Entity() = default;

        template<class Comp>
        Comp* getComponent();

        Component* getComponent(str name);

        template<class Comp>
        void addComponent(Component* component);


        /// Life time functions
        void init();
        void update();
        void destroy();

    private:
        ///TODO should i allow mutliple components of the same type?
        std::unordered_map<str, Component*> componentTable;
    };



}