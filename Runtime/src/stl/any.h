//
// Created by allos on 4/19/2025.
// Note: HUGE credits to BBIng on stackoverflow basically copied his implementation :)

#pragma once
#include <utility>

namespace catos {

    class any {


        template<typename Td>
        class any_value {
        public:
            static void contruct(void **data, Td&& val) {
                *data = new Td(std::forward<Td>(val));
            }

            static void deconstruct(void *data) {
                auto ptr = (Td*) data;
                delete ptr;
            }

        };

    public:

        template <typename Td, typename Tp = std::decay_t<Td>>
        any(Td&& val) : deconstructor(any_value<Tp>::deconstruct) {
            any_value<Tp>::contruct(&data, std::forward<Tp>(val));
        }

        ~any() {
            deconstructor(data);
            data = nullptr;
        }

        template<typename Tp>
        Tp get() {
            return *static_cast<Tp*>(data);
        }


    private:
        void* data;
        void (* deconstructor)(void* data);

    };

}