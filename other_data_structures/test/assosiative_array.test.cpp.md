---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/associative_array
    links:
    - http://xorshift.di.unimi.it/splitmix64.c
    - https://codeforces.com/blog/entry/62393>
    - https://judge.yosupo.jp/problem/associative_array
  bundledCode: "#line 1 \"other_data_structures/test/assosiative_array.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n#include\
    \ <iostream>\n#include <unordered_map>\n\n#include <chrono>\nstruct custom_hash\n\
    {\n    // <https://codeforces.com/blog/entry/62393>\n    static uint64_t splitmix64(uint64_t\
    \ x)\n    {\n        // http://xorshift.di.unimi.it/splitmix64.c\n        x +=\
    \ 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n   \
    \     x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n\n    size_t operator()(uint64_t x) const\n    {\n        static const\
    \ uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + FIXED_RANDOM);\n    }\n};\n#include <ext/pb_ds/assoc_container.hpp>\n\
    using namespace __gnu_pbds;\n\nint main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \    // std::unordered_map<long long, long long, custom_hash> mp;\n    gp_hash_table<long\
    \ long, long long, custom_hash> mp;\n\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--)\n    {\n        int q;\n        std::cin >> q;\n        if (q)\n     \
    \   {\n            long long k;\n            std::cin >> k;\n            std::cout\
    \ << mp[k] << '\\n';\n        }\n        else\n        {\n            long long\
    \ k, v;\n            std::cin >> k >> v;\n            mp[k] = v;\n        }\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n#include\
    \ <iostream>\n#include <unordered_map>\n\n#include <chrono>\nstruct custom_hash\n\
    {\n    // <https://codeforces.com/blog/entry/62393>\n    static uint64_t splitmix64(uint64_t\
    \ x)\n    {\n        // http://xorshift.di.unimi.it/splitmix64.c\n        x +=\
    \ 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n   \
    \     x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n\n    size_t operator()(uint64_t x) const\n    {\n        static const\
    \ uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + FIXED_RANDOM);\n    }\n};\n#include <ext/pb_ds/assoc_container.hpp>\n\
    using namespace __gnu_pbds;\n\nint main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \    // std::unordered_map<long long, long long, custom_hash> mp;\n    gp_hash_table<long\
    \ long, long long, custom_hash> mp;\n\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--)\n    {\n        int q;\n        std::cin >> q;\n        if (q)\n     \
    \   {\n            long long k;\n            std::cin >> k;\n            std::cout\
    \ << mp[k] << '\\n';\n        }\n        else\n        {\n            long long\
    \ k, v;\n            std::cin >> k >> v;\n            mp[k] = v;\n        }\n\
    \    }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: other_data_structures/test/assosiative_array.test.cpp
  requiredBy: []
  timestamp: '2020-09-29 03:12:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_data_structures/test/assosiative_array.test.cpp
layout: document
redirect_from:
- /verify/other_data_structures/test/assosiative_array.test.cpp
- /verify/other_data_structures/test/assosiative_array.test.cpp.html
title: other_data_structures/test/assosiative_array.test.cpp
---
