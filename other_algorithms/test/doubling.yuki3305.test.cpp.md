---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/doubling.hpp
    title: "Binary lifting / doubling \uFF08\u30C0\u30D6\u30EA\u30F3\u30B0\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/3305
    links:
    - https://yukicoder.me/problems/no/3305
  bundledCode: "#line 1 \"other_algorithms/test/doubling.yuki3305.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/3305\"\n#line 2 \"other_algorithms/doubling.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// Binary lifting / `Doubling`\n//\
    \ Complexity: O(NlogN) precalculation / O(logN) per query\n// https://atcoder.jp/contests/arc060/submissions/7039451\n\
    struct BinaryLifting {\n    int N, lgD;\n\n    bool is_valid(int idx) const {\
    \ return 0 <= idx and idx < N; }\n\n    std::vector<std::vector<int>> mat;\n \
    \   BinaryLifting() : N(0), lgD(0) {}\n    BinaryLifting(const std::vector<int>\
    \ &to, int lgd = 0) : N(to.size()), lgD(lgd) {\n        while ((1LL << lgD) <\
    \ N) lgD++;\n        mat.assign(lgD, std::vector<int>(N));\n        mat[0] = to;\n\
    \n        for (int d = 0; d < lgD - 1; d++) {\n            for (int i = 0; i <\
    \ N; i++) {\n                mat[d + 1][i] = mat[d][is_valid(mat[d][i]) ? mat[d][i]\
    \ : i];\n            }\n        }\n    }\n\n    int kth_next(int now, long long\
    \ k) const {\n        assert(k >= 0);\n        assert(k < (1LL << lgD));\n   \
    \     for (int d = 0; k and is_valid(now); d++, k >>= 1) {\n            if (k\
    \ & 1) now = mat[d][now];\n        }\n        return now;\n    }\n\n    // Distance\
    \ from l to [r, \\infty)\n    // Requirement: mat[0][i] >= r (i = r, r + 1, ...)\
    \ (monotone)\n    int distance(int l, int r) const {\n        if (l >= r) return\
    \ 0;\n        int ret = 0;\n        for (int d = lgD - 1; d >= 0; d--) {\n   \
    \         if (mat[d][l] < r and is_valid(mat[d][l])) ret += 1 << d, l = mat[d][l];\n\
    \        }\n\n        if (!is_valid(mat[0][l]) or mat[0][l] >= r) {\n        \
    \    return ret + 1;\n        } else {\n            return -1; // Unable to reach\n\
    \        }\n    }\n};\n#line 3 \"other_algorithms/test/doubling.yuki3305.test.cpp\"\
    \n\n#include <iostream>\n#include <utility>\n#line 7 \"other_algorithms/test/doubling.yuki3305.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    cin >> N >> Q;\n    vector<int> A(N);\n    for (auto &a :\
    \ A) cin >> a;\n\n    vector<int> nexts(N, N);\n\n    vector<pair<int, int>> st;\n\
    \    st.emplace_back(N, N);\n    for (int i = N - 1; i >= 0; --i) {\n        while\
    \ (st.back().first < A.at(i)) st.pop_back();\n        nexts.at(i) = st.back().second;\n\
    \        st.emplace_back(A.at(i), i);\n    }\n\n    const BinaryLifting binary_lifting(nexts);\n\
    \n    while (Q--) {\n        int l, r;\n        cin >> l >> r;\n        --l;\n\
    \        cout << r - l - binary_lifting.distance(l, r) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/3305\"\n#include \"../doubling.hpp\"\
    \n\n#include <iostream>\n#include <utility>\n#include <vector>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    int N, Q;\n    cin >> N >> Q;\n    vector<int> A(N);\n    for (auto &a :\
    \ A) cin >> a;\n\n    vector<int> nexts(N, N);\n\n    vector<pair<int, int>> st;\n\
    \    st.emplace_back(N, N);\n    for (int i = N - 1; i >= 0; --i) {\n        while\
    \ (st.back().first < A.at(i)) st.pop_back();\n        nexts.at(i) = st.back().second;\n\
    \        st.emplace_back(A.at(i), i);\n    }\n\n    const BinaryLifting binary_lifting(nexts);\n\
    \n    while (Q--) {\n        int l, r;\n        cin >> l >> r;\n        --l;\n\
    \        cout << r - l - binary_lifting.distance(l, r) << '\\n';\n    }\n}\n"
  dependsOn:
  - other_algorithms/doubling.hpp
  isVerificationFile: true
  path: other_algorithms/test/doubling.yuki3305.test.cpp
  requiredBy: []
  timestamp: '2025-10-07 09:40:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/doubling.yuki3305.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/doubling.yuki3305.test.cpp
- /verify/other_algorithms/test/doubling.yuki3305.test.cpp.html
title: other_algorithms/test/doubling.yuki3305.test.cpp
---
