#pragma once
#include <string>
#include <vector>

template <typename T> std::vector<std::vector<T>> rotate90(const std::vector<std::vector<T>> &in) {
    const int H = in.size(), W = in[0].size();
    std::vector<std::vector<T>> ret(W, std::vector<T>(H));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) ret[j][i] = in[i][W - 1 - j];
    }
    return ret;
}

std::vector<std::string> rotate90(const std::vector<std::string> &in) {
    const int H = in.size(), W = in[0].size();
    std::vector<std::string> ret(W, std::string(H, '\0'));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) ret[j][i] = in[i][W - 1 - j];
    }
    return ret;
}
