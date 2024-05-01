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

    // Component is an abstract class that is the base for any component.
    struct Component {
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void destroy() = 0;
    };

    // Entities hold components which do the logic.
    class Entity {

    public:
        Entity(str& name) : _name(name) {};
        ~Entity() = default;

        // Get a component via its type. returns a pointer of that type.
        template<class Comp>
        Comp* getComponent();

        // Get a component via name, returns a Component pointer.
        Component* getComponent(str& name);

        // Add a component. Needs a type for the registry name.
        template<class Comp>
        void addComponent(Component* component);

        // Returns the name of the entity
        str& getName() { return _name; };

        /// Life time functions

        //Runs Component.init() on every registered component. (Init gets run at the start of the game)
        void init();
        //Runs Component.update() on every registered component. ( Gets called every tick)
        void update();
        //Runs Component.destroy() on every registered component. ( Gets called at the end of the program).
        void destroy();

    private:
        ///TODO should i allow mutliple components of the same type?
        std::unordered_map<str, Component*> componentTable;
        str& _name;
    };



}