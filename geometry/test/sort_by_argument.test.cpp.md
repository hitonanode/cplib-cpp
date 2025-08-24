---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/sort_by_argument.hpp
    title: geometry/sort_by_argument.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "#line 1 \"geometry/test/sort_by_argument.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\n#line 2 \"geometry/sort_by_argument.hpp\"\
    \n\n// Point on grid, sortable by its argument\nstruct Point {\n    long long\
    \ X, Y;\n    Point() = default;\n    Point(long long x, long long y) : X(x), Y(y)\
    \ {}\n\n    bool operator<(const Point &r) const {\n        const int ll = lower_or_upper(),\
    \ lr = r.lower_or_upper();\n        if (ll != lr) return ll < lr;\n        return\
    \ X * r.Y > r.X * Y;\n    }\n\n    bool operator==(const Point &r) const {\n \
    \       return lower_or_upper() == r.lower_or_upper() and X * r.Y == r.X * Y;\n\
    \    }\n\n    int lower_or_upper() const {\n        if (Y) return Y > 0 ? 1 :\
    \ -1;\n        if (X) return X > 0 ? -1 : 1;\n        return 0; // origin\n  \
    \  }\n\n    void rotate_pi() { X = -X, Y = -Y; }\n};\n#line 3 \"geometry/test/sort_by_argument.test.cpp\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    int N;\n    cin >> N;\n    vector<Point> ps;\n    while (N--) {\n       \
    \ long long x, y;\n        cin >> x >> y;\n        ps.emplace_back(x, y);\n  \
    \  }\n    sort(ps.begin(), ps.end());\n    for (auto p : ps) cout << p.X << '\
    \ ' << p.Y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n#include \"../sort_by_argument.hpp\"\n\n#include <algorithm>\n#include <iostream>\n\
    #include <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N;\n    cin >> N;\n    vector<Point>\
    \ ps;\n    while (N--) {\n        long long x, y;\n        cin >> x >> y;\n  \
    \      ps.emplace_back(x, y);\n    }\n    sort(ps.begin(), ps.end());\n    for\
    \ (auto p : ps) cout << p.X << ' ' << p.Y << '\\n';\n}\n"
  dependsOn:
  - geometry/sort_by_argument.hpp
  isVerificationFile: true
  path: geometry/test/sort_by_argument.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 23:11:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: geometry/test/sort_by_argument.test.cpp
layout: document
redirect_from:
- /verify/geometry/test/sort_by_argument.test.cpp
- /verify/geometry/test/sort_by_argument.test.cpp.html
title: geometry/test/sort_by_argument.test.cpp
---
