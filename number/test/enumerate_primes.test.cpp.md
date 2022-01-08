---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_primes
    links:
    - https://judge.yosupo.jp/problem/enumerate_primes
  bundledCode: "#line 1 \"number/test/enumerate_primes.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/enumerate_primes\"\n#line 2 \"number/sieve.hpp\"\
    \n#include <cassert>\n#include <map>\n#include <vector>\n\n// CUT begin\n// Linear\
    \ sieve algorithm for fast prime factorization\n// Complexity: O(N) time, O(N)\
    \ space:\n// - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces / AtCoder GCC, C++17)\n\
    // - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder GCC, C++17)\n// Reference:\n\
    // [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm for Finding Prime Numbers,\"\
    \n//     Communications of the ACM, 21(12), 999-1003, 1978.\n// - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n\
    // - https://37zigen.com/linear-sieve/\nstruct Sieve {\n    std::vector<int> min_factor;\n\
    \    std::vector<int> primes;\n    Sieve(int MAXN) : min_factor(MAXN + 1) {\n\
    \        for (int d = 2; d <= MAXN; d++) {\n            if (!min_factor[d]) {\n\
    \                min_factor[d] = d;\n                primes.emplace_back(d);\n\
    \            }\n            for (const auto &p : primes) {\n                if\
    \ (p > min_factor[d] or d * p > MAXN) break;\n                min_factor[d * p]\
    \ = p;\n            }\n        }\n    }\n    // Prime factorization for 1 <= x\
    \ <= MAXN^2\n    // Complexity: O(log x)           (x <= MAXN)\n    //       \
    \      O(MAXN / log MAXN) (MAXN < x <= MAXN^2)\n    template <class T> std::map<T,\
    \ int> factorize(T x) const {\n        std::map<T, int> ret;\n        assert(x\
    \ > 0 and\n               x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size()\
    \ - 1));\n        for (const auto &p : primes) {\n            if (x < T(min_factor.size()))\
    \ break;\n            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if\
    \ (x >= T(min_factor.size())) ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++,\
    \ x /= min_factor[x];\n        return ret;\n    }\n    // Enumerate divisors of\
    \ 1 <= x <= MAXN^2\n    // Be careful of highly composite numbers https://oeis.org/A002182/list\n\
    \    // https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt (n,\
    \ (# of div. of n)):\n    // 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <class T> std::vector<T> divisors(T x) const {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Euler phi functions of divisors\
    \ of given x\n    // Verified: ABC212 G https://atcoder.jp/contests/abc212/tasks/abc212_g\n\
    \    // Complexity: O(sqrt(x) + d(x))\n    template <class T> std::map<T, T> euler_of_divisors(T\
    \ x) const {\n        assert(x >= 1);\n        std::map<T, T> ret;\n        ret[1]\
    \ = 1;\n        std::vector<T> divs{1};\n        for (auto p : factorize(x)) {\n\
    \            int n = ret.size();\n            for (int i = 0; i < n; i++) {\n\
    \                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);\n    \
    \            divs.push_back(divs[i] * p.first);\n                for (T a = divs[i]\
    \ * p.first, d = 1; d < p.second; a *= p.first, d++) {\n                    ret[a\
    \ * p.first] = ret[a] * p.first;\n                    divs.push_back(a * p.first);\n\
    \                }\n            }\n        }\n        return ret;\n    }\n   \
    \ // Moebius function Table, (-1)^{# of different prime factors} for square-free\
    \ x\n    // return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0,\
    \ ...] https://oeis.org/A008683\n    std::vector<int> GenerateMoebiusFunctionTable()\
    \ const {\n        std::vector<int> ret(min_factor.size());\n        for (unsigned\
    \ i = 1; i < min_factor.size(); i++) {\n            if (i == 1) {\n          \
    \      ret[i] = 1;\n            } else if ((i / min_factor[i]) % min_factor[i]\
    \ == 0) {\n                ret[i] = 0;\n            } else {\n               \
    \ ret[i] = -ret[i / min_factor[i]];\n            }\n        }\n        return\
    \ ret;\n    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    // Note:\
    \ **0^0 == 1**\n    template <class MODINT> std::vector<MODINT> enumerate_kth_pows(long\
    \ long K, int nmax) const {\n        assert(nmax < int(min_factor.size()));\n\
    \        assert(K >= 0);\n        if (K == 0) return std::vector<MODINT>(nmax\
    \ + 1, 1);\n        std::vector<MODINT> ret(nmax + 1);\n        ret[0] = 0, ret[1]\
    \ = 1;\n        for (int n = 2; n <= nmax; n++) {\n            if (min_factor[n]\
    \ == n) {\n                ret[n] = MODINT(n).pow(K);\n            } else {\n\
    \                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n     \
    \       }\n        }\n        return ret;\n    }\n};\n// Sieve sieve((1 << 20));\n\
    #line 3 \"number/test/enumerate_primes.test.cpp\"\n#include <iostream>\n#line\
    \ 5 \"number/test/enumerate_primes.test.cpp\"\nusing namespace std;\n\nint main()\
    \ {\n    int N, A, B;\n    cin >> N >> A >> B;\n    Sieve sieve(N);\n    vector<int>\
    \ ret;\n    for (unsigned i = 0; A * i + B < sieve.primes.size(); i++)\n     \
    \   ret.push_back(sieve.primes[A * i + B]);\n    cout << sieve.primes.size() <<\
    \ ' ' << ret.size() << '\\n';\n    for (auto p : ret) cout << p << ' ';\n    cout\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\n#include\
    \ \"../sieve.hpp\"\n#include <iostream>\n#include <vector>\nusing namespace std;\n\
    \nint main() {\n    int N, A, B;\n    cin >> N >> A >> B;\n    Sieve sieve(N);\n\
    \    vector<int> ret;\n    for (unsigned i = 0; A * i + B < sieve.primes.size();\
    \ i++)\n        ret.push_back(sieve.primes[A * i + B]);\n    cout << sieve.primes.size()\
    \ << ' ' << ret.size() << '\\n';\n    for (auto p : ret) cout << p << ' ';\n \
    \   cout << '\\n';\n}\n"
  dependsOn:
  - number/sieve.hpp
  isVerificationFile: true
  path: number/test/enumerate_primes.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: number/test/enumerate_primes.test.cpp
layout: document
redirect_from:
- /verify/number/test/enumerate_primes.test.cpp
- /verify/number/test/enumerate_primes.test.cpp.html
title: number/test/enumerate_primes.test.cpp
---
