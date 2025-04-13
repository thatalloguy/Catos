//
// Created by allos on 4/8/2025.
//
// Credits to Skore's ArchiveReader

#pragma once
#include "stl/string.h"

namespace catos {

    enum class SerializedType: unsigned int{

    };

    class Reader {

    public:
        
        virtual ~Reader() = default;


        //Fundamentals

        virtual void readBool(const catos::string& name, bool value) = 0;
        virtual void readInt(const catos::string& name, int value) = 0;
        virtual void readFloat(const catos::string& name, float value) = 0;
        virtual void readString(const catos::string& name, const char* value) = 0;
        //virtual void readBuffer(const catos::string& name, void* data, size_t size) = 0;

        virtual void beginMap(const catos::string& name) = 0;
        virtual void endMap() = 0;

        virtual void beginArray(const catos::string& name) = 0;
        virtual void endArray() = 0;

        virtual void begin() = 0;
        virtual void close() = 0;

        virtual SerializedType getNextEntryType() = 0;

    protected:
        virtual bool validate() = 0;
    };

}
