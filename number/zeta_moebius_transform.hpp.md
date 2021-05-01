---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://toph.co/p/height-of-the-trees
    - https://yukicoder.me/submissions/385043
    - https://yukicoder.me/submissions/385120
  bundledCode: "#line 2 \"number/sieve.hpp\"\n#include <cassert>\n#include <map>\n\
    #include <vector>\n\n// CUT begin\n// Linear sieve algorithm for fast prime factorization\n\
    // Complexity: O(N) time, O(N) space:\n// - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces\
    \ / AtCoder GCC, C++17)\n// - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder\
    \ GCC, C++17)\n// Reference:\n// [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm\
    \ for Finding Prime Numbers,\"\n//     Communications of the ACM, 21(12), 999-1003,\
    \ 1978.\n// - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n// -\
    \ https://37zigen.com/linear-sieve/\nstruct Sieve {\n    std::vector<int> min_factor;\n\
    \    std::vector<int> primes;\n    Sieve(int MAXN) : min_factor(MAXN + 1) {\n\
    \        for (int d = 2; d <= MAXN; d++) {\n            if (!min_factor[d]) {\n\
    \                min_factor[d] = d;\n                primes.emplace_back(d);\n\
    \            }\n            for (const auto &p : primes) {\n                if\
    \ (p > min_factor[d] or d * p > MAXN) break;\n                min_factor[d * p]\
    \ = p;\n            }\n        }\n    }\n    // Prime factorization for 1 <= x\
    \ <= MAXN^2\n    // Complexity: O(log x)           (x <= MAXN)\n    //       \
    \      O(MAXN / log MAXN) (MAXN < x <= MAXN^2)\n    template <typename T> std::map<T,\
    \ int> factorize(T x) {\n        std::map<T, int> ret;\n        assert(x > 0 and\
    \ x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size() - 1));\n\
    \        for (const auto &p : primes) {\n            if (x < T(min_factor.size()))\
    \ break;\n            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if\
    \ (x >= T(min_factor.size())) ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++,\
    \ x /= min_factor[x];\n        return ret;\n    }\n    // Enumerate divisors of\
    \ 1 <= x <= MAXN^2\n    // Be careful of highly composite numbers https://oeis.org/A002182/list\
    \ https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt\n    //\
    \ (n, (# of div. of n)): 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <typename T> std::vector<T> divisors(T x) {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Moebius function Table, (-1)^{#\
    \ of different prime factors} for square-free x\n    // return: [0=>0, 1=>1, 2=>-1,\
    \ 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...] https://oeis.org/A008683\n    std::vector<int>\
    \ GenerateMoebiusFunctionTable() {\n        std::vector<int> ret(min_factor.size());\n\
    \        for (unsigned i = 1; i < min_factor.size(); i++) {\n            if (i\
    \ == 1)\n                ret[i] = 1;\n            else if ((i / min_factor[i])\
    \ % min_factor[i] == 0)\n                ret[i] = 0;\n            else\n     \
    \           ret[i] = -ret[i / min_factor[i]];\n        }\n        return ret;\n\
    \    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    template <typename\
    \ MODINT> std::vector<MODINT> enumerate_kth_pows(long long K, int nmax) {\n  \
    \      assert(nmax < int(min_factor.size()));\n        std::vector<MODINT> ret(nmax\
    \ + 1);\n        ret[0] = 0, ret[1] = 1;\n        for (int n = 2; n <= nmax; n++)\
    \ {\n            if (min_factor[n] == n) {\n                ret[n] = MODINT(n).pow(K);\n\
    \            } else {\n                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n\
    \            }\n        }\n        return ret;\n    }\n};\n// Sieve sieve(1 <<\
    \ 15);  // (can factorize n <= 10^9)\n#line 3 \"number/zeta_moebius_transform.hpp\"\
    \n#include <algorithm>\n#line 5 \"number/zeta_moebius_transform.hpp\"\n#include\
    \ <utility>\n#line 7 \"number/zeta_moebius_transform.hpp\"\n\n// CUT begin\n//\
    \ f[n]\u306B\u5BFE\u3057\u3066\u3001\u5168\u3066\u306En\u306E\u500D\u6570n*i\u306B\
    \u5BFE\u3059\u308Bf[n*i]\u306E\u548C\u304C\u51FA\u3066\u304F\u308B \u8A08\u7B97\
    \u91CFO(NloglogN)\n// \u7D20\u6570p\u6BCE\u306B\u51E6\u7406\u3059\u308B\u9AD8\u901F\
    \u30BC\u30FC\u30BF\u5909\u63DB\n// \u4F7F\u7528\u4F8B https://yukicoder.me/submissions/385043\n\
    template <typename T> void fast_integer_zeta(std::vector<T> &f) {\n    int N =\
    \ f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p = 2;\
    \ p <= N; p++) {\n        if (is_prime[p]) {\n            for (int q = p * 2;\
    \ q <= N; q += p) is_prime[q] = 0;\n            for (int j = N / p * p; j > 0;\
    \ j -= p) f[j / p] += f[j];\n        }\n    }\n}\n\n// fast_integer_zeta\u306E\
    \u9006\u6F14\u7B97 O(NloglogN)\n// \u4F7F\u7528\u4F8B https://yukicoder.me/submissions/385120\n\
    template <typename T> void fast_integer_moebius(std::vector<T> &f) {\n    int\
    \ N = f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p\
    \ = 2; p <= N; p++) {\n        if (is_prime[p]) {\n            for (int q = p\
    \ * 2; q <= N; q += p) is_prime[q] = 0;\n            for (int j = p; j <= N; j\
    \ += p) f[j / p] -= f[j];\n        }\n    }\n}\n\n// fast_integer_moebius \u306E\
    \u9AD8\u901F\u5316\uFF08\u767B\u5834\u3057\u306A\u3044\u7D20\u56E0\u6570\u304C\
    \u591A\u3051\u308C\u3070\u8A08\u7B97\u91CF\u6539\u5584\uFF09\n// Requirement:\
    \ f \u306E key \u3068\u3057\u3066\u767B\u5834\u3059\u308B\u6B63\u6574\u6570\u306E\
    \u5168\u3066\u306E\u7D04\u6570\u304C key \u3068\u3057\u3066\u767B\u5834\n// Verified:\
    \ https://toph.co/p/height-of-the-trees\ntemplate <typename Int, typename Val>\n\
    void sparse_fast_integer_moebius(std::vector<std::pair<Int, Val>> &f, const Sieve\
    \ &sieve) {\n    if (f.empty()) return;\n    std::sort(f.begin(), f.end());\n\
    \    assert(f.back().first < Int(sieve.min_factor.size()));\n    std::vector<Int>\
    \ primes;\n    for (auto p : f) {\n        if (sieve.min_factor[p.first] == p.first)\
    \ primes.push_back(p.first);\n    }\n    std::vector<std::vector<int>> p2is(primes.size());\n\
    \    for (int i = 0; i < int(f.size()); i++) {\n        Int a = f[i].first, pold\
    \ = 0;\n        int k = 0;\n        while (a > 1) {\n            auto p = sieve.min_factor[a];\n\
    \            if (p != pold) {\n                while (primes[k] != p) k++;\n \
    \               p2is[k].emplace_back(i);\n            }\n            pold = p,\
    \ a /= p;\n        }\n    }\n    for (int d = 0; d < int(primes.size()); d++)\
    \ {\n        Int p = primes[d];\n        for (auto i : p2is[d]) {\n          \
    \  auto comp = [](const std::pair<Int, Val> &l, const std::pair<Int, Val> &r)\
    \ { return l.first < r.first; };\n            auto itr = std::lower_bound(f.begin(),\
    \ f.end(), std::make_pair(f[i].first / p, 0), comp);\n            itr->second\
    \ -= f[i].second;\n        }\n    }\n}\n"
  code: "#pragma once\n#include \"../number/sieve.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\n// CUT begin\n// f[n]\u306B\
    \u5BFE\u3057\u3066\u3001\u5168\u3066\u306En\u306E\u500D\u6570n*i\u306B\u5BFE\u3059\
    \u308Bf[n*i]\u306E\u548C\u304C\u51FA\u3066\u304F\u308B \u8A08\u7B97\u91CFO(NloglogN)\n\
    // \u7D20\u6570p\u6BCE\u306B\u51E6\u7406\u3059\u308B\u9AD8\u901F\u30BC\u30FC\u30BF\
    \u5909\u63DB\n// \u4F7F\u7528\u4F8B https://yukicoder.me/submissions/385043\n\
    template <typename T> void fast_integer_zeta(std::vector<T> &f) {\n    int N =\
    \ f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p = 2;\
    \ p <= N; p++) {\n        if (is_prime[p]) {\n            for (int q = p * 2;\
    \ q <= N; q += p) is_prime[q] = 0;\n            for (int j = N / p * p; j > 0;\
    \ j -= p) f[j / p] += f[j];\n        }\n    }\n}\n\n// fast_integer_zeta\u306E\
    \u9006\u6F14\u7B97 O(NloglogN)\n// \u4F7F\u7528\u4F8B https://yukicoder.me/submissions/385120\n\
    template <typename T> void fast_integer_moebius(std::vector<T> &f) {\n    int\
    \ N = f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p\
    \ = 2; p <= N; p++) {\n        if (is_prime[p]) {\n            for (int q = p\
    \ * 2; q <= N; q += p) is_prime[q] = 0;\n            for (int j = p; j <= N; j\
    \ += p) f[j / p] -= f[j];\n        }\n    }\n}\n\n// fast_integer_moebius \u306E\
    \u9AD8\u901F\u5316\uFF08\u767B\u5834\u3057\u306A\u3044\u7D20\u56E0\u6570\u304C\
    \u591A\u3051\u308C\u3070\u8A08\u7B97\u91CF\u6539\u5584\uFF09\n// Requirement:\
    \ f \u306E key \u3068\u3057\u3066\u767B\u5834\u3059\u308B\u6B63\u6574\u6570\u306E\
    \u5168\u3066\u306E\u7D04\u6570\u304C key \u3068\u3057\u3066\u767B\u5834\n// Verified:\
    \ https://toph.co/p/height-of-the-trees\ntemplate <typename Int, typename Val>\n\
    void sparse_fast_integer_moebius(std::vector<std::pair<Int, Val>> &f, const Sieve\
    \ &sieve) {\n    if (f.empty()) return;\n    std::sort(f.begin(), f.end());\n\
    \    assert(f.back().first < Int(sieve.min_factor.size()));\n    std::vector<Int>\
    \ primes;\n    for (auto p : f) {\n        if (sieve.min_factor[p.first] == p.first)\
    \ primes.push_back(p.first);\n    }\n    std::vector<std::vector<int>> p2is(primes.size());\n\
    \    for (int i = 0; i < int(f.size()); i++) {\n        Int a = f[i].first, pold\
    \ = 0;\n        int k = 0;\n        while (a > 1) {\n            auto p = sieve.min_factor[a];\n\
    \            if (p != pold) {\n                while (primes[k] != p) k++;\n \
    \               p2is[k].emplace_back(i);\n            }\n            pold = p,\
    \ a /= p;\n        }\n    }\n    for (int d = 0; d < int(primes.size()); d++)\
    \ {\n        Int p = primes[d];\n        for (auto i : p2is[d]) {\n          \
    \  auto comp = [](const std::pair<Int, Val> &l, const std::pair<Int, Val> &r)\
    \ { return l.first < r.first; };\n            auto itr = std::lower_bound(f.begin(),\
    \ f.end(), std::make_pair(f[i].first / p, 0), comp);\n            itr->second\
    \ -= f[i].second;\n        }\n    }\n}\n"
  dependsOn:
  - number/sieve.hpp
  isVerificationFile: false
  path: number/zeta_moebius_transform.hpp
  requiredBy: []
  timestamp: '2021-05-01 20:55:29+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/zeta_moebius_transform.hpp
layout: document
redirect_from:
- /library/number/zeta_moebius_transform.hpp
- /library/number/zeta_moebius_transform.hpp.html
title: number/zeta_moebius_transform.hpp
---
