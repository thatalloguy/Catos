//
// Created by allos on 4/13/2025.
//
#pragma once

#include "io/reader.h"

namespace catos {


    class YamlReader: public Reader {
        virtual ~YamlReader() = default;


        //Fundamentals

        virtual bool readBool(const catos::string& name, bool value) override;
        virtual int readInt(const catos::string& name, int value) override;
        virtual float readFloat(const catos::string& name, float value) override;
        virtual catos::string readString(const catos::string& name, const char* value) override;
        //virtual void readBuffer(const catos::string& name, void* data, size_t size) override;

        virtual void beginMap(const catos::string& name) override;
        virtual void endMap() override;

        virtual void beginArray(const catos::string& name) override;
        virtual void endArray() override;

        virtual void begin() override;
        virtual void close() override;

        virtual SerializedType getNextEntryType() override;

    protected:
        virtual bool validate() override;
    };

}

