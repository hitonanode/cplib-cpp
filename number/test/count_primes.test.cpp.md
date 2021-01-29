---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/count_primes.hpp
    title: number/count_primes.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/counting_primes
    links:
    - https://judge.yosupo.jp/problem/counting_primes
  bundledCode: "#line 1 \"number/test/count_primes.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/counting_primes\"\n#line 2 \"number/count_primes.hpp\"\
    \n#include <algorithm>\n#include <cmath>\n#include <vector>\n\n// CUT begin\n\
    struct CountPrimes {\n    // Count Primes less than or equal to x (\\pi(x)) for\
    \ each x = N / i (i = 1, ..., N) in O(N^(2/3)) time\n    // Learned this algorihtm\
    \ from <https://old.yosupo.jp/submission/14650>\n    // Reference: <https://min-25.hatenablog.com/entry/2018/11/11/172216>\n\
    \    using Int = long long;\n    Int n, n2, n3, n6;\n    std::vector<int> is_prime;\
    \ // [0, 0, 1, 1, 0, 1, 0, 1, ...]\n    std::vector<Int> primes;   // primes up\
    \ to O(N^(1/2)), [2, 3, 5, 7, ...]\n\n    int s;               // size of vs\n\
    \    std::vector<Int> vs; // [N, ..., n2, n2 - 1, n2 - 2, ..., 3, 2, 1]\n    std::vector<Int>\
    \ pi; // pi[i] = (# of primes s.t. <= vs[i]) is finally obtained\n\n    std::vector<int>\
    \ _fenwick;\n\n    int getidx(Int a) const { return a <= n2 ? s - a : n / a -\
    \ 1; } // vs[i] >= a \u3092\u6E80\u305F\u3059\u6700\u5927\u306E i \u3092\u8FD4\
    \u3059\n\n    void _fenwick_rec_update(int i, Int cur, bool first) { // pi[n3:]\
    \ \u306B\u5BFE\u3057\u3066 cur * (primes[i] \u4EE5\u4E0A\u306E\u7D20\u56E0\u6570\
    ) \u306E\u6570\u306E\u5BC4\u4E0E\u3092\u6E1B\u3058\u308B\n        if (!first)\
    \ {\n            for (int x = getidx(cur) - n3; x >= 0; x -= (x + 1) & (-x - 1))\
    \ _fenwick[x]--;\n        }\n        for (int j = i; cur * primes[j] <= vs[n3];\
    \ j++) _fenwick_rec_update(j, cur * primes[j], false);\n    }\n\n    CountPrimes(Int\
    \ n_) : n(n_), n2((Int)sqrtl(n)), n3((Int)cbrtl(n)), n6((Int)sqrtl(n3)) {\n  \
    \      is_prime.assign(n2 + 300, 1), is_prime[0] = is_prime[1] = 0; // `+ 300`:\
    \ <https://en.wikipedia.org/wiki/Prime_gap>\n        for (size_t p = 2; p < is_prime.size();\
    \ p++) {\n            if (is_prime[p]) {\n                primes.push_back(p);\n\
    \                for (size_t j = p * 2; j < is_prime.size(); j += p) is_prime[j]\
    \ = 0;\n            }\n        }\n        for (Int now = n; now; now = n / (n\
    \ / now + 1))\n            vs.push_back(now); // [N, N / 2, ..., 1], Relevant\
    \ integers (decreasing) length ~= 2sqrt(N)\n        s = vs.size();\n\n       \
    \ // pi[i] = (# of integers x s.t. x <= vs[i],  (x is prime or all factors of\
    \ x >= p))\n        // pre = (# of primes less than p)\n        // \u6700\u5C0F\
    \u306E\u7D20\u56E0\u6570 p = 2, ..., \u306B\u3064\u3044\u3066\u7BE9\u3063\u3066\
    \u3044\u304F\n        pi.resize(s);\n        for (int i = 0; i < s; i++) pi[i]\
    \ = vs[i] - 1;\n        int pre = 0;\n\n        auto trans = [&](int i, Int p)\
    \ { pi[i] -= pi[getidx(vs[i] / p)] - pre; };\n\n        size_t ip = 0;\n\n   \
    \     // [Sieve Part 1] For each prime p satisfying p <= N^(1/6) (Only O(N^(1/6)\
    \ / log N) such primes exist),\n        //                O(sqrt(N)) simple operation\
    \ is conducted.\n        // - Complexity of this part: O(N^(2/3) / logN)\n   \
    \     for (; primes[ip] <= n6; ip++, pre++) {\n            const auto &p = primes[ip];\n\
    \            for (int i = 0; p * p <= vs[i]; i++) trans(i, p);\n        }\n\n\
    \        // [Sieve Part 2] For each prime p satisfying N^(1/6) < p <= N^(1/3),\n\
    \        //                point-wise & Fenwick tree-based hybrid update is used\n\
    \        // - first N^(1/3) elements are simply updated by quadratic algorithm.\n\
    \        // - Updates of latter segments are managed by Fenwick tree.\n      \
    \  // - Complexity of this part: O(N^(2/3)) (O(N^(2/3)/log N) operations for Fenwick\
    \ tree (O(logN) per query))\n        _fenwick.assign(s - n3, 0); // Fenwick tree,\
    \ inversed order (summation for upper region)\n        auto trans2 = [&](int i,\
    \ Int p) {\n            int j = getidx(vs[i] / p);\n            auto z = pi[j];\n\
    \            if (j >= n3) {\n                for (j -= n3; j < int(_fenwick.size());\
    \ j += (j + 1) & (-j - 1)) z += _fenwick[j];\n            }\n            pi[i]\
    \ -= z - pre;\n        };\n        for (; primes[ip] <= n3; ip++, pre++) {\n \
    \           const auto &p = primes[ip];\n            for (int i = 0; i < n3 and\
    \ p * p <= vs[i]; i++)\n                trans2(i, p);                        \
    \  // upto n3, total trans2 times: O(N^(2/3) / logN)\n            _fenwick_rec_update(ip,\
    \ primes[ip], true); // total update times: O(N^(2/3) / logN)\n        }\n   \
    \     for (int i = s - n3 - 1; i >= 0; i--) {\n            int j = i + ((i + 1)\
    \ & (-i - 1));\n            if (j < s - n3) _fenwick[i] += _fenwick[j];\n    \
    \    }\n        for (int i = 0; i < s - n3; i++) pi[i + n3] += _fenwick[i];\n\n\
    \        // [Sieve Part 3] For each prime p satisfying N^(1/3) < p <= N^(1/2),\
    \ use only simple updates.\n        // - Complexity of this part: O(N^(2/3) /\
    \ logN)\n        //     \\sum_i (# of factors of vs[i] of the form p^2, p >= N^(1/3))\
    \ = \\sum_{i=1}^{N^(1/3)} \\pi(\\sqrt(vs[i])))\n        //                   \
    \                                               = sqrt(N) \\sum_i^{N^(1/3)} i^{-1/2}\
    \ / logN = O(N^(2/3) / logN)\n        //     (Note: \\sum_{i=1}^{N} i^{-1/2} =\
    \ O(sqrt N) <https://math.stackexchange.com/questions/2600796/finding-summation-of-inverse-of-square-roots>)\n\
    \        for (; primes[ip] <= n2; ip++, pre++) {\n            const auto &p =\
    \ primes[ip];\n            for (int i = 0; p * p <= vs[i]; i++) trans(i, p);\n\
    \        }\n    }\n};\n#line 3 \"number/test/count_primes.test.cpp\"\n#include\
    \ <iostream>\n\nint main() {\n    long long N;\n    std::cout << CountPrimes((std::cin\
    \ >> N, N)).pi[0] << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/counting_primes\"\n#include\
    \ \"../count_primes.hpp\"\n#include <iostream>\n\nint main() {\n    long long\
    \ N;\n    std::cout << CountPrimes((std::cin >> N, N)).pi[0] << '\\n';\n}\n"
  dependsOn:
  - number/count_primes.hpp
  isVerificationFile: true
  path: number/test/count_primes.test.cpp
  requiredBy: []
  timestamp: '2021-01-12 01:46:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/count_primes.test.cpp
layout: document
redirect_from:
- /verify/number/test/count_primes.test.cpp
- /verify/number/test/count_primes.test.cpp.html
title: number/test/count_primes.test.cpp
---
