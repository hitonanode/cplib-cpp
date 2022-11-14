#pragma once
#include <string>
#include <vector>

// Rolling Hash (Rabin-Karp), 2dim
template <typename V> struct rolling_hash_2d {
    const V Bx, By;
    std::vector<V> powx, powy; // powx[i] = Bx^i
    std::vector<std::vector<V>> hash;

    void gen_pow(int h, int w) {
        powx.assign(h + 1, V(1));
        for (int i = 1; i <= h; ++i) powx.at(i) = powx.at(i - 1) * Bx;
        powy.assign(w + 1, V(1));
        for (int i = 1; i <= w; ++i) powy.at(i) = powy.at(i - 1) * By;
    }

    inline V _at(int x, int y) const noexcept {
        if (x < 0 or x >= int(hash.size())) return V();
        if (y < 0 or y >= int(hash[x].size())) return V();
        return hash[x][y];
    }

    template <typename Int> void build(const std::vector<std::vector<Int>> &s) {
        const int H = s.size(), W = H ? s.at(0).size() : 0;
        gen_pow(H, W);

        hash.assign(H, std::vector<V>(W, V()));
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) hash[i][j] = _at(i, j - 1) * By + s[i][j];
        }

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) hash[i][j] = hash[i][j] + _at(i - 1, j) * Bx;
        }
    }

    template <typename Int>
    rolling_hash_2d(const std::vector<std::vector<Int>> &s, V bx, V by) : Bx(bx), By(by) {
        build(s);
    }

    rolling_hash_2d(const std::vector<std::string> &m, V bx, V by) : Bx(bx), By(by) {
        std::vector<std::vector<int>> v_;
        for (const auto &s : m) {
            v_.push_back({});
            for (char c : s) v_.back().push_back(int(c));
        }
        build(v_);
    }

    V get(int xl, int xr, int yl, int yr) const {
        return _at(xr - 1, yr - 1) - _at(xl - 1, yr - 1) * powx[xr - xl] -
               _at(xr - 1, yl - 1) * powy[yr - yl] +
               _at(xl - 1, yl - 1) * powx[xr - xl] * powy[yr - yl];
    }
};
