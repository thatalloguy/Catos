//
// Created by allos on 5/5/2024.
//


#pragma once
#include "types.h"
#include "type_utils.h"

#include <unordered_map>


namespace catos {


    /// A struct that holds all info the application needs at launch
    struct AppCreationInfo {
        ///            MAJOR | MINOR | PATCH?
        uint version = 001;
        str applicationTitle = "Catos Application";
    };


    /// Main class that holds all information.
    class App {

    public:

        /// Initializes the Application (Also registers all "known" class to the registry)
        App(AppCreationInfo* creationInfo);
        ~App();

        /// Returns if the app is still running.
        bool is_alive();




        /// Used to bind an instance to an type
        template<typename A>
        void bind(const void* instance) {
            _instance_register[type_utils::get_type_hash<A>()] = instance;
        };

        /// Returns the registered instance
        template<typename A>
        A* get() {
            return  (A*) (_instance_register[type_utils::get_type_hash<A>()]);
        }


        /// Returns a pointer to the info with what the application is made.
        AppCreationInfo* getAppInfo();


    private:

        void init_registry();


        AppCreationInfo* _info;
        bool _is_alive = false;

        std::unordered_map<size_t, const void* > _instance_register;
    };

}
