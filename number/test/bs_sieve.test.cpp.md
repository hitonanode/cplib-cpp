---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: number/bs_sieve.hpp
    title: number/bs_sieve.hpp
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
  bundledCode: "#line 1 \"number/test/bs_sieve.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\
    \n#line 2 \"number/bs_sieve.hpp\"\n#include <algorithm>\n#include <bitset>\n#include\
    \ <cassert>\n#include <vector>\n\n// CUT begin\n// Complexity: O(N log log N):\n\
    // - N = 10^7:  8 /  6 MB,   62 /  81 ms (Codeforces / AtCoder, GCC C++17)\n//\
    \ - N = 10^8: 61 / 44 MB, 1481 / 866 ms (Codeforces / AtCoder, GCC C++17)\ntemplate\
    \ <int LIMN> struct BitsetSieve {\n    std::vector<int> primes;\n    std::bitset<LIMN\
    \ + 1> is_prime;\n    const int maxN;\n    BitsetSieve(int MAXN = LIMN) : maxN(MAXN)\
    \ {\n        is_prime.set();\n        is_prime.reset(0), is_prime.reset(1);\n\
    \        for (int p = 2; p <= MAXN; p++) {\n            if (is_prime[p]) {\n \
    \               primes.push_back(p);\n                for (int j = p * 2; j <=\
    \ MAXN; j += p) is_prime[j] = 0;\n            }\n        }\n    }\n    // Count\
    \ primes less than or equal to x\n    int prime_counting(int x) {\n        assert(x\
    \ <= maxN);\n        return std::distance(primes.begin(), std::upper_bound(primes.begin(),\
    \ primes.end(), x));\n    }\n};\n#line 3 \"number/test/bs_sieve.test.cpp\"\n#include\
    \ <iostream>\n#line 5 \"number/test/bs_sieve.test.cpp\"\nusing namespace std;\n\
    \nint main() {\n    int N, A, B;\n    cin >> N >> A >> B;\n    BitsetSieve<500000001>\
    \ sieve(N);\n    vector<int> ret;\n    for (unsigned i = 0; A * i + B < sieve.primes.size();\
    \ i++)\n        ret.push_back(sieve.primes[A * i + B]);\n    cout << sieve.primes.size()\
    \ << ' ' << ret.size() << '\\n';\n    for (auto p : ret) cout << p << ' ';\n \
    \   cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\n#include\
    \ \"../bs_sieve.hpp\"\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\n\nint main() {\n    int N, A, B;\n    cin >> N >> A >> B;\n    BitsetSieve<500000001>\
    \ sieve(N);\n    vector<int> ret;\n    for (unsigned i = 0; A * i + B < sieve.primes.size();\
    \ i++)\n        ret.push_back(sieve.primes[A * i + B]);\n    cout << sieve.primes.size()\
    \ << ' ' << ret.size() << '\\n';\n    for (auto p : ret) cout << p << ' ';\n \
    \   cout << '\\n';\n}\n"
  dependsOn:
  - number/bs_sieve.hpp
  isVerificationFile: true
  path: number/test/bs_sieve.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: number/test/bs_sieve.test.cpp
layout: document
redirect_from:
- /verify/number/test/bs_sieve.test.cpp
- /verify/number/test/bs_sieve.test.cpp.html
title: number/test/bs_sieve.test.cpp
---
