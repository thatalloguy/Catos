//
// Created by allos on 4/6/2025.
// Credits to Skore's - ArchiveWriter

#pragma once


#include "stl/string.h"

namespace catos {

    class Writer {

    public:

        virtual ~Writer() = default;


        virtual bool open(const catos::string& path) = 0;

        //Fundamentals
        virtual void writeBool(const catos::string& name, bool value) = 0;
        virtual void writeInt(const catos::string& name, int value) = 0;
        virtual void writeFloat(const catos::string& name, float value) = 0;
        virtual void writeString(const catos::string& name, const char* value) = 0;
        //virtual void writeBuffer(const catos::string& name, void* data, size_t size) = 0;

        virtual void beginMap(const catos::string& name) = 0;
        virtual void endMap() = 0;

        virtual void beginArray(const catos::string& name) = 0;
        virtual void endArray() = 0;

        virtual void begin() = 0;
        virtual void close() = 0;

    protected:
        virtual bool validate() = 0;


    };

}

