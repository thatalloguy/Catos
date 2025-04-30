//
// Created by allos on 4/13/2025.
//
#pragma once

#include "io/reader.h"

namespace catos {


    class YamlReader: public Reader {
        virtual ~YamlReader() = default;


        bool open(const std::string& content) override;

        //Fundamentals

        virtual bool readBool(const catos::string& name) override;
        virtual int readInt(const catos::string& name) override;
        virtual float readFloat(const catos::string& name) override;
        virtual catos::string readString(const catos::string& name) override;
        //virtual void readBuffer(const catos::string& name, void* data, size_t size) override;

        virtual void beginMap(const catos::string& name) override;
        virtual void endMap() override;

        virtual void beginArray(const catos::string& name) override;
        virtual void endArray() override;


        virtual SerializedType getNextEntryType() override;

        virtual bool nextArrrayElement() override;


    protected:
        virtual bool validate() override;
    };

}

