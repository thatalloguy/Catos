//
// Created by allos on 4/8/2025.
//
// Credits to Skore's ArchiveReader

#pragma once
#include "stl/string.h"
#include "stl/vector.h"
#include "core/constructor.h"

namespace catos {

    enum class SerializedType: unsigned int {
        BOOL = 0,
        INT = 1,
        FLOAT = 2,
        STRING = 3,
        MAP = 4,
        ARRAY = 5,
    };

    class Reader {

    public:

        virtual ~Reader() = default;


        //Fundamentals

        virtual bool readBool(const catos::string& name) = 0;
        virtual int readInt(const catos::string& name) = 0;
        virtual float readFloat(const catos::string& name) = 0;
        virtual catos::string readString(const catos::string& name) = 0;
        //virtual void readBuffer(const catos::string& name, void* data, size_t size) = 0;

        virtual void beginMap(const catos::string& name) = 0;
        virtual void endMap() = 0;

        virtual void beginArray(const catos::string& name) = 0;
        virtual void endArray() = 0;

        virtual void read(const catos::string& source, catos::vector<catos::Instance*>& out) = 0;

        virtual SerializedType getNextEntryType() = 0;

    protected:
        virtual bool validate() = 0;
    };

}
