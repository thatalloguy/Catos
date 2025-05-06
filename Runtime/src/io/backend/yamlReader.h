//
// Created by allos on 4/13/2025.
//
#pragma once

#include "io/reader.h"
#include <ryml.hpp>


namespace catos {


    class YamlReader: public Reader {
        virtual ~YamlReader() = default;


        bool open(const std::string& content) override;

        //Fundamentals

        virtual bool readBool(const catos::string& name) override;
        virtual int readInt(const catos::string& name) override;
        virtual float readFloat(const catos::string& name) override;
        virtual catos::string readString(const catos::string& name) override;


        virtual bool readBool() override;
        virtual int readInt() override;
        virtual float readFloat() override;
        virtual catos::string readString() override;


        virtual void beginMap() override;
        virtual void beginArray() override;

        virtual void beginMap(const catos::string& name) override;
        virtual void endMap() override;

        virtual void beginArray(const catos::string& name) override;
        virtual void endArray() override;


        virtual SerializedType getNextEntryType() override;

        virtual bool nextArrrayElement() override;

        virtual catos::string getCurrentKey() override;


    protected:
        virtual bool validate() override;

    private:
        ryml::Tree _tree;
        ryml::NodeRef _root{};
        ryml::NodeRef _current_node{};
        catos::vector<ryml::NodeRef> _stack{};
        size_t _array_index = 0;
        size_t _prev_array_index = 0;

        bool _is_root_open = false;
    };

}

