//
// Created by allos on 4/6/2025.
//
#pragma once

#include "io/Writer.h"

namespace catos {


    class YamlWriter: public Writer {
    public:
        ~YamlWriter() override = default;

        void writeBool(const string &name, bool value) override;

        void writeInt(const string &name, int value) override;

        void writeFloat(const string &name, float value) override;

        void writeString(const string &name, const char *value) override;

        void beginMap() override;
        void beginMap(const string &name) override;
        void endMap() override;

        void beginArray() override;
        void beginArray(const string &name) override;
        void endArray() override;

        void begin() override;

        void close() override;

    protected:
        bool validate() override;

    private:
        int maps_opened = 0;
        int maps_closed = 0;

        int arrays_openend = 0;
        int arrays_closed = 0;
    };

}
