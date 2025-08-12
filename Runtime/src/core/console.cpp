//
// Created by allos on 12/08/2025.
//

#include "console.h"




namespace {
    bool is_initialized = false;
    catos::vector<catos::ConsoleLog> logs;
}

namespace catos::Console {


    void initialize() {
        if (is_initialized)
            return;

        is_initialized = true;
        spdlog::default_logger()->sinks().push_back(std::make_shared<_ConsoleSink<std::mutex>>());
    }


    void clean_up() {
    }



    void log(LogLevel level, const char* message) {
        std::cout << "logged";
        logs.push_back({level, message});
    }

    const vector<ConsoleLog>& get_logs() {
        return logs;
    }

}