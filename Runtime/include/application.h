//
// Created by allos on 5/5/2024.
//


#pragma once
#include "types.h"
#include "type_utils.h"

#include <unordered_map>


namespace catos {

    struct AppCreationInfo {
        ///            MAJOR | MINOR | PATCH?
        uint version = 001;
        str applicationTitle = "Catos Application";
    };


    class App {

    public:

        App(AppCreationInfo* creationInfo);
        ~App();


        bool is_alive();




        /// Used to bind an instance to an type
        template<typename A>
        void bind(const void* instance) {
            _instance_register[type_utils::get_type_hash<A>()] = instance;
        };

        /// Returns the registered instance
        template<typename A>
        A* get() {
            A* obj = (A*) (_instance_register[type_utils::get_type_hash<A>()]);
            return obj;
        }


        AppCreationInfo* getAppInfo();


    private:

        void init_registry();


        AppCreationInfo* _info;
        bool _is_alive = false;

        std::unordered_map<size_t, const void* > _instance_register;
    };

}
