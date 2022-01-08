#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Single line reading functions for multi-case & NO final case notification inputs
// Verified: https://codeforces.com/gym/100162/problem/G
std::vector<int> read_ints() {
    std::string s;
    std::getline(std::cin, s);
    if (s.empty()) return {};
    std::stringstream ss(s);
    std::vector<int> ret;
    while (!ss.eof()) {
        int t;
        ss >> t;
        ret.push_back(t);
    }
    return ret;
}

std::string read_str() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}
