//
// Created by allos on 12/08/2025.
//
#pragma once

#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

#include "stl/string.h"
#include "stl/vector.h"

namespace catos {

    enum LogLevel: unsigned int {
        unknown     = 0,
        debug       = 1,
        info        = 2,
        warning     = 3,
        error       = 4,
        critical    = 5,
    };

    inline LogLevel getLevel(spdlog::level::level_enum level) {
        switch (level) {
            case spdlog::level::debug:
                return debug;

            case spdlog::level::info:
                return info;

            case spdlog::level::warn:
                return warning;

            case spdlog::level::err:
                return error;

            case spdlog::level::critical:
                return critical;

            default:
                return unknown;
        }
    }

    struct ConsoleLog {
        LogLevel level;
        string message;
    };


    namespace Console {

        void initialize();

        void log(LogLevel level, const char* message);
        const vector<ConsoleLog>& get_logs();

        void clean_up();

    }


    template<typename Mutex>
   class _ConsoleSink : public spdlog::sinks::base_sink <Mutex>
    {
    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override
        {
            spdlog::memory_buf_t formatted;
            spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);

            Console::log(
                getLevel(msg.level),
                fmt::to_string(formatted).c_str()
            );
        }

        void flush_() override
        {
            std::cout << std::flush;
        }
    };



}
