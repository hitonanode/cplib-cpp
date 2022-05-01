#pragma once
#include <string>
#include <vector>

template <typename T> std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &v) {
    const int H = v.size(), W = v[0].size();
    std::vector<std::vector<T>> ret(W, std::vector<T>(H));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) ret[j][i] = v[i][j];
    }
    return ret;
}

std::vector<std::string> transpose(const std::vector<std::string> &v) {
    const int H = v.size(), W = v[0].size();
    std::vector<std::string> ret(W, std::string(H, '\0'));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) ret[j][i] = v[i][j];
    }
    return ret;
}
