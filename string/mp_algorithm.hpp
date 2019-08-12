#pragma once
#include <string>
#include <vector>


std::vector<int> mp_algorithm(std::string s) {
    int N = s.length();
    std::vector<int> ret(N + 1, -1);
    int j = -1;
    for (int i = 0; i < N;  i++) {
        while (j >= 0 and s[i] != s[j]) j = ret[j];
        ret[i + 1] = ++j;
    }
    return ret;
}
