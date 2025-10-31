//
// Created by allos on 31/10/2025.
//
#pragma once
#include <chrono>


///Credits to https://github.com/jbikker/tmpl8/blob/master/template/precomp.h
//Used it alot for bomberman and i quite like it :)
class Timer {
public:
    Timer() { reset(); };

    float elapsed() const {
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - start);
        return (float)time_span.count();
    }
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    };

private:
    std::chrono::high_resolution_clock::time_point start;
};