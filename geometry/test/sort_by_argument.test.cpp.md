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
  bundledCode: "#line 2 \"geometry/sort_by_argument.hpp\"\n#include <cmath>\n\n//\
    \ CUT begin\n// Point on grid, sortable by its argument\nstruct Point {\n    constexpr\
    \ static double eps = 1e-2;\n    long long X, Y;\n    double theta;\n    Point()\
    \ = default;\n    Point(long long x, long long y) : X(x), Y(y), theta(std::atan2(y,\
    \ x)) {}\n    bool operator<(const Point &r) const {\n        double b = theta\
    \ - r.theta;\n        return std::abs(b) > eps ? (b < 0) : (X * r.Y > r.X * Y);\n\
    \    }\n    bool operator==(const Point &r) const {\n        return std::abs(theta\
    \ - r.theta) < eps and X * r.Y == r.X * Y;\n    }\n    void rotate_pi() {\n  \
    \      theta += M_PI;\n        X *= -1;\n        Y *= -1;\n    }\n};\n#line 2\
    \ \"geometry/test/sort_by_argument.test.cpp\"\n#include <algorithm>\n#include\
    \ <iostream>\n#include <vector>\n#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<Point> ps;\n    while (N--) {\n      \
    \  long long x, y;\n        cin >> x >> y;\n        ps.emplace_back(x, y);\n \
    \   }\n    sort(ps.begin(), ps.end());\n    for (auto p : ps) cout << p.X << '\
    \ ' << p.Y << '\\n';\n}\n"
  code: "#include \"geometry/sort_by_argument.hpp\"\n#include <algorithm>\n#include\
    \ <iostream>\n#include <vector>\n#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<Point> ps;\n    while (N--) {\n      \
    \  long long x, y;\n        cin >> x >> y;\n        ps.emplace_back(x, y);\n \
    \   }\n    sort(ps.begin(), ps.end());\n    for (auto p : ps) cout << p.X << '\
    \ ' << p.Y << '\\n';\n}\n"
  dependsOn:
  - geometry/sort_by_argument.hpp
  isVerificationFile: true
  path: geometry/test/sort_by_argument.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: geometry/test/sort_by_argument.test.cpp
layout: document
redirect_from:
- /verify/geometry/test/sort_by_argument.test.cpp
- /verify/geometry/test/sort_by_argument.test.cpp.html
title: geometry/test/sort_by_argument.test.cpp
---
