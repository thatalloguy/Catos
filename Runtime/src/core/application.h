//
// Created by allos on 5/5/2024.
//


#pragma once

#include "types.h"
#include <unordered_map>
#include <typeinfo>

namespace catos {


    /// Main class that holds all information.
    class App {

    public:

        /// Initializes the Application (Also registers all "known" class to the registry)
        App();
        virtual ~App();

        /// Returns if the app is still running.
        virtual bool is_alive() { return true; };

        /// Used to bind an instance to an type
        template<typename A>
        void bind(const void* instance) {
            _instance_register[typeid(A).hash_code()] = instance;
        };

        /// Returns the registered instance
        template<typename A>
        A* get() {
            return  (A*) (_instance_register[typeid(A).hash_code()]);
        }

    protected:
        void init_registry();

    private:
        std::unordered_map<size_t, const void* > _instance_register;
    };

}
