#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

template <int MOD1 = 1000000007, int MOD2 = 998244353>
struct DoubleHash : public std::pair<int, int> {
    using ll = long long;
    using pair = std::pair<int, int>;
    DoubleHash(const pair &x) : pair(x) {}
    DoubleHash(int x, int y) : pair(x, y) {}
    explicit DoubleHash(int x) : DoubleHash(x, x) {}
    DoubleHash() : DoubleHash(0) {}
    static inline DoubleHash mod_subtract(pair x) {
        if (x.first >= MOD1) x.first -= MOD1;
        if (x.second >= MOD2) x.second -= MOD2;
        return x;
    }
    DoubleHash operator+(const DoubleHash &x) const {
        return mod_subtract({this->first + x.first, this->second + x.second});
    }
    DoubleHash operator+(unsigned x) const {
        return mod_subtract({this->first + x, this->second + x});
    }
    DoubleHash operator-(const DoubleHash &x) const {
        return mod_subtract({this->first + MOD1 - x.first, this->second + MOD2 - x.second});
    }
    DoubleHash operator*(const DoubleHash &x) const {
        return {int(ll(this->first) * x.first % MOD1), int(ll(this->second) * x.second % MOD2)};
    }
    static DoubleHash randgen(bool force_update = false) {
        static DoubleHash b{0, 0};
        if (b == DoubleHash{0, 0} or force_update) {
            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int> d(1 << 16, 1 << 30);
            b = {d(mt), d(mt)};
        }
        return b;
    }
};

// Rolling Hash (Rabin-Karp), 1dim
template <typename V = DoubleHash<>> struct rolling_hash {
    int N;
    const V B;
    std::vector<V> hash;         // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]
    static std::vector<V> power; // power[i] = B^i
    void _extend_powvec() {
        while (static_cast<int>(power.size()) <= N) {
            auto tmp = power.back() * B;
            power.push_back(tmp);
        }
    }
    template <typename Int>
    rolling_hash(const std::vector<Int> &s, V b = V::randgen()) : N(s.size()), B(b), hash(N + 1) {
        for (int i = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];
        _extend_powvec();
    }
    rolling_hash(const std::string &s = "", V b = V::randgen()) : N(s.size()), B(b), hash(N + 1) {
        for (int i = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];
        _extend_powvec();
    }
    void addchar(const char &c) {
        V hnew = hash[N] * B + c;
        N++, hash.emplace_back(hnew);
        _extend_powvec();
    }
    V get(int l, int r) const { // s[l] * B^(r - l - 1) + ... + s[r - 1]
        return hash[r] - hash[l] * power[r - l];
    }
    int lcplen(int l1, int l2) const { return longest_common_prefix(*this, l1, *this, l2); }
};
template <typename V> std::vector<V> rolling_hash<V>::power{V(1)};

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
