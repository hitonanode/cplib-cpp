#pragma once
#include <chrono>
#include <random>
#include <string>
#include <vector>
using namespace std;

// CUT begin
struct DoubleHash : public pair<unsigned, unsigned> {
    using ull = unsigned long long;
    static pair<unsigned, unsigned> MODs;
    DoubleHash(pair<unsigned, unsigned> x) : pair(x) {}
    DoubleHash(unsigned x, unsigned y) : pair(x, y) {}
    DoubleHash(unsigned x) : DoubleHash(x, x) {}
    DoubleHash() : DoubleHash(0) {}
    static inline DoubleHash mod_subtract(pair<unsigned, unsigned> x) {
        if (x.first >= MODs.first) x.first -= MODs.first;
        if (x.second >= MODs.second) x.second -= MODs.second;
        return x;
    }
    DoubleHash operator+(const DoubleHash &x) const { return mod_subtract({this->first + x.first, this->second + x.second}); }
    DoubleHash operator+(unsigned x) const { return mod_subtract({this->first + x, this->second + x}); }
    DoubleHash operator-(const DoubleHash &x) const { return mod_subtract({this->first + MODs.first - x.first, this->second + MODs.second - x.second}); }
    DoubleHash operator*(const DoubleHash &x) const { return {unsigned(ull(this->first) * x.first % MODs.first), unsigned(ull(this->second) * x.second % MODs.second)}; }
    DoubleHash operator*(unsigned x) const { return {unsigned(ull(this->first) * x % MODs.first), unsigned(ull(this->second) * x % MODs.second)}; }
    static DoubleHash gen_b(bool force_update = false) {
        static DoubleHash b{0, 0};
        if (b == DoubleHash{0, 0} or force_update) {
            mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
            uniform_int_distribution<unsigned> d(1 << 16, 1 << 29);
            b = {d(mt), d(mt)};
        }
        return b;
    }
};
pair<unsigned, unsigned> DoubleHash::MODs{1000000007, 998244353};

// Rolling Hash (Rabin-Karp), 1dim
template <typename V = DoubleHash> struct rolling_hash {
    int N;
    V B;
    vector<V> hash;  // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]
    vector<V> power; // power[i] = B^i
    rolling_hash(const string &s = "", V b = V::gen_b()) : B(b) {
        N = s.length();
        hash.resize(N + 1), power.resize(N + 1, 1);
        for (int i = 0; i < N; i++) {
            power[i + 1] = power[i] * B;
            hash[i + 1] = hash[i] * B + s[i];
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
