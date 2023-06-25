#pragma once
#include <chrono>

class timer_ {
    std::chrono::system_clock::time_point start_;

public:
    timer_() : start_(now()) {}

    static std::chrono::system_clock::time_point now() { return std::chrono::system_clock::now(); }

    int spent_ms() const {
        auto diff = now() - start_;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    }
} timer;
