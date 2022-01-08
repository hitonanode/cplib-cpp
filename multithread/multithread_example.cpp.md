---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"multithread/multithread_example.cpp\"\n// \u30DE\u30EB\u30C1\
    \u30B9\u30EC\u30C3\u30C9\u3067\u30ED\u30FC\u30AB\u30EB\u5B9F\u884C\u9AD8\u901F\
    \u5316 \u30B3\u30F3\u30D1\u30A4\u30EB\u6642\u306E\u30AA\u30D7\u30B7\u30E7\u30F3\
    \u306B -pthread \u304C\u5FC5\u8981\n#include <bits/stdc++.h>\nusing namespace\
    \ std;\nusing pint = pair<int, int>;\n#define FOR(i, begin, end) for (int i =\
    \ (begin), i##_end_ = (end); i < i##_end_; i++)\n#define IFOR(i, begin, end) for\
    \ (int i = (end)-1, i##_begin_ = (begin); i >= i##_begin_; i--)\n#define REP(i,\
    \ n) FOR(i, 0, n)\n#define IREP(i, n) IFOR(i, 0, n)\n#define dbg(x) cerr << #x\
    \ << \" = \" << (x) << \" (L\" << __LINE__ << \") \" << __FILE__ << endl;\n\n\
    struct SingleCaseInput {\n    int N, M;\n    vector<pint> query;\n    SingleCaseInput(int\
    \ n, int m, const vector<pint> &q) : N(n), M(m), query(q) {}\n};\nvector<SingleCaseInput>\
    \ testcase;\n\nvector<string> ret;\n\n/* \u5404\u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\
    \u306E\u5B8C\u4E86\u72B6\u6CC1\u3092\u4FDD\u6301 */\nmutex mtx;\nvector<int> done;\n\
    \nvoid solve(int tc) { /* tc\u500B\u76EE\u306E\u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\
    \u3092\u51E6\u7406\u3059\u308B\u95A2\u6570 */\n}\n\nvoid run() {\n    /* \u672A\
    \u5B8C\u4E86\u3067\u6700\u3082\u756A\u53F7\u304C\u82E5\u3044\u30C6\u30B9\u30C8\
    \u30B1\u30FC\u30B9\u3092\u51E6\u7406 */\n    int i = 0;\n    while (true) {\n\
    \        mtx.lock();\n        while (i < done.size() and done[i]) i++;\n     \
    \   if (i < done.size()) done[i] = 1;\n        mtx.unlock();\n        if (i >=\
    \ done.size()) break;\n        solve(i);\n    }\n}\n\nint main() {\n    auto START\
    \ = chrono::system_clock::now();\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \n    int TC;\n    cin >> TC;\n    REP(tc, TC) {\n        int N, M;\n        cin\
    \ >> N >> M;\n        vector<pint> q(M);\n        REP(i, M) cin >> q[i].first\
    \ >> q[i].second;\n        testcase.emplace_back(N, M, q);\n    }\n    ret.resize(TC);\n\
    \    done.assign(TC, 0);\n\n    size_t n_thread =\n        thread::hardware_concurrency();\
    \ // \u30B9\u30EC\u30C3\u30C9\u6570\u3092\u81EA\u52D5\u53D6\u5F97\uFF0E 8\u3084\
    16\u3068\u624B\u3067\u8A2D\u5B9A\u3057\u3066\u3082\u3088\u3044\n    if (n_thread\
    \ == 0) n_thread = 1;\n\n    vector<thread> threads(n_thread);\n    REP(i, n_thread)\
    \ { threads[i] = thread(run); }\n    REP(i, n_thread) { threads[i].join(); }\n\
    \    REP(tc, TC) { cout << \"Case #\" << tc + 1 << \": \" << ret[tc] << endl;\
    \ }\n    dbg(chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START)\n            .count());\n}\n"
  code: "// \u30DE\u30EB\u30C1\u30B9\u30EC\u30C3\u30C9\u3067\u30ED\u30FC\u30AB\u30EB\
    \u5B9F\u884C\u9AD8\u901F\u5316 \u30B3\u30F3\u30D1\u30A4\u30EB\u6642\u306E\u30AA\
    \u30D7\u30B7\u30E7\u30F3\u306B -pthread \u304C\u5FC5\u8981\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing pint = pair<int, int>;\n#define FOR(i, begin, end)\
    \ for (int i = (begin), i##_end_ = (end); i < i##_end_; i++)\n#define IFOR(i,\
    \ begin, end) for (int i = (end)-1, i##_begin_ = (begin); i >= i##_begin_; i--)\n\
    #define REP(i, n) FOR(i, 0, n)\n#define IREP(i, n) IFOR(i, 0, n)\n#define dbg(x)\
    \ cerr << #x << \" = \" << (x) << \" (L\" << __LINE__ << \") \" << __FILE__ <<\
    \ endl;\n\nstruct SingleCaseInput {\n    int N, M;\n    vector<pint> query;\n\
    \    SingleCaseInput(int n, int m, const vector<pint> &q) : N(n), M(m), query(q)\
    \ {}\n};\nvector<SingleCaseInput> testcase;\n\nvector<string> ret;\n\n/* \u5404\
    \u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\u306E\u5B8C\u4E86\u72B6\u6CC1\u3092\u4FDD\
    \u6301 */\nmutex mtx;\nvector<int> done;\n\nvoid solve(int tc) { /* tc\u500B\u76EE\
    \u306E\u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\u3092\u51E6\u7406\u3059\u308B\u95A2\
    \u6570 */\n}\n\nvoid run() {\n    /* \u672A\u5B8C\u4E86\u3067\u6700\u3082\u756A\
    \u53F7\u304C\u82E5\u3044\u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\u3092\u51E6\u7406\
    \ */\n    int i = 0;\n    while (true) {\n        mtx.lock();\n        while (i\
    \ < done.size() and done[i]) i++;\n        if (i < done.size()) done[i] = 1;\n\
    \        mtx.unlock();\n        if (i >= done.size()) break;\n        solve(i);\n\
    \    }\n}\n\nint main() {\n    auto START = chrono::system_clock::now();\n   \
    \ std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\n    int TC;\n  \
    \  cin >> TC;\n    REP(tc, TC) {\n        int N, M;\n        cin >> N >> M;\n\
    \        vector<pint> q(M);\n        REP(i, M) cin >> q[i].first >> q[i].second;\n\
    \        testcase.emplace_back(N, M, q);\n    }\n    ret.resize(TC);\n    done.assign(TC,\
    \ 0);\n\n    size_t n_thread =\n        thread::hardware_concurrency(); // \u30B9\
    \u30EC\u30C3\u30C9\u6570\u3092\u81EA\u52D5\u53D6\u5F97\uFF0E 8\u308416\u3068\u624B\
    \u3067\u8A2D\u5B9A\u3057\u3066\u3082\u3088\u3044\n    if (n_thread == 0) n_thread\
    \ = 1;\n\n    vector<thread> threads(n_thread);\n    REP(i, n_thread) { threads[i]\
    \ = thread(run); }\n    REP(i, n_thread) { threads[i].join(); }\n    REP(tc, TC)\
    \ { cout << \"Case #\" << tc + 1 << \": \" << ret[tc] << endl; }\n    dbg(chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START)\n            .count());\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: multithread/multithread_example.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: multithread/multithread_example.cpp
layout: document
redirect_from:
- /library/multithread/multithread_example.cpp
- /library/multithread/multithread_example.cpp.html
title: multithread/multithread_example.cpp
---
