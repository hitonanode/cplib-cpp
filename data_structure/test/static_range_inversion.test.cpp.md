---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/static_range_inversion.hpp
    title: data_structure/static_range_inversion.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 2 \"data_structure/static_range_inversion.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// Static Range Inversion Query (Online)\n// Complexity: O((N +\
    \ Q)sqrt(N)) time, O(Nsqrt(N)) space (~128MB for N=1e5)\n// Reference: <https://stackoverflow.com/questions/21763392/counting-inversions-in-ranges>\n\
    template <typename T> struct StaticRangeInversion {\n    const int N;\n    const\
    \ int bs;    // bucket size\n    const int nb_bc; // # of buckets\n    std::vector<int>\
    \ vals;\n    std::vector<std::pair<int, int>> vals_sorted;\n    std::vector<std::vector<int>>\
    \ presuf;\n    std::vector<int> sufG, preH;\n    std::vector<std::vector<long\
    \ long>> R;\n\n    StaticRangeInversion(const std::vector<T> &sequence) : N(sequence.size()),\
    \ bs(ceil(sqrt(std::max(N, 1)))), nb_bc((N + bs - 1) / bs) {\n        std::vector<T>\
    \ dict = sequence;\n        std::sort(dict.begin(), dict.end()), dict.erase(std::unique(dict.begin(),\
    \ dict.end()), dict.end());\n        const int D = dict.size();\n        vals.reserve(N),\
    \ vals_sorted.reserve(N);\n        for (auto x : sequence) {\n            vals.emplace_back(std::lower_bound(dict.begin(),\
    \ dict.end(), x) - dict.begin());\n            vals_sorted.emplace_back(vals.back(),\
    \ int(vals.size()) - 1);\n        }\n\n        presuf.assign(nb_bc, std::vector<int>(N));\n\
    \        sufG.resize(N), preH.resize(N);\n\n        for (int ibc = 0; ibc < nb_bc;\
    \ ibc++) {\n            const int L = ibc * bs, R = std::min(L + bs, N);\n   \
    \         std::sort(vals_sorted.begin() + L, vals_sorted.begin() + R);\n     \
    \       std::vector<int> cnt(D + 1);\n            for (int i = L; i < R; i++)\
    \ { cnt[vals[i] + 1]++; }\n            for (int i = 0; i < D; i++) { cnt[i + 1]\
    \ += cnt[i]; }\n            for (int b = 0; b < ibc; b++) {\n                for\
    \ (int i = (b + 1) * bs - 1; i >= b * bs; i--) { presuf[ibc][i] = presuf[ibc][i\
    \ + 1] + cnt[vals[i]]; }\n            }\n            for (int b = ibc + 1; b <\
    \ bs; b++) {\n                for (int i = b * bs; i < std::min((b + 1) * bs,\
    \ N); i++) { presuf[ibc][i] = (i == b * bs ? 0 : presuf[ibc][i - 1]) + cnt.back()\
    \ - cnt[vals[i] + 1]; }\n            }\n            for (int i = L + 1; i < R;\
    \ i++) {\n                preH[i] = preH[i - 1] + std::count_if(vals.begin() +\
    \ L, vals.begin() + i, [&](int x) { return x > vals[i]; });\n            }\n \
    \           for (int i = R - 2; i >= L; i--) {\n                sufG[i] = sufG[i\
    \ + 1] + std::count_if(vals.begin() + i + 1, vals.begin() + R, [&](int x) { return\
    \ x < vals[i]; });\n            }\n        }\n\n        R.resize(nb_bc, std::vector<long\
    \ long>(nb_bc));\n        for (int i = nb_bc - 1; i >= 0; i--) {\n           \
    \ R[i][i] = sufG[i * bs];\n            for (int j = i + 1; j < nb_bc; j++) { R[i][j]\
    \ = R[i][j - 1] + R[i + 1][j] - R[i + 1][j - 1] + presuf[j][i * bs]; }\n     \
    \   }\n    }\n    long long get(int l, int r) const {\n        assert(l >= 0 and\
    \ l <= N and r >= 0 and r <= N and l <= r);\n        const int lb = (l + bs -\
    \ 1) / bs, rb = (r == N ? nb_bc : r / bs) - 1;\n        long long ret = 0;\n \
    \       if (l / bs == (r - 1) / bs) {\n            const int b = l / bs;\n   \
    \         ret += preH[r - 1] - (l % bs ? preH[l - 1] : 0);\n            int less_cnt\
    \ = 0;\n            for (int p = b * bs, q = std::min((b + 1) * bs, N); p < q;\
    \ p++) {\n                less_cnt += (vals_sorted[p].second >= l and vals_sorted[p].second\
    \ < r);\n                ret -= less_cnt * (vals_sorted[p].second < l);\n    \
    \        }\n            return ret;\n        }\n        ret += R[lb][rb];\n  \
    \      if (bs * lb > l) {\n            ret += sufG[l];\n            for (int b\
    \ = lb; b <= rb; b++) { ret += presuf[b][l]; }\n        }\n        if (bs * (rb\
    \ + 1) < r) {\n            ret += preH[r - 1];\n            for (int b = lb; b\
    \ <= rb; b++) { ret += presuf[b][r - 1]; }\n        }\n        int less_cnt =\
    \ 0, j = (rb + 1) * bs;\n        for (int p = std::max(0, (lb - 1) * bs), q =\
    \ lb * bs; p < q; p++) {\n            if (vals_sorted[p].second >= l) {\n    \
    \            while (j < std::min(N, (rb + 2) * bs) and (vals_sorted[j].second\
    \ >= r or vals_sorted[j].first < vals_sorted[p].first)) { less_cnt += (vals_sorted[j].second\
    \ < r), j++; }\n                ret += less_cnt;\n            }\n        }\n \
    \       return ret;\n    }\n};\n#line 2 \"data_structure/test/static_range_inversion.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, Q;\n    cin >> N >> Q;\n    vector<int>\
    \ A(N);\n    for (auto &a : A) cin >> a;\n    StaticRangeInversion<int> riq(A);\n\
    \n    while (Q--) {\n        int l, r;\n        cin >> l >> r;\n        cout <<\
    \ riq.get(l, r) << '\\n';\n    }\n}\n"
  code: "#include \"../static_range_inversion.hpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, Q;\n    cin >> N >> Q;\n    vector<int>\
    \ A(N);\n    for (auto &a : A) cin >> a;\n    StaticRangeInversion<int> riq(A);\n\
    \n    while (Q--) {\n        int l, r;\n        cin >> l >> r;\n        cout <<\
    \ riq.get(l, r) << '\\n';\n    }\n}\n"
  dependsOn:
  - data_structure/static_range_inversion.hpp
  isVerificationFile: true
  path: data_structure/test/static_range_inversion.test.cpp
  requiredBy: []
  timestamp: '2021-02-26 23:47:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/static_range_inversion.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/static_range_inversion.test.cpp
- /verify/data_structure/test/static_range_inversion.test.cpp.html
title: data_structure/test/static_range_inversion.test.cpp
---
