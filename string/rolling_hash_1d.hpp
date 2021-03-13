#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

// CUT begin
struct DoubleHash : public std::pair<unsigned, unsigned> {
    using ull = unsigned long long;
    using pair = std::pair<unsigned, unsigned>;
    static std::pair<unsigned, unsigned> MODs;
    DoubleHash(std::pair<unsigned, unsigned> x) : pair(x) {}
    DoubleHash(unsigned x, unsigned y) : pair(x, y) {}
    DoubleHash(unsigned x) : DoubleHash(x, x) {}
    DoubleHash() : DoubleHash(0) {}
    static inline DoubleHash mod_subtract(pair x) {
        if (x.first >= MODs.first) x.first -= MODs.first;
        if (x.second >= MODs.second) x.second -= MODs.second;
        return x;
    }
    DoubleHash operator+(const DoubleHash &x) const {
        return mod_subtract({this->first + x.first, this->second + x.second});
    }
    DoubleHash operator+(unsigned x) const { return mod_subtract({this->first + x, this->second + x}); }
    DoubleHash operator-(const DoubleHash &x) const {
        return mod_subtract({this->first + MODs.first - x.first, this->second + MODs.second - x.second});
    }
    DoubleHash operator*(const DoubleHash &x) const {
        return {unsigned(ull(this->first) * x.first % MODs.first), unsigned(ull(this->second) * x.second % MODs.second)};
    }
    DoubleHash operator*(unsigned x) const {
        return {unsigned(ull(this->first) * x % MODs.first), unsigned(ull(this->second) * x % MODs.second)};
    }
    static DoubleHash gen_b(bool force_update = false) {
        static DoubleHash b{0, 0};
        if (b == DoubleHash{0, 0} or force_update) {
            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<unsigned> d(1 << 16, 1 << 29);
            b = {d(mt), d(mt)};
        }
        return b;
    }
};
std::pair<unsigned, unsigned> DoubleHash::MODs{1000000007, 998244353};

// Rolling Hash (Rabin-Karp), 1dim
template <typename V = DoubleHash> struct rolling_hash {
    int N;
    const V B;
    std::vector<V> hash;         // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]
    static std::vector<V> power; // power[i] = B^i
    rolling_hash(const std::string &s = "", V b = V::gen_b()) : B(b) {
        N = s.length();
        hash.resize(N + 1);
        for (int i = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];
        while (static_cast<int>(power.size()) <= N) {
            auto tmp = power.back() * B;
            power.push_back(tmp);
        }
    }
    void addchar(const char &c) {
        V hnew = hash[N] * B + c, pnew = power[N] * B;
        N++, hash.emplace_back(hnew), power.emplace_back(pnew);
    }
    V get(int l, int r) const { // s[l] * B^(r - l - 1) + ... + s[r - 1]
        return hash[r] - hash[l] * power[r - l];
    }
};
template <typename V> std::vector<V> rolling_hash<V>::power{1};

// Longest common prerfix between s1[l1, N1) and s2[l2, N2)
template <typename T>
int longest_common_prefix(const rolling_hash<T> &rh1, int l1, const rolling_hash<T> &rh2, int l2) {
    int lo = 0, hi = std::min(rh1.N + 1 - l1, rh2.N + 1 - l2);
    while (hi - lo > 1) {
        const int c = (lo + hi) / 2;
        auto h1 = rh1.get(l1, l1 + c), h2 = rh2.get(l2, l2 + c);
        (h1 == h2 ? lo : hi) = c;
    }
    return lo;
}
// Longest common suffix between s1[0, r1) and s2[0, r2)
template <typename T>
int longest_common_suffix(const rolling_hash<T> &rh1, int r1, const rolling_hash<T> &rh2, int r2) {
    int lo = 0, hi = std::min(r1, r2) + 1;
    while (hi - lo > 1) {
        const int c = (lo + hi) / 2;
        auto h1 = rh1.get(r1 - c, r1), h2 = rh2.get(r2 - c, r2);
        (h1 == h2 ? lo : hi) = c;
    }
    return lo;
}
