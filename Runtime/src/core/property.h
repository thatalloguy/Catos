//
// Created by allos on 3/19/2025.
//
#pragma once

#include <iostream>
#include <unordered_map>
#include "types.h"
#include "stl/any.h"
#include "spdlog/spdlog.h"


#include <stl/vector.h>
#include <stl/pair.h>
#include <stl/rawvector.h>
#include <any>



namespace catos {

    namespace _property_utils {
        unsigned long get_ref(void* ptr);

    }

    enum class PropertyType {
        BASIC =     1,
        VECTOR =    2,
        HASHMAP =   3,
        POINTER =   4,
        CUSTOM =    0,
    };

    // Properties :)
    /// See PropertyImpl for details.
    class Property {

    public:
        ///Stores an member pointer to a field of an type.
        /// NOTE see the PropertyImpl for further documentation

        virtual ~Property() = default;

        virtual void* get_value(const void* obj_ptr) = 0;
        virtual int get_length(const void* obj_ptr) = 0;

        virtual void set_value(const void* instance,  catos::any val) = 0;


        virtual PropertyType get_type() {
            return PropertyType::BASIC;
        };

        virtual const char* get_name() = 0;
        virtual const char* get_type_name() = 0;
        virtual size_t& get_type_hash() = 0;

        virtual bool is_class() = 0;


        virtual void set_name(const char* name) = 0;

        cstr desc = "NONE";
    };

    /// PropertyImpl implements Property and holds an member function pointer. Used to get an value of an field of an Type's instance.
    template<typename T, typename U>
    class PropertyImpl : public Property {


    public:
        U T::* memberPtr;
        const char* name;

        size_t sizeof_type;

        std::string type_name;
        size_t type_hash;

        ///PropertyImpl exist in order to avoid having to deal with templates at the user-side.
        PropertyImpl(U T::* memPtr) : memberPtr(memPtr) {
            type_name = typeid(U).name();
            type_hash = typeid(U).hash_code();
            sizeof_type = sizeof(U);
        };

        /// Set the name of the property
        void set_name(const char* new_name) override {
            name = new_name;
        }

        PropertyType get_type() const {
            return PropertyType::BASIC;
        }

        virtual size_t get_type_size() {
            return sizeof_type;
        };


        /// Use Get value (which can be cased to the desired type) to return an value of an instance.
        void* get_value(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);
            return const_cast<void*>(reinterpret_cast<const void*>(&(obj->*memberPtr)));
        }

        void set_value(const void* instance, catos::any val) override {

            T* obj = (T*) instance;

            obj->*memberPtr = val.get<U>();
        }

        int get_length(const void* obj_ptr) {
            return 0;
        }

        /// Get the name of the property
        const char* get_name() override{
            return name;
        }

        /// Returns the name of the fields type.
        const char* get_type_name() override {
            return type_name.c_str();
        };

        /// Returns (a reference of) the type's hash
        size_t& get_type_hash() override {
            return type_hash;
        };

        bool is_class() override {
            return std::is_class<U>::value;
        }



    };


    class VectorProperty: public Property {
    public:

        virtual void push_back_value(void* instance, catos::any value) = 0;
        virtual void push_back_ptr(void* instance, void* value) = 0;

    };


    template<typename T, typename U>
    class VectorPropertyImpl : public VectorProperty {


    public:
        catos::vector<U> T::* memberPtr;
        catos::raw_vector* vec = nullptr;

        const char* name{};

        size_t sizeof_type{};


        std::string type_name;
        size_t type_hash{};

        ///PropertyImpl exist in order to avoid having to deal with templates at the user-side.
        VectorPropertyImpl(catos::vector<U> T::* memPtr) : memberPtr(memPtr) {
            type_name = typeid(U).name();
            type_hash = typeid(U).hash_code();
            sizeof_type = sizeof(U);
        };

        ~VectorPropertyImpl() {
            delete vec;
        }

        /// Set the name of the property
        void set_name(const char* new_name) override {
            name = new_name;
        }


        PropertyType get_type() override {
            return PropertyType::VECTOR;
        }



        /// Use Get value (which can be cased to the desired type) to return an value of an instance.
        void* get_value(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);

            delete vec;
            vec = new raw_vector((catos::vector<U>*) &(obj->*memberPtr));

            return vec;
        }


        void set_value(const void* instance, catos::any val) override {

            T* obj = (T*) instance;

            obj->*memberPtr = val.get<catos::vector<U>>();
        }


        virtual void push_back_value(void* instance, catos::any value) override {
            T* obj = (T*) instance;

            catos::vector<U>* vec =  (catos::vector<U>*) &(obj->*memberPtr);

            U v = value.get<U>();
            vec->push_back(v);


        }

        virtual void push_back_ptr(void* instance, void* value) override {
            T* obj = (T*) instance;

            catos::vector<U>* vec =  (catos::vector<U>*) &(obj->*memberPtr);

            U* val = (U*) value;

            vec->push_back(*val);


        }


        int get_length(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);
            return (obj->*memberPtr).length();
        }
        /// Get the name of the property
        const char* get_name() override{
            return name;
        }

        /// Returns the name of the fields type.
        const char* get_type_name() override {
            return type_name.c_str();
        };

        /// Returns (a reference of) the type's hash
        size_t& get_type_hash() override {
            return type_hash;
        };

        bool is_class() override {
            return std::is_class<U>::value;
        }

    };


    template<typename T, typename K, typename V>
    class HashMapProperty : public Property {


    public:
        std::unordered_map<K, V> T::* memberPtr;
        const char* name;

        size_t sizeof_type;


        std::string type_name;
        size_t type_hash;

        ///PropertyImpl exist in order to avoid having to deal with templates at the user-side.
        HashMapProperty(std::unordered_map<K, V> T::* memPtr) : memberPtr(memPtr) {
            type_name = typeid(catos::Pair<K, V>).name();
            type_hash = typeid(catos::Pair<K, V>).hash_code();
            sizeof_type = sizeof(catos::Pair<K, V>);
        };

        /// Set the name of the property
        void set_name(const char* new_name) override {
            name = new_name;
        }


        PropertyType get_type() override {
            return PropertyType::VECTOR;
        }



        /// Use Get value (which can be cased to the desired type) to return an value of an instance.
        void* get_value(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);

            return const_cast<void*>(reinterpret_cast<const void*>(&(obj->*memberPtr)));
        }

        void set_value(const void* instance, catos::any val) override {

            T* obj = (T*) instance;

            obj->*memberPtr = val.get<std::unordered_map<K, V>>();
        }

        int get_length(const void* objPtr) {
            const T* obj = static_cast<const T*>(objPtr);
            return (obj->*memberPtr).size();
        }
        /// Get the name of the property
        const char* get_name() override{
            return name;
        }

        /// Returns the name of the fields type.
        const char* get_type_name() override {
            return type_name.c_str();
        };

        /// Returns (a reference of) the type's hash
        size_t& get_type_hash() override {
            return type_hash;
        };

        bool is_class() override {
            return std::is_class<K>::value;
        }

    };

    template<typename T, typename U>
    class PointerProperty : public Property {


    public:
        U T::* memberPtr;
        const char* name;

        size_t sizeof_type;

        std::string type_name;
        size_t type_hash;



        ///PropertyImpl exist in order to avoid having to deal with templates at the user-side.
        PointerProperty(U T::* memPtr) : memberPtr(memPtr) {
            type_name = typeid(U).name();
            type_hash = typeid(U).hash_code();
            sizeof_type = sizeof(U);
        };

        /// Set the name of the property
        void set_name(const char* new_name) override {
            name = new_name;
        }

        PropertyType get_type() const {
            return PropertyType::BASIC;
        }

        virtual size_t get_type_size() {
            return sizeof_type;
        };


        /// Use Get value (which can be cased to the desired type) to return an value of an instance.
        void* get_value(const void* objPtr) override {
            const T* obj = static_cast<const T*>(objPtr);

            return (void*) (obj->*memberPtr);
        }

        int get_length(const void* obj_ptr) {
            return 0;
        }

        /// Get the name of the property
        const char* get_name() override{
            return name;
        }

        /// Returns the name of the fields type.
        const char* get_type_name() override {
            return type_name.c_str();
        };

        /// Returns (a reference of) the type's hash
        size_t& get_type_hash() override {
            return type_hash;
        };

        bool is_class() override {
            return std::is_class<U>::value;
        }


    };

}