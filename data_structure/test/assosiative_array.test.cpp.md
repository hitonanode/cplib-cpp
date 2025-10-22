---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: random/custom_hash.hpp
    title: "Custom hash functions \uFF08\u5404\u7A2E\u30C7\u30FC\u30BF\u69CB\u9020\
      \u306E\u305F\u3081\u306E\u30CF\u30C3\u30B7\u30E5\u95A2\u6570\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/associative_array
    links:
    - https://judge.yosupo.jp/problem/associative_array
  bundledCode: "#line 1 \"data_structure/test/assosiative_array.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n#line 2 \"random/custom_hash.hpp\"\
    \n#include <chrono>\n#include <cstdlib>\n#include <functional>\n\nstruct custom_hash\
    \ {\n    // https://codeforces.com/blog/entry/62393\n    static uint64_t splitmix64(uint64_t\
    \ x) {\n        // http://xorshift.di.unimi.it/splitmix64.c\n        x += 0x9e3779b97f4a7c15;\n\
    \        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n        x = (x ^ (x >> 27))\
    \ * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n    }\n\n    size_t operator()(uint64_t\
    \ x) const {\n        static const uint64_t FIXED_RANDOM =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + FIXED_RANDOM);\n    }\n};\n\n// Template of std::hash\
    \ for arbitrary structs\n// template <> struct std::hash<T> {\n//     std::size_t\
    \ operator()(const T &x) const noexcept {\n//         static custom_hash h;\n\
    //         return h(/* */);\n//     }\n// };\n\n// robust unordered_map\n// #include\
    \ <unordered_map>\n// std::unordered_map<int, int, custom_hash> robust_unordered_map;\n\
    \n// fast unordered_set / unordered_map\n// #include <ext/pb_ds/assoc_container.hpp>\n\
    // using namespace __gnu_pbds;\n// gp_hash_table<int, null_type, custom_hash>\
    \ fast_hash_table;\n#line 3 \"data_structure/test/assosiative_array.test.cpp\"\
    \n#include <iostream>\n\n#include <ext/pb_ds/assoc_container.hpp>\nusing namespace\
    \ __gnu_pbds;\n\nint main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \    // std::unordered_map<long long, long long, custom_hash> mp;\n    gp_hash_table<long\
    \ long, long long, custom_hash> mp;\n\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--) {\n        int q;\n        std::cin >> q;\n        if (q) {\n        \
    \    long long k;\n            std::cin >> k;\n            std::cout << mp[k]\
    \ << '\\n';\n        } else {\n            long long k, v;\n            std::cin\
    \ >> k >> v;\n            mp[k] = v;\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n#include\
    \ \"../../random/custom_hash.hpp\"\n#include <iostream>\n\n#include <ext/pb_ds/assoc_container.hpp>\n\
    using namespace __gnu_pbds;\n\nint main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \    // std::unordered_map<long long, long long, custom_hash> mp;\n    gp_hash_table<long\
    \ long, long long, custom_hash> mp;\n\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--) {\n        int q;\n        std::cin >> q;\n        if (q) {\n        \
    \    long long k;\n            std::cin >> k;\n            std::cout << mp[k]\
    \ << '\\n';\n        } else {\n            long long k, v;\n            std::cin\
    \ >> k >> v;\n            mp[k] = v;\n        }\n    }\n}\n"
  dependsOn:
  - random/custom_hash.hpp
  isVerificationFile: true
  path: data_structure/test/assosiative_array.test.cpp
  requiredBy: []
  timestamp: '2025-10-23 00:38:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/assosiative_array.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/assosiative_array.test.cpp
- /verify/data_structure/test/assosiative_array.test.cpp.html
title: data_structure/test/assosiative_array.test.cpp
---
