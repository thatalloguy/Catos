//
// Created by allos on 05/10/2025.
//
#pragma once
#include "../actionManager.h"


namespace catos::actions {


    template<typename T>
    class ChangeValueAction: public Action {
    public:
        ChangeValueAction(T old_value, T* instance) {
            _old_value = old_value;
            _new_value = *instance;
            _instance = instance;
        }

        void execute() override {
            *_instance = _new_value;
        }

        void revoke() override {
            *_instance = _old_value;
        }


    private:
        T _old_value;
        T _new_value;
        T* _instance;

    };

}
