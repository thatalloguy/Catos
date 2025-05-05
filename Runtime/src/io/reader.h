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
        INVALID = 6,
    };


    struct Pack {
        catos::string key;
        catos::string val;
        bool has_val;
        bool is_array;
        bool is_map;
        bool is_pointer;

        catos::vector<Pack> children{};
    };



    class Reader {

    public:

        virtual ~Reader() = default;

        virtual bool open(const std::string& content) = 0;

        //Fundamentals
        virtual bool readBool(const catos::string& name) = 0;
        virtual int readInt(const catos::string& name) = 0;
        virtual float readFloat(const catos::string& name) = 0;
        virtual catos::string readString(const catos::string& name) = 0;
        //virtual void readBuffer(const catos::string& name, void* data, size_t size) = 0;


        virtual bool readBool() = 0;
        virtual int readInt() = 0;
        virtual float readFloat() = 0;
        virtual catos::string readString() = 0;

        virtual void beginMap(const catos::string& name) = 0;
        virtual void endMap() = 0;

        virtual void beginArray(const catos::string& name) = 0;
        virtual void endArray() = 0;


        virtual void beginMap() = 0;
        virtual void beginArray() = 0;

        virtual bool nextArrrayElement() = 0;
        virtual catos::string getCurrentKey() = 0;

        virtual SerializedType getNextEntryType() = 0;

    protected:
        virtual bool validate() = 0;
    };

}
