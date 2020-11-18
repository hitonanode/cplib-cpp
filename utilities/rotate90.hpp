#pragma once
#include <vector>

// CUT begin
template <typename T> std::vector<std::vector<T>> rotate90(const std::vector<std::vector<T>>& in) {
    const size_t H = in.size(), W = in[0].size();
    std::vector<std::vector<T>> ret(W, std::vector<T>(H));
    for (size_t i = 0; i < H; i++) {
        for (size_t j = 0; j < W; j++) ret[j][i] = in[i][W - 1 - j];
    }
    return ret;
}
