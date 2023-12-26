---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: string/lyndon.hpp
    title: "Lyndon words \uFF08Lyndon \u6587\u5B57\u5217\u306B\u95A2\u3059\u308B\u5404\
      \u7A2E\u95A2\u6570\uFF09"
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash_1d.hpp
    title: "Rolling hash (one dimensional) \uFF08\u4E00\u6B21\u5143\u30ED\u30FC\u30EA\
      \u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/runenumerate
    links:
    - https://judge.yosupo.jp/problem/runenumerate
  bundledCode: "#line 2 \"modint.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <set>\n#include <vector>\n\ntemplate <int md> struct ModInt {\n    using\
    \ lint = long long;\n    constexpr static int mod() { return md; }\n    static\
    \ int get_primitive_root() {\n        static int primitive_root = 0;\n       \
    \ if (!primitive_root) {\n            primitive_root = [&]() {\n             \
    \   std::set<int> fac;\n                int v = md - 1;\n                for (lint\
    \ i = 2; i * i <= v; i++)\n                    while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < md; g++) {\n                    bool ok = true;\n               \
    \     for (auto i : fac)\n                        if (ModInt(g).pow((md - 1) /\
    \ i) == 1) {\n                            ok = false;\n                      \
    \      break;\n                        }\n                    if (ok) return g;\n\
    \                }\n                return -1;\n            }();\n        }\n\
    \        return primitive_root;\n    }\n    int val_;\n    int val() const noexcept\
    \ { return val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    constexpr\
    \ ModInt(lint v) { _setval(v % md + md); }\n    constexpr explicit operator bool()\
    \ const { return val_ != 0; }\n    constexpr ModInt operator+(const ModInt &x)\
    \ const {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    constexpr\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    constexpr\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    constexpr ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    constexpr ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint\
    \ a, const ModInt &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint\
    \ a, const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
    \ a, const ModInt &x) { return ModInt(a) / x; }\n    constexpr bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    constexpr bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    constexpr bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    constexpr\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n\n    constexpr ModInt pow(lint n) const {\n\
    \        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n\
    \ & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static constexpr int cache_limit = std::min(md, 1 << 21);\n\
    \    static std::vector<ModInt> facs, facinvs, invs;\n\n    constexpr static void\
    \ _precalculation(int N) {\n        const int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr\
    \ ModInt inv() const {\n        if (this->val_ < cache_limit) {\n            if\
    \ (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n            while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val_];\n\
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n \
    \   constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val_];\n    }\n\
    \    constexpr ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    constexpr ModInt doublefac() const {\n        lint k = (this->val_ +\
    \ 1) / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr ModInt nCr(int r) const {\n        if (r < 0 or this->val_\
    \ < r) return ModInt(0);\n        return this->fac() * (*this - r).facinv() *\
    \ ModInt(r).facinv();\n    }\n\n    constexpr ModInt nPr(int r) const {\n    \
    \    if (r < 0 or this->val_ < r) return ModInt(0);\n        return this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    static ModInt binom(int n, int r) {\n\
    \        static long long bruteforce_times = 0;\n\n        if (r < 0 or n < r)\
    \ return ModInt(0);\n        if (n <= bruteforce_times or n < (int)facs.size())\
    \ return ModInt(n).nCr(r);\n\n        r = std::min(r, n - r);\n\n        ModInt\
    \ ret = ModInt(r).facinv();\n        for (int i = 0; i < r; ++i) ret *= n - i;\n\
    \        bruteforce_times += r;\n\n        return ret;\n    }\n\n    // Multinomial\
    \ coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n    // Complexity:\
    \ O(sum(ks))\n    template <class Vec> static ModInt multinomial(const Vec &ks)\
    \ {\n        ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n\
    \            assert(k >= 0);\n            ret *= ModInt(k).facinv(), sum += k;\n\
    \        }\n        return ret * ModInt(sum).fac();\n    }\n\n    // Catalan number,\
    \ C_n = binom(2n, n) / (n + 1)\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4\
    \ = 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt(n * 2).fac() * ModInt(n + 1).facinv() * ModInt(n).facinv();\n    }\n\n\
    \    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
    \ 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n        ModInt\
    \ b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0,\
    \ m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j\
    \ - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val_, md - x.val_));\n    }\n};\ntemplate <int\
    \ md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\ntemplate <int md> std::vector<ModInt<md>>\
    \ ModInt<md>::facinvs = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::invs\
    \ = {0};\n\nusing ModInt998244353 = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n\
    // using mint = ModInt<1000000007>;\n#line 2 \"string/lyndon.hpp\"\n#include <algorithm>\n\
    #line 4 \"string/lyndon.hpp\"\n#include <functional>\n#include <string>\n#include\
    \ <tuple>\n#include <utility>\n#line 9 \"string/lyndon.hpp\"\n\n// CUT begin\n\
    // Lyndon factorization based on Duval's algorithm\n// **NOT VERIFIED YET**\n\
    // Reference:\n// [1] K. T. Chen, R. H. Fox, R. C. Lyndon,\n//     \"Free Differential\
    \ Calculus, IV. The Quotient Groups of the Lower Central Series,\"\n//     Annals\
    \ of Mathematics, 68(1), 81-95, 1958.\n// [2] J. P. Duval, \"Factorizing words\
    \ over an ordered alphabet,\"\n//     Journal of Algorithms, 4(4), 363-381, 1983.\n\
    // - https://cp-algorithms.com/string/lyndon_factorization.html\n// - https://qiita.com/nakashi18/items/66882bd6e0127174267a\n\
    template <typename T>\nstd::vector<std::pair<int, int>> lyndon_factorization(const\
    \ std::vector<T> &S) {\n    const int N = S.size();\n    std::vector<std::pair<int,\
    \ int>> ret;\n    for (int l = 0; l < N;) {\n        int i = l, j = i + 1;\n \
    \       while (j < N and S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;\n\
    \        int n = (j - l) / (j - i);\n        for (int t = 0; t < n; t++) ret.emplace_back(l,\
    \ j - i), l += j - i;\n    }\n    return ret;\n}\n\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const std::string &s) {\n    const int N = int(s.size());\n\
    \    std::vector<int> v(N);\n    for (int i = 0; i < N; i++) v[i] = s[i];\n  \
    \  return lyndon_factorization<int>(v);\n}\n\n// Compute the longest Lyndon prefix\
    \ for each suffix s[i:N]\n// (Our implementation is $O(N \\cdot (complexity of\
    \ lcplen()))$)\n// Example:\n// - `teletelepathy` -> [1,4,1,2,1,4,1,2,1,4,1,2,1]\n\
    // Reference:\n// [1] H. Bannai et al., \"The \"Runs\" Theorem,\"\n//     SIAM\
    \ Journal on Computing, 46(5), 1501-1514, 2017.\ntemplate <typename String, typename\
    \ LCPLENCallable>\nstd::vector<int> longest_lyndon_prefixes(const String &s, const\
    \ LCPLENCallable &lcp) {\n    const int N = s.size();\n    std::vector<std::pair<int,\
    \ int>> st{{N, N}};\n    std::vector<int> ret(N);\n    for (int i = N - 1, j =\
    \ i; i >= 0; i--, j = i) {\n        while (st.size() > 1) {\n            int iv\
    \ = st.back().first, jv = st.back().second;\n            int l = lcp.lcplen(i,\
    \ iv);\n            if (!(iv + l < N and s[i + l] < s[iv + l])) break;\n     \
    \       j = jv;\n            st.pop_back();\n        }\n        st.emplace_back(i,\
    \ j);\n        ret[i] = j - i + 1;\n    }\n    return ret;\n}\n\n// Compute all\
    \ runs in given string\n// Complexity: $O(N \\cdot (complexity of lcplen()))$\
    \ in this implementation\n// (Theoretically $O(N)$ achievable)\n// N = 2e5 ->\
    \ ~120 ms\n// Reference:\n// [1] H. Bannai et al., \"The \"Runs\" Theorem,\"\n\
    //     SIAM Journal on Computing, 46(5), 1501-1514, 2017.\ntemplate <typename\
    \ LCPLENCallable, typename String>\nstd::vector<std::tuple<int, int, int>> run_enumerate(String\
    \ s) {\n    if (s.empty()) return {};\n    LCPLENCallable lcp(s);\n    std::reverse(s.begin(),\
    \ s.end());\n    LCPLENCallable revlcp(s);\n    std::reverse(s.begin(), s.end());\n\
    \    auto t = s;\n    auto lo = *std::min_element(s.begin(), s.end()), hi = *std::max_element(s.begin(),\
    \ s.end());\n    for (auto &c : t) c = hi - (c - lo);\n    auto l1 = longest_lyndon_prefixes(s,\
    \ lcp), l2 = longest_lyndon_prefixes(t, lcp);\n    int N = s.size();\n    std::vector<std::tuple<int,\
    \ int, int>> ret;\n    for (int i = 0; i < N; i++) {\n        int j = i + l1[i],\
    \ L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i, j);\n        if (R\
    \ - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);\n\n        if (l1[i] != l2[i])\
    \ {\n            j = i + l2[i], L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i,\
    \ j);\n            if (R - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);\n\
    \        }\n    }\n    std::sort(ret.begin(), ret.end());\n    ret.erase(std::unique(ret.begin(),\
    \ ret.end()), ret.end());\n    return ret;\n}\n\n// Enumerate Lyndon words up\
    \ to length n in lexical order\n// https://github.com/bqi343/USACO/blob/master/Implementations/content/combinatorial%20(11.2)/DeBruijnSeq.h\n\
    // Example: k=2, n=4 => [[0,],[0,0,0,1,],[0,0,1,],[0,0,1,1,],[0,1,],[0,1,1,],[0,1,1,1,],[1,],]\n\
    // Verified: https://codeforces.com/gym/102001/problem/C / https://codeforces.com/gym/100162/problem/G\n\
    std::vector<std::vector<int>> enumerate_lyndon_words(int k, int n) {\n    assert(k\
    \ > 0);\n    assert(n > 0);\n    std::vector<std::vector<int>> ret;\n    std::vector<int>\
    \ aux(n + 1);\n\n    std::function<void(int, int)> gen = [&](int t, int p) {\n\
    \        // t: current length\n        // p: current min cycle length\n      \
    \  if (t == n) {\n            std::vector<int> tmp(aux.begin() + 1, aux.begin()\
    \ + p + 1);\n            ret.push_back(std::move(tmp));\n        } else {\n  \
    \          ++t;\n            aux[t] = aux[t - p];\n            gen(t, p);\n  \
    \          while (++aux[t] < k) gen(t, t);\n        }\n    };\n    gen(0, 1);\n\
    \    return ret;\n}\n#line 3 \"string/rolling_hash_1d.hpp\"\n#include <chrono>\n\
    #include <random>\n#line 8 \"string/rolling_hash_1d.hpp\"\n\ntemplate <class T1,\
    \ class T2> struct PairHash : public std::pair<T1, T2> {\n    using PH = PairHash<T1,\
    \ T2>;\n    explicit PairHash(T1 x, T2 y) : std::pair<T1, T2>(x, y) {}\n    explicit\
    \ PairHash(int x) : std::pair<T1, T2>(x, x) {}\n    PairHash() : PairHash(0) {}\n\
    \    PH operator+(const PH &x) const { return PH(this->first + x.first, this->second\
    \ + x.second); }\n    PH operator-(const PH &x) const { return PH(this->first\
    \ - x.first, this->second - x.second); }\n    PH operator*(const PH &x) const\
    \ { return PH(this->first * x.first, this->second * x.second); }\n    PH operator+(int\
    \ x) const { return PH(this->first + x, this->second + x); }\n    static PH randgen(bool\
    \ force_update = false) {\n        static PH b(0);\n        if (b == PH(0) or\
    \ force_update) {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<int> d(1 << 30);\n            b = PH(T1(d(mt)),\
    \ T2(d(mt)));\n        }\n        return b;\n    }\n\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const PH &x) {\n        return os <<\
    \ \"(\" << x.first << \", \" << x.second << \")\";\n    }\n};\n\ntemplate <class\
    \ T1, class T2, class T3> struct TupleHash3 : public std::tuple<T1, T2, T3> {\n\
    \    using TH = TupleHash3<T1, T2, T3>;\n    explicit TupleHash3(T1 x, T2 y, T3\
    \ z) : std::tuple<T1, T2, T3>(x, y, z) {}\n    explicit TupleHash3(int x) : std::tuple<T1,\
    \ T2, T3>(x, x, x) {}\n    TupleHash3() : TupleHash3(0) {}\n\n    inline const\
    \ T1 &v1() const noexcept { return std::get<0>(*this); }\n    inline const T2\
    \ &v2() const noexcept { return std::get<1>(*this); }\n    inline const T3 &v3()\
    \ const noexcept { return std::get<2>(*this); }\n\n    TH operator+(const TH &x)\
    \ const { return TH(v1() + x.v1(), v2() + x.v2(), v3() + x.v3()); }\n    TH operator-(const\
    \ TH &x) const { return TH(v1() - x.v1(), v2() - x.v2(), v3() - x.v3()); }\n \
    \   TH operator*(const TH &x) const { return TH(v1() * x.v1(), v2() * x.v2(),\
    \ v3() * x.v3()); }\n    TH operator+(int x) const { return TH(v1() + x, v2()\
    \ + x, v3() + x); }\n    static TH randgen(bool force_update = false) {\n    \
    \    static TH b(0);\n        if (b == TH(0) or force_update) {\n            std::mt19937\
    \ mt(std::chrono::steady_clock::now().time_since_epoch().count());\n         \
    \   std::uniform_int_distribution<int> d(1 << 30);\n            b = TH(T1(d(mt)),\
    \ T2(d(mt)), T3(d(mt)));\n        }\n        return b;\n    }\n\n    template\
    \ <class OStream> friend OStream &operator<<(OStream &os, const TH &x) {\n   \
    \     return os << \"(\" << x.v1() << \", \" << x.v2() << \", \" << x.v3() <<\
    \ \")\";\n    }\n};\n\n// Rolling Hash (Rabin-Karp), 1dim\ntemplate <typename\
    \ V> struct rolling_hash {\n    int N;\n    const V B;\n    std::vector<V> hash;\
    \         // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]\n    static std::vector<V>\
    \ power; // power[i] = B^i\n    void _extend_powvec() {\n        if (power.size()\
    \ > 1 and power.at(1) != B) power = {V(1)};\n        while (static_cast<int>(power.size())\
    \ <= N) {\n            auto tmp = power.back() * B;\n            power.push_back(tmp);\n\
    \        }\n    }\n    template <typename Int>\n    rolling_hash(const std::vector<Int>\
    \ &s, V b = V::randgen()) : N(s.size()), B(b), hash(N + 1) {\n        for (int\
    \ i = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];\n        _extend_powvec();\n\
    \    }\n    rolling_hash(const std::string &s = \"\", V b = V::randgen()) : N(s.size()),\
    \ B(b), hash(N + 1) {\n        for (int i = 0; i < N; i++) hash[i + 1] = hash[i]\
    \ * B + s[i];\n        _extend_powvec();\n    }\n    void addchar(const char &c)\
    \ {\n        V hnew = hash[N] * B + c;\n        N++, hash.emplace_back(hnew);\n\
    \        _extend_powvec();\n    }\n\n    struct Hash {\n        int length;\n\
    \        V val;\n        Hash() : length(0), val(V()) {}\n        Hash(int len,\
    \ const V &v) : length(len), val(v) {}\n\n        bool operator==(const Hash &r)\
    \ const noexcept {\n            return length == r.length and val == r.val;\n\
    \        }\n\n        Hash operator*(const Hash &r) const {\n            return\
    \ Hash(length + r.length, val * power.at(r.length) + r.val);\n        }\n\n  \
    \      template <class OStream> friend OStream &operator<<(OStream &os, const\
    \ Hash &x) {\n            return os << \"(length=\" << x.length << \", val=\"\
    \ << x.val << \")\";\n        }\n    };\n\n    Hash get(int l, int r) const {\
    \ // s[l] * B^(r - l - 1) + ... + s[r - 1]\n        if (l >= r) return Hash();\n\
    \        return Hash(r - l, hash[r] - hash[l] * power[r - l]);\n    }\n\n    int\
    \ lcplen(int l1, int l2) const { return longest_common_prefix(*this, l1, *this,\
    \ l2); }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{V(1)};\n\
    \n// Longest common prerfix between s1[l1, N1) and s2[l2, N2)\ntemplate <typename\
    \ T>\nint longest_common_prefix(const rolling_hash<T> &rh1, int l1, const rolling_hash<T>\
    \ &rh2, int l2) {\n    int lo = 0, hi = std::min(rh1.N + 1 - l1, rh2.N + 1 - l2);\n\
    \    while (hi - lo > 1) {\n        const int c = (lo + hi) / 2;\n        auto\
    \ h1 = rh1.get(l1, l1 + c), h2 = rh2.get(l2, l2 + c);\n        (h1 == h2 ? lo\
    \ : hi) = c;\n    }\n    return lo;\n}\n// Longest common suffix between s1[0,\
    \ r1) and s2[0, r2)\ntemplate <typename T>\nint longest_common_suffix(const rolling_hash<T>\
    \ &rh1, int r1, const rolling_hash<T> &rh2, int r2) {\n    int lo = 0, hi = std::min(r1,\
    \ r2) + 1;\n    while (hi - lo > 1) {\n        const int c = (lo + hi) / 2;\n\
    \        auto h1 = rh1.get(r1 - c, r1), h2 = rh2.get(r2 - c, r2);\n        (h1\
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n#line 6 \"string/test/run_enumerate_lyndon_hash.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   string S;\n    cin >> S;\n    auto ret = run_enumerate<rolling_hash<PairHash<ModInt998244353,\
    \ ModInt998244353>>>(S);\n    cout << ret.size() << '\\n';\n    for (auto p :\
    \ ret) cout << get<0>(p) << ' ' << get<1>(p) << ' ' << get<2>(p) << '\\n';\n}\n"
  code: "#include \"../../modint.hpp\"\n#include \"../lyndon.hpp\"\n#include \"../rolling_hash_1d.hpp\"\
    \n#include <iostream>\n#include <string>\n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    string S;\n    cin >> S;\n    auto ret = run_enumerate<rolling_hash<PairHash<ModInt998244353,\
    \ ModInt998244353>>>(S);\n    cout << ret.size() << '\\n';\n    for (auto p :\
    \ ret) cout << get<0>(p) << ' ' << get<1>(p) << ' ' << get<2>(p) << '\\n';\n}\n"
  dependsOn:
  - modint.hpp
  - string/lyndon.hpp
  - string/rolling_hash_1d.hpp
  isVerificationFile: true
  path: string/test/run_enumerate_lyndon_hash.test.cpp
  requiredBy: []
  timestamp: '2023-12-26 21:26:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/run_enumerate_lyndon_hash.test.cpp
layout: document
redirect_from:
- /verify/string/test/run_enumerate_lyndon_hash.test.cpp
- /verify/string/test/run_enumerate_lyndon_hash.test.cpp.html
title: string/test/run_enumerate_lyndon_hash.test.cpp
---
