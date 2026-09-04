---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/fast_hash_map.hpp
    title: Fast hash map
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
  bundledCode: "#line 1 \"data_structure/test/fast_hash_map.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/associative_array\"\n#line 2 \"data_structure/fast_hash_map.hpp\"\
    \n\n#include <array>\n#include <bit>\n#include <cassert>\n#include <chrono>\n\
    #include <cstddef>\n#include <cstdint>\n#include <random>\n#include <type_traits>\n\
    \n// Fixed-capacity hash map for integer keys.\n// N must be a power of two. At\
    \ most N distinct keys can be stored.\ntemplate <typename K, typename V, std::size_t\
    \ N> struct HashMap {\n    static_assert(std::has_single_bit(N));\n    static_assert(std::is_integral_v<K>);\n\
    \    static_assert(sizeof(K) <= sizeof(std::uint64_t));\n\nprivate:\n    std::array<K,\
    \ N> keys;\n    std::array<V, N> values;\n    std::array<std::uint32_t, N> versions{};\n\
    \n    std::uint32_t version = 1;\n    std::size_t count = 0;\n    std::uint64_t\
    \ multiplier;\n\n    static std::uint64_t make_multiplier() noexcept {\n     \
    \   // Use a nondeterministic seed\n        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \        return mt() | 1;\n    }\n\n    std::size_t hash(K key) const noexcept\
    \ {\n        if constexpr (N == 1) {\n            return 0;\n        } else {\n\
    \            constexpr int shift = 64 - std::countr_zero(N);\n            return\
    \ (static_cast<std::uint64_t>(key) * multiplier) >> shift;\n        }\n    }\n\
    \npublic:\n    HashMap() : multiplier(make_multiplier()) {}\n\n    void set(K\
    \ key, V value) noexcept {\n        std::size_t pos = hash(key);\n        for\
    \ (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos] !=\
    \ version) {\n                keys[pos] = key;\n                values[pos] =\
    \ value;\n                versions[pos] = version;\n                assert(count\
    \ < N);\n                ++count;\n                return;\n            }\n  \
    \          if (keys[pos] == key) {\n                values[pos] = value;\n   \
    \             return;\n            }\n            pos = (pos + 1) & (N - 1);\n\
    \        }\n        assert(false && \"HashMap capacity exceeded\");\n    }\n\n\
    \    V get(K key) const noexcept {\n        std::size_t pos = hash(key);\n   \
    \     for (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos]\
    \ != version) return V{};\n            if (keys[pos] == key) return values[pos];\n\
    \            pos = (pos + 1) & (N - 1);\n        }\n        return V{};\n    }\n\
    \n    std::size_t size() const noexcept { return count; }\n    bool empty() const\
    \ noexcept { return count == 0; }\n\n    void clear() noexcept {\n        ++version;\n\
    \        count = 0;\n    }\n    void reset() noexcept { clear(); }\n};\n#line\
    \ 4 \"data_structure/test/fast_hash_map.test.cpp\"\n#include <iostream>\n\nHashMap<unsigned\
    \ long long, unsigned long long, 1 << 21> mp;\n\nint main() {\n    std::cin.tie(nullptr),\
    \ std::ios::sync_with_stdio(false);\n\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--) {\n        int type;\n        unsigned long long key;\n        std::cin\
    \ >> type >> key;\n        if (type == 0) {\n            unsigned long long value;\n\
    \            std::cin >> value;\n            mp.set(key, value);\n        } else\
    \ {\n            std::cout << mp.get(key) << '\\n';\n        }\n    }\n\n    mp.clear();\n\
    \    assert(mp.empty());\n    assert(mp.size() == 0);\n    assert(mp.get(1) ==\
    \ 0);\n\n    mp.set(1, 2);\n    mp.set(1, 3);\n    assert(mp.size() == 1);\n \
    \   assert(mp.get(1) == 3);\n\n    mp.reset();\n    assert(mp.empty());\n    assert(mp.get(1)\
    \ == 0);\n\n    HashMap<int, int, 1> one;\n    assert(one.get(-1) == 0);\n   \
    \ one.set(-1, 4);\n    assert(one.size() == 1);\n    assert(one.get(-1) == 4);\n\
    \    assert(one.get(0) == 0);\n    one.clear();\n    one.set(0, 5);\n    assert(one.get(0)\
    \ == 5);\n\n    HashMap<int, int, 8> full;\n    for (int i = 0; i < 8; ++i) full.set(i,\
    \ i + 1);\n    assert(full.size() == 8);\n    for (int i = 0; i < 8; ++i) assert(full.get(i)\
    \ == i + 1);\n    assert(full.get(8) == 0);\n    full.clear();\n    full.set(8,\
    \ 9);\n    assert(full.size() == 1);\n    assert(full.get(8) == 9);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n#include\
    \ \"../fast_hash_map.hpp\"\n#include <cassert>\n#include <iostream>\n\nHashMap<unsigned\
    \ long long, unsigned long long, 1 << 21> mp;\n\nint main() {\n    std::cin.tie(nullptr),\
    \ std::ios::sync_with_stdio(false);\n\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--) {\n        int type;\n        unsigned long long key;\n        std::cin\
    \ >> type >> key;\n        if (type == 0) {\n            unsigned long long value;\n\
    \            std::cin >> value;\n            mp.set(key, value);\n        } else\
    \ {\n            std::cout << mp.get(key) << '\\n';\n        }\n    }\n\n    mp.clear();\n\
    \    assert(mp.empty());\n    assert(mp.size() == 0);\n    assert(mp.get(1) ==\
    \ 0);\n\n    mp.set(1, 2);\n    mp.set(1, 3);\n    assert(mp.size() == 1);\n \
    \   assert(mp.get(1) == 3);\n\n    mp.reset();\n    assert(mp.empty());\n    assert(mp.get(1)\
    \ == 0);\n\n    HashMap<int, int, 1> one;\n    assert(one.get(-1) == 0);\n   \
    \ one.set(-1, 4);\n    assert(one.size() == 1);\n    assert(one.get(-1) == 4);\n\
    \    assert(one.get(0) == 0);\n    one.clear();\n    one.set(0, 5);\n    assert(one.get(0)\
    \ == 5);\n\n    HashMap<int, int, 8> full;\n    for (int i = 0; i < 8; ++i) full.set(i,\
    \ i + 1);\n    assert(full.size() == 8);\n    for (int i = 0; i < 8; ++i) assert(full.get(i)\
    \ == i + 1);\n    assert(full.get(8) == 0);\n    full.clear();\n    full.set(8,\
    \ 9);\n    assert(full.size() == 1);\n    assert(full.get(8) == 9);\n}\n"
  dependsOn:
  - data_structure/fast_hash_map.hpp
  isVerificationFile: true
  path: data_structure/test/fast_hash_map.test.cpp
  requiredBy: []
  timestamp: '2026-09-05 01:34:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/fast_hash_map.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/fast_hash_map.test.cpp
- /verify/data_structure/test/fast_hash_map.test.cpp.html
title: data_structure/test/fast_hash_map.test.cpp
---
