#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <tuple>
#include <vector>

template <class T1, class T2> struct PairHash : public std::pair<T1, T2> {
    using PH = PairHash<T1, T2>;
    explicit PairHash(T1 x, T2 y) : std::pair<T1, T2>(x, y) {}
    explicit PairHash(int x) : std::pair<T1, T2>(x, x) {}
    PairHash() : PairHash(0) {}
    PH operator+(const PH &x) const { return PH(this->first + x.first, this->second + x.second); }
    PH operator-(const PH &x) const { return PH(this->first - x.first, this->second - x.second); }
    PH operator*(const PH &x) const { return PH(this->first * x.first, this->second * x.second); }
    PH operator+(int x) const { return PH(this->first + x, this->second + x); }
    static PH randgen(bool force_update = false) {
        static PH b(0);
        if (b == PH(0) or force_update) {
            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int> d(1 << 30);
            b = PH(T1(d(mt)), T2(d(mt)));
        }
        return b;
    }

    template <class OStream> friend OStream &operator<<(OStream &os, const PH &x) {
        return os << "(" << x.first << ", " << x.second << ")";
    }
};

template <class T1, class T2, class T3> struct TupleHash3 : public std::tuple<T1, T2, T3> {
    using TH = TupleHash3<T1, T2, T3>;
    explicit TupleHash3(T1 x, T2 y, T3 z) : std::tuple<T1, T2, T3>(x, y, z) {}
    explicit TupleHash3(int x) : std::tuple<T1, T2, T3>(x, x, x) {}
    TupleHash3() : TupleHash3(0) {}

    inline const T1 &v1() const noexcept { return std::get<0>(*this); }
    inline const T2 &v2() const noexcept { return std::get<1>(*this); }
    inline const T3 &v3() const noexcept { return std::get<2>(*this); }

    TH operator+(const TH &x) const { return TH(v1() + x.v1(), v2() + x.v2(), v3() + x.v3()); }
    TH operator-(const TH &x) const { return TH(v1() - x.v1(), v2() - x.v2(), v3() - x.v3()); }
    TH operator*(const TH &x) const { return TH(v1() * x.v1(), v2() * x.v2(), v3() * x.v3()); }
    TH operator+(int x) const { return TH(v1() + x, v2() + x, v3() + x); }
    static TH randgen(bool force_update = false) {
        static TH b(0);
        if (b == TH(0) or force_update) {
            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int> d(1 << 30);
            b = TH(T1(d(mt)), T2(d(mt)), T3(d(mt)));
        }
        return b;
    }

    template <class OStream> friend OStream &operator<<(OStream &os, const TH &x) {
        return os << "(" << x.v1() << ", " << x.v2() << ", " << x.v3() << ")";
    }
};

// Rolling Hash (Rabin-Karp), 1dim
template <typename V> struct rolling_hash {
    int N;
    const V B;
    std::vector<V> hash;         // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]
    static std::vector<V> power; // power[i] = B^i
    void _extend_powvec() {
        if (power.size() > 1 and power.at(1) != B) power = {V(1)};
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

    struct Hash {
        int length;
        V val;
        Hash() : length(0), val(V()) {}
        Hash(int len, const V &v) : length(len), val(v) {}

        bool operator==(const Hash &r) const noexcept {
            return length == r.length and val == r.val;
        }

        Hash operator*(const Hash &r) const {
            return Hash(length + r.length, val * power.at(r.length) + r.val);
        }

        template <class OStream> friend OStream &operator<<(OStream &os, const Hash &x) {
            return os << "(length=" << x.length << ", val=" << x.val << ")";
        }
    };

    Hash get(int l, int r) const { // s[l] * B^(r - l - 1) + ... + s[r - 1]
        if (l >= r) return Hash();
        return Hash(r - l, hash[r] - hash[l] * power[r - l]);
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
