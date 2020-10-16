#pragma once
#include <algorithm>
#include <chrono>
#include <random>

// CUT begin
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// std::shuffle(v.begin(), v.end(), rng);
