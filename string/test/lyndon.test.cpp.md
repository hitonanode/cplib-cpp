---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/lyndon.hpp
    title: "Lyndon words \uFF08Lyndon \u6587\u5B57\u5217\u306B\u95A2\u3059\u308B\u5404\
      \u7A2E\u95A2\u6570\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lyndon_factorization
    links:
    - https://judge.yosupo.jp/problem/lyndon_factorization
  bundledCode: "#line 1 \"string/test/lyndon.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/lyndon_factorization\"\
    \n#line 2 \"string/lyndon.hpp\"\n#include <algorithm>\n#include <cassert>\n#include\
    \ <functional>\n#include <string>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\n// CUT begin\n// Lyndon factorization based on Duval's algorithm\n\
    // **NOT VERIFIED YET**\n// Reference:\n// [1] K. T. Chen, R. H. Fox, R. C. Lyndon,\n\
    //     \"Free Differential Calculus, IV. The Quotient Groups of the Lower Central\
    \ Series,\"\n//     Annals of Mathematics, 68(1), 81-95, 1958.\n// [2] J. P. Duval,\
    \ \"Factorizing words over an ordered alphabet,\"\n//     Journal of Algorithms,\
    \ 4(4), 363-381, 1983.\n// - https://cp-algorithms.com/string/lyndon_factorization.html\n\
    // - https://qiita.com/nakashi18/items/66882bd6e0127174267a\ntemplate <typename\
    \ T>\nstd::vector<std::pair<int, int>> lyndon_factorization(const std::vector<T>\
    \ &S) {\n    const int N = S.size();\n    std::vector<std::pair<int, int>> ret;\n\
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
    \ Journal on Computing, 46(5), 1501-1514, 2017.\ntemplate <typename String, typename\
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
    //     SIAM Journal on Computing, 46(5), 1501-1514, 2017.\ntemplate <typename\
    \ LCPLENCallable, typename String>\nstd::vector<std::tuple<int, int, int>> run_enumerate(String\
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
    \ ret.end()), ret.end());\n    return ret;\n}\n\n// Enumerate Lyndon words up\
    \ to length n in lexical order\n// https://github.com/bqi343/USACO/blob/master/Implementations/content/combinatorial%20(11.2)/DeBruijnSeq.h\n\
    // Example: k=2, n=4 => [[0,],[0,0,0,1,],[0,0,1,],[0,0,1,1,],[0,1,],[0,1,1,],[0,1,1,1,],[1,],]\n\
    // Verified: https://codeforces.com/gym/102001/problem/C / https://codeforces.com/gym/100162/problem/G\n\
    std::vector<std::vector<int>> enumerate_lyndon_words(int k, int n) {\n    assert(k\
    \ > 0);\n    assert(n > 0);\n    std::vector<std::vector<int>> ret;\n    std::vector<int>\
    \ aux(n + 1);\n\n    std::function<void(int, int)> gen = [&](int t, int p) {\n\
    \        // t: current length\n        // p: current min cycle length\n      \
    \  if (t == n) {\n            std::vector<int> tmp(aux.begin() + 1, aux.begin()\
    \ + p + 1);\n            ret.push_back(std::move(tmp));\n        } else {\n  \
    \          ++t;\n            aux[t] = aux[t - p];\n            gen(t, p);\n  \
    \          while (++aux[t] < k) gen(t, t);\n        }\n    };\n    gen(0, 1);\n\
    \    return ret;\n}\n#line 3 \"string/test/lyndon.test.cpp\"\n\n#include <iostream>\n\
    #line 6 \"string/test/lyndon.test.cpp\"\nusing namespace std;\n\nint main() {\n\
    \    cin.tie(nullptr);\n    ios_base::sync_with_stdio(false);\n\n    string S;\n\
    \    cin >> S;\n    auto ret = lyndon_factorization(S);\n    for (auto [l, len]\
    \ : ret) cout << l << ' ';\n    cout << S.size() << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lyndon_factorization\"\n\
    #include \"../lyndon.hpp\"\n\n#include <iostream>\n#include <string>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr);\n    ios_base::sync_with_stdio(false);\n\
    \n    string S;\n    cin >> S;\n    auto ret = lyndon_factorization(S);\n    for\
    \ (auto [l, len] : ret) cout << l << ' ';\n    cout << S.size() << '\\n';\n}\n"
  dependsOn:
  - string/lyndon.hpp
  isVerificationFile: true
  path: string/test/lyndon.test.cpp
  requiredBy: []
  timestamp: '2023-12-26 22:37:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/lyndon.test.cpp
layout: document
redirect_from:
- /verify/string/test/lyndon.test.cpp
- /verify/string/test/lyndon.test.cpp.html
title: string/test/lyndon.test.cpp
---
