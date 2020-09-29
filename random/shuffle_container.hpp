#pragma once
#include <algorithm>
#include <random>

// CUT begin
std::random_device seed_gen;
std::mt19937 engine(seed_gen());
// std::shuffle(v.begin(), v.end(), engine);
