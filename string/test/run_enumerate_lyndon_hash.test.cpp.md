---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.hpp
    title: "Lyndon factorization \uFF08Lyndon \u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash_1d.hpp
    title: string/rolling_hash_1d.hpp
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
  bundledCode: "#line 2 \"string/lyndon_factorization.hpp\"\n#include <algorithm>\n\
    #include <string>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// Lyndon factorization based on Duval's algorithm\n// **NOT VERIFIED\
    \ YET**\n// Reference:\n// [1] K. T. Chen, R. H. Fox, R. C. Lyndon,\n//     \"\
    Free Differential Calculus, IV. The Quotient Groups of the Lower Central Series,\"\
    \n//     Annals of Mathematics, 81-95, 1958.\n// [2] J. P. Duval, \"Factorizing\
    \ words over an ordered alphabet,\"\n//     Journal of Algorithms, 4(4), 363-381,\
    \ 1983.\n// - https://cp-algorithms.com/string/lyndon_factorization.html\n// -\
    \ https://qiita.com/nakashi18/items/66882bd6e0127174267a\ntemplate <typename T>\
    \ std::vector<std::pair<int, int>> lyndon_factorization(const std::vector<T> &S)\
    \ {\n    const int N = S.size();\n    std::vector<std::pair<int, int>> ret;\n\
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
    \ Journal on Computing, 46.5, 1501-1514, 2017.\ntemplate <typename String, typename\
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
    //     SIAM Journal on Computing, 46.5, 1501-1514, 2017.\ntemplate <typename LCPLENCallable,\
    \ typename String> std::vector<std::tuple<int, int, int>> run_enumerate(String\
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
    \ ret.end()), ret.end());\n    return ret;\n}\n#line 3 \"string/rolling_hash_1d.hpp\"\
    \n#include <chrono>\n#include <random>\n#line 7 \"string/rolling_hash_1d.hpp\"\
    \n\n// CUT begin\nstruct DoubleHash : public std::pair<unsigned, unsigned> {\n\
    \    using ull = unsigned long long;\n    using pair = std::pair<unsigned, unsigned>;\n\
    \    static std::pair<unsigned, unsigned> MODs;\n    DoubleHash(std::pair<unsigned,\
    \ unsigned> x) : pair(x) {}\n    DoubleHash(unsigned x, unsigned y) : pair(x,\
    \ y) {}\n    DoubleHash(unsigned x) : DoubleHash(x, x) {}\n    DoubleHash() :\
    \ DoubleHash(0) {}\n    static inline DoubleHash mod_subtract(pair x) {\n    \
    \    if (x.first >= MODs.first) x.first -= MODs.first;\n        if (x.second >=\
    \ MODs.second) x.second -= MODs.second;\n        return x;\n    }\n    DoubleHash\
    \ operator+(const DoubleHash &x) const {\n        return mod_subtract({this->first\
    \ + x.first, this->second + x.second});\n    }\n    DoubleHash operator+(unsigned\
    \ x) const { return mod_subtract({this->first + x, this->second + x}); }\n   \
    \ DoubleHash operator-(const DoubleHash &x) const {\n        return mod_subtract({this->first\
    \ + MODs.first - x.first, this->second + MODs.second - x.second});\n    }\n  \
    \  DoubleHash operator*(const DoubleHash &x) const {\n        return {unsigned(ull(this->first)\
    \ * x.first % MODs.first), unsigned(ull(this->second) * x.second % MODs.second)};\n\
    \    }\n    DoubleHash operator*(unsigned x) const {\n        return {unsigned(ull(this->first)\
    \ * x % MODs.first), unsigned(ull(this->second) * x % MODs.second)};\n    }\n\
    \    static DoubleHash gen_b(bool force_update = false) {\n        static DoubleHash\
    \ b{0, 0};\n        if (b == DoubleHash{0, 0} or force_update) {\n           \
    \ std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<unsigned> d(1 << 16, 1 << 29);\n  \
    \          b = {d(mt), d(mt)};\n        }\n        return b;\n    }\n};\nstd::pair<unsigned,\
    \ unsigned> DoubleHash::MODs{1000000007, 998244353};\n\n// Rolling Hash (Rabin-Karp),\
    \ 1dim\ntemplate <typename V = DoubleHash> struct rolling_hash {\n    int N;\n\
    \    const V B;\n    std::vector<V> hash;         // hash[i] = s[0] * B^(i - 1)\
    \ + ... + s[i - 1]\n    static std::vector<V> power; // power[i] = B^i\n    void\
    \ _extend_powvec() {\n        while (static_cast<int>(power.size()) <= N) {\n\
    \            auto tmp = power.back() * B;\n            power.push_back(tmp);\n\
    \        }\n    }\n    template <typename Int> rolling_hash(const std::vector<Int>\
    \ &s, V b = V::gen_b()) : N(s.size()), B(b), hash(N + 1) {\n        for (int i\
    \ = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];\n        _extend_powvec();\n\
    \    }\n    rolling_hash(const std::string &s = \"\", V b = V::gen_b()) : N(s.size()),\
    \ B(b), hash(N + 1) {\n        for (int i = 0; i < N; i++) hash[i + 1] = hash[i]\
    \ * B + s[i];\n        _extend_powvec();\n    }\n    void addchar(const char &c)\
    \ {\n        V hnew = hash[N] * B + c;\n        N++, hash.emplace_back(hnew);\n\
    \        _extend_powvec();\n    }\n    V get(int l, int r) const { // s[l] * B^(r\
    \ - l - 1) + ... + s[r - 1]\n        return hash[r] - hash[l] * power[r - l];\n\
    \    }\n    int lcplen(int l1, int l2) const {\n        return longest_common_prefix(*this,\
    \ l1, *this, l2);\n    }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{1};\n\
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
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n#line 3 \"string/test/run_enumerate_lyndon_hash.test.cpp\"\
    \n#include <iostream>\n#line 5 \"string/test/run_enumerate_lyndon_hash.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   string S;\n    cin >> S;\n    auto ret = run_enumerate<rolling_hash<DoubleHash>>(S);\n\
    \    cout << ret.size() << '\\n';\n    for (auto p : ret) cout << get<0>(p) <<\
    \ ' ' << get<1>(p) << ' ' << get<2>(p) << '\\n';\n}\n"
  code: "#include \"../lyndon_factorization.hpp\"\n#include \"../rolling_hash_1d.hpp\"\
    \n#include <iostream>\n#include <string>\n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    string S;\n    cin >> S;\n    auto ret = run_enumerate<rolling_hash<DoubleHash>>(S);\n\
    \    cout << ret.size() << '\\n';\n    for (auto p : ret) cout << get<0>(p) <<\
    \ ' ' << get<1>(p) << ' ' << get<2>(p) << '\\n';\n}\n"
  dependsOn:
  - string/lyndon_factorization.hpp
  - string/rolling_hash_1d.hpp
  isVerificationFile: true
  path: string/test/run_enumerate_lyndon_hash.test.cpp
  requiredBy: []
  timestamp: '2021-03-14 17:31:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/run_enumerate_lyndon_hash.test.cpp
layout: document
redirect_from:
- /verify/string/test/run_enumerate_lyndon_hash.test.cpp
- /verify/string/test/run_enumerate_lyndon_hash.test.cpp.html
title: string/test/run_enumerate_lyndon_hash.test.cpp
---
