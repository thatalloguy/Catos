//
// Created by allos on 05/10/2025.
//
#pragma once
#include "../actionManager.h"


namespace catos::actions {


    template<typename T>
    class ChangeValueAction: public Action {
    public:
        ChangeValueAction(T oldValue, T* instance) {
            _oldValue = oldValue;
            _newValue = *instance;
            _instance = instance;
        }

        void execute() override {
            *_instance = _newValue;
        }

        void revoke() override {
            *_instance = _oldValue;
        }


    private:
        T _oldValue;
        T _newValue;
        T* _instance;

    };

}
