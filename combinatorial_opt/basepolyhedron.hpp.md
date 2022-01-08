---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://www.amazon.co.jp/dp/B01N6G0579>,
    - https://yukicoder.me/problems/no/1316>
  bundledCode: "#line 1 \"combinatorial_opt/basepolyhedron.hpp\"\n#include <algorithm>\n\
    #include <functional>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// LinearProgrammingOnBasePolyhedron : Maximize/minimize linear\
    \ function on base polyhedron, using\n// Edmonds' algorithm\n//\n// maximize/minimize\
    \ cx s.t. (x on some base polyhedron)\n// Reference: <https://www.amazon.co.jp/dp/B01N6G0579>,\
    \ Sec. 2.4, Algorithm 2.2-2.3\n//            \"Submodular Functions, Matroids,\
    \ and Certain Polyhedra\" [Edmonds+, 1970]\n// Used for: <https://yukicoder.me/problems/no/1316>\n\
    template <typename Tvalue> struct LinearProgrammingOnBasePolyhedron {\n    using\
    \ Tfunc = std::function<Tvalue(int, const std::vector<Tvalue> &)>;\n    static\
    \ Tvalue EPS;\n    int N;\n    std::vector<Tvalue> c;\n    Tfunc maximize_xi;\n\
    \    Tvalue xsum;\n    bool minimize;\n\n    Tvalue fun;\n    std::vector<Tvalue>\
    \ x;\n    bool infeasible;\n\n    void _init(const std::vector<Tvalue> &c_, Tfunc\
    \ q_, Tvalue xsum_, Tvalue xlowerlimit,\n               bool minimize_) {\n  \
    \      N = c_.size();\n        c = c_;\n        maximize_xi = q_;\n        xsum\
    \ = xsum_;\n        minimize = minimize_;\n        fun = 0;\n        x.assign(N,\
    \ xlowerlimit);\n        infeasible = false;\n    }\n\n    void _solve() {\n \
    \       std::vector<std::pair<Tvalue, int>> c2i(N);\n        for (int i = 0; i\
    \ < N; i++) c2i[i] = std::make_pair(c[i], i);\n\n        std::sort(c2i.begin(),\
    \ c2i.end());\n        if (!minimize) std::reverse(c2i.begin(), c2i.end());\n\
    \        for (const auto &p : c2i) {\n            const int i = p.second;\n  \
    \          x[i] = maximize_xi(i, x);\n        }\n        Tvalue error = std::accumulate(x.begin(),\
    \ x.end(), Tvalue(0)) - xsum;\n        if (error > EPS or -error > EPS) {\n  \
    \          infeasible = true;\n        } else {\n            for (int i = 0; i\
    \ < N; i++) fun += x[i] * c[i];\n        }\n    }\n\n    LinearProgrammingOnBasePolyhedron(const\
    \ std::vector<Tvalue> &c_, Tfunc q_, Tvalue xsum_,\n                         \
    \             Tvalue xlowerlimit, bool minimize_) {\n        _init(c_, q_, xsum_,\
    \ xlowerlimit, minimize_);\n        _solve();\n    }\n};\ntemplate <> long long\
    \ LinearProgrammingOnBasePolyhedron<long long>::EPS = 0;\ntemplate <> long double\
    \ LinearProgrammingOnBasePolyhedron<long double>::EPS = 1e-10;\n"
  code: "#include <algorithm>\n#include <functional>\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// LinearProgrammingOnBasePolyhedron\
    \ : Maximize/minimize linear function on base polyhedron, using\n// Edmonds' algorithm\n\
    //\n// maximize/minimize cx s.t. (x on some base polyhedron)\n// Reference: <https://www.amazon.co.jp/dp/B01N6G0579>,\
    \ Sec. 2.4, Algorithm 2.2-2.3\n//            \"Submodular Functions, Matroids,\
    \ and Certain Polyhedra\" [Edmonds+, 1970]\n// Used for: <https://yukicoder.me/problems/no/1316>\n\
    template <typename Tvalue> struct LinearProgrammingOnBasePolyhedron {\n    using\
    \ Tfunc = std::function<Tvalue(int, const std::vector<Tvalue> &)>;\n    static\
    \ Tvalue EPS;\n    int N;\n    std::vector<Tvalue> c;\n    Tfunc maximize_xi;\n\
    \    Tvalue xsum;\n    bool minimize;\n\n    Tvalue fun;\n    std::vector<Tvalue>\
    \ x;\n    bool infeasible;\n\n    void _init(const std::vector<Tvalue> &c_, Tfunc\
    \ q_, Tvalue xsum_, Tvalue xlowerlimit,\n               bool minimize_) {\n  \
    \      N = c_.size();\n        c = c_;\n        maximize_xi = q_;\n        xsum\
    \ = xsum_;\n        minimize = minimize_;\n        fun = 0;\n        x.assign(N,\
    \ xlowerlimit);\n        infeasible = false;\n    }\n\n    void _solve() {\n \
    \       std::vector<std::pair<Tvalue, int>> c2i(N);\n        for (int i = 0; i\
    \ < N; i++) c2i[i] = std::make_pair(c[i], i);\n\n        std::sort(c2i.begin(),\
    \ c2i.end());\n        if (!minimize) std::reverse(c2i.begin(), c2i.end());\n\
    \        for (const auto &p : c2i) {\n            const int i = p.second;\n  \
    \          x[i] = maximize_xi(i, x);\n        }\n        Tvalue error = std::accumulate(x.begin(),\
    \ x.end(), Tvalue(0)) - xsum;\n        if (error > EPS or -error > EPS) {\n  \
    \          infeasible = true;\n        } else {\n            for (int i = 0; i\
    \ < N; i++) fun += x[i] * c[i];\n        }\n    }\n\n    LinearProgrammingOnBasePolyhedron(const\
    \ std::vector<Tvalue> &c_, Tfunc q_, Tvalue xsum_,\n                         \
    \             Tvalue xlowerlimit, bool minimize_) {\n        _init(c_, q_, xsum_,\
    \ xlowerlimit, minimize_);\n        _solve();\n    }\n};\ntemplate <> long long\
    \ LinearProgrammingOnBasePolyhedron<long long>::EPS = 0;\ntemplate <> long double\
    \ LinearProgrammingOnBasePolyhedron<long double>::EPS = 1e-10;\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/basepolyhedron.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/basepolyhedron.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/basepolyhedron.hpp
- /library/combinatorial_opt/basepolyhedron.hpp.html
title: combinatorial_opt/basepolyhedron.hpp
---
