#pragma once
#include <chrono>

// CUT begin
auto START = std::chrono::system_clock::now();
int64_t spent_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - START).count();
