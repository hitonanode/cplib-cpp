---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/modint_mersenne61.hpp
    title: "$\\mathbb{F}_{2^{61} - 1}$ \uFF08\u30CF\u30C3\u30B7\u30E5\u7528\u30E1\u30EB\
      \u30BB\u30F3\u30CC\u7D20\u6570 modint\uFF09"
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
  bundledCode: "#line 2 \"number/modint_mersenne61.hpp\"\n#include <cassert>\n#include\
    \ <chrono>\n#include <random>\n\n// F_p, p = 2^61 - 1\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    class ModIntMersenne61 {\n    static const long long md = (1LL << 61) - 1;\n \
    \   long long _v;\n\n    inline unsigned hi() const noexcept { return _v >> 31;\
    \ }\n    inline unsigned lo() const noexcept { return _v & ((1LL << 31) - 1);\
    \ }\n\npublic:\n    static long long mod() { return md; }\n\n    ModIntMersenne61()\
    \ : _v(0) {}\n    // 0 <= x < md * 2\n    explicit ModIntMersenne61(long long\
    \ x) : _v(x >= md ? x - md : x) {}\n\n    long long val() const noexcept { return\
    \ _v; }\n\n    ModIntMersenne61 operator+(const ModIntMersenne61 &x) const {\n\
    \        return ModIntMersenne61(_v + x._v);\n    }\n\n    ModIntMersenne61 operator-(const\
    \ ModIntMersenne61 &x) const {\n        return ModIntMersenne61(_v + md - x._v);\n\
    \    }\n\n    ModIntMersenne61 operator*(const ModIntMersenne61 &x) const {\n\
    \        using ull = unsigned long long;\n\n        ull uu = (ull)hi() * x.hi()\
    \ * 2;\n        ull ll = (ull)lo() * x.lo();\n        ull lu = (ull)hi() * x.lo()\
    \ + (ull)lo() * x.hi();\n\n        ull sum = uu + ll + ((lu & ((1ULL << 30) -\
    \ 1)) << 31) + (lu >> 30);\n        ull reduced = (sum >> 61) + (sum & ull(md));\n\
    \        return ModIntMersenne61(reduced);\n    }\n\n    ModIntMersenne61 pow(long\
    \ long n) const {\n        assert(n >= 0);\n        ModIntMersenne61 ans(1), tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    ModIntMersenne61\
    \ inv() const { return pow(md - 2); }\n\n    ModIntMersenne61 operator/(const\
    \ ModIntMersenne61 &x) const { return *this * x.inv(); }\n\n    ModIntMersenne61\
    \ operator-() const { return ModIntMersenne61(md - _v); }\n    ModIntMersenne61\
    \ &operator+=(const ModIntMersenne61 &x) { return *this = *this + x; }\n    ModIntMersenne61\
    \ &operator-=(const ModIntMersenne61 &x) { return *this = *this - x; }\n    ModIntMersenne61\
    \ &operator*=(const ModIntMersenne61 &x) { return *this = *this * x; }\n    ModIntMersenne61\
    \ &operator/=(const ModIntMersenne61 &x) { return *this = *this / x; }\n\n   \
    \ ModIntMersenne61 operator+(unsigned x) const { return ModIntMersenne61(this->_v\
    \ + x); }\n\n    bool operator==(const ModIntMersenne61 &x) const { return _v\
    \ == x._v; }\n    bool operator!=(const ModIntMersenne61 &x) const { return _v\
    \ != x._v; }\n    bool operator<(const ModIntMersenne61 &x) const { return _v\
    \ < x._v; } // To use std::map\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const ModIntMersenne61 &x) {\n        return os <<\
    \ x._v;\n    }\n\n    static ModIntMersenne61 randgen(bool force_update = false)\
    \ {\n        static ModIntMersenne61 b(0);\n        if (b == ModIntMersenne61(0)\
    \ or force_update) {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<long long> d(1, ModIntMersenne61::mod());\n\
    \            b = ModIntMersenne61(d(mt));\n        }\n        return b;\n    }\n\
    };\n#line 2 \"string/lyndon.hpp\"\n#include <algorithm>\n#line 4 \"string/lyndon.hpp\"\
    \n#include <functional>\n#include <string>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Lyndon factorization based on Duval's algorithm\n\
    // **NOT VERIFIED YET**\n// Reference:\n// [1] K. T. Chen, R. H. Fox, R. C. Lyndon,\n\
    //     \"Free Differential Calculus, IV. The Quotient Groups of the Lower Central\
    \ Series,\"\n//     Annals of Mathematics, 68(1), 81-95, 1958.\n// [2] J. P. Duval,\
    \ \"Factorizing words over an ordered alphabet,\"\n//     Journal of Algorithms,\
    \ 4(4), 363-381, 1983.\n// - https://cp-algorithms.com/string/lyndon_factorization.html\n\
    // - https://qiita.com/nakashi18/items/66882bd6e0127174267a\ntemplate <typename\
    \ T>\nstd::vector<std::pair<int, int>> lyndon_factorization(const std::vector<T>\
    \ &S) {\n    const int N = S.size();\n    std::vector<std::pair<int, int>> ret;\n\
    \    for (int l = 0; l < N;) {\n        int i = l, j = i + 1;\n        while (j\
    \ < N and S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;\n        int n =\
    \ (j - l) / (j - i);\n        for (int t = 0; t < n; t++) ret.emplace_back(l,\
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
    \    return ret;\n}\n#line 8 \"string/rolling_hash_1d.hpp\"\n\ntemplate <class\
    \ T1, class T2> struct PairHash : public std::pair<T1, T2> {\n    using PH = PairHash<T1,\
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
    \        }\n\n        bool operator<(const Hash &x) const { // To use std::map\n\
    \            if (length != x.length) return length < x.length;\n            return\
    \ val < x.val;\n        }\n\n        Hash operator*(const Hash &r) const {\n \
    \           return Hash(length + r.length, val * power.at(r.length) + r.val);\n\
    \        }\n\n        template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const Hash &x) {\n            return os << \"(length=\" << x.length <<\
    \ \", val=\" << x.val << \")\";\n        }\n    };\n\n    Hash get(int l, int\
    \ r) const { // s[l] * B^(r - l - 1) + ... + s[r - 1]\n        if (l >= r) return\
    \ Hash();\n        return Hash(r - l, hash[r] - hash[l] * power[r - l]);\n   \
    \ }\n\n    int lcplen(int l1, int l2) const { return longest_common_prefix(*this,\
    \ l1, *this, l2); }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{V(1)};\n\
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
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n#line 4 \"string/test/run_enumerate_lyndon_mersenne61.test.cpp\"\
    \n#include <iostream>\n#line 6 \"string/test/run_enumerate_lyndon_mersenne61.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   string S;\n    cin >> S;\n    auto ret = run_enumerate<rolling_hash<ModIntMersenne61>>(S);\n\
    \    cout << ret.size() << '\\n';\n    for (auto p : ret) cout << get<0>(p) <<\
    \ ' ' << get<1>(p) << ' ' << get<2>(p) << '\\n';\n}\n"
  code: "#include \"../../number/modint_mersenne61.hpp\"\n#include \"../lyndon.hpp\"\
    \n#include \"../rolling_hash_1d.hpp\"\n#include <iostream>\n#include <string>\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   string S;\n    cin >> S;\n    auto ret = run_enumerate<rolling_hash<ModIntMersenne61>>(S);\n\
    \    cout << ret.size() << '\\n';\n    for (auto p : ret) cout << get<0>(p) <<\
    \ ' ' << get<1>(p) << ' ' << get<2>(p) << '\\n';\n}\n"
  dependsOn:
  - number/modint_mersenne61.hpp
  - string/lyndon.hpp
  - string/rolling_hash_1d.hpp
  isVerificationFile: true
  path: string/test/run_enumerate_lyndon_mersenne61.test.cpp
  requiredBy: []
  timestamp: '2024-01-13 20:34:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/run_enumerate_lyndon_mersenne61.test.cpp
layout: document
redirect_from:
- /verify/string/test/run_enumerate_lyndon_mersenne61.test.cpp
- /verify/string/test/run_enumerate_lyndon_mersenne61.test.cpp.html
title: string/test/run_enumerate_lyndon_mersenne61.test.cpp
---
