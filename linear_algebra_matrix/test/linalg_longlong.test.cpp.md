---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/linalg_longlong.hpp
    title: linear_algebra_matrix/linalg_longlong.hpp
  - icon: ':heavy_check_mark:'
    path: number/bare_mod_algebra.hpp
    title: number/bare_mod_algebra.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624
  bundledCode: "#line 2 \"number/bare_mod_algebra.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n// CUT\
    \ begin\n// Solve ax+by=gcd(a, b)\ntemplate <class Int> Int extgcd(Int a, Int\
    \ b, Int &x, Int &y) {\n    Int d = a;\n    if (b != 0) {\n        d = extgcd(b,\
    \ a % b, y, x), y -= (a / b) * x;\n    } else {\n        x = 1, y = 0;\n    }\n\
    \    return d;\n}\n// Calculate a^(-1) (MOD m) s if gcd(a, m) == 1\n// Calculate\
    \ x s.t. ax == gcd(a, m) MOD m\ntemplate <class Int> Int mod_inverse(Int a, Int\
    \ m) {\n    Int x, y;\n    extgcd<Int>(a, m, x, y);\n    x %= m;\n    return x\
    \ + (x < 0) * m;\n}\n\n// Require: 1 <= b\n// return: (g, x) s.t. g = gcd(a, b),\
    \ xa = g MOD b, 0 <= x < b/g\ntemplate <class Int> /* constexpr */ std::pair<Int,\
    \ Int> inv_gcd(Int a, Int b) {\n    a %= b;\n    if (a < 0) a += b;\n    if (a\
    \ == 0) return {b, 0};\n    Int s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n\
    \        Int u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp =\
    \ s;\n        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0\
    \ < 0) m0 += b / s;\n    return {s, m0};\n}\n\ntemplate <class Int>\n/* constexpr\
    \ */ std::pair<Int, Int> crt(const std::vector<Int> &r, const std::vector<Int>\
    \ &m) {\n    assert(r.size() == m.size());\n    int n = int(r.size());\n    //\
    \ Contracts: 0 <= r0 < m0\n    Int r0 = 0, m0 = 1;\n    for (int i = 0; i < n;\
    \ i++) {\n        assert(1 <= m[i]);\n        Int r1 = r[i] % m[i], m1 = m[i];\n\
    \        if (r1 < 0) r1 += m1;\n        if (m0 < m1) {\n            std::swap(r0,\
    \ r1);\n            std::swap(m0, m1);\n        }\n        if (m0 % m1 == 0) {\n\
    \            if (r0 % m1 != r1) return {0, 0};\n            continue;\n      \
    \  }\n        Int g, im;\n        std::tie(g, im) = inv_gcd<Int>(m0, m1);\n\n\
    \        Int u1 = m1 / g;\n        if ((r1 - r0) % g) return {0, 0};\n\n     \
    \   Int x = (r1 - r0) / g % u1 * im % u1;\n        r0 += x * m0;\n        m0 *=\
    \ u1;\n        if (r0 < 0) r0 += m0;\n    }\n    return {r0, m0};\n}\n\n// \u87FB\
    \u672C P.262\n// \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\
    \uFF0C\u8272\u3005\u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\
    \u3089\u5143\u306E\u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\
    \u5F0F A * x = B mod M \u306E\u89E3\n// Requirement: M[i] > 0\n// Output: x =\
    \ first MOD second (if solution exists), (0, 0) (otherwise)\ntemplate <class Int>\n\
    std::pair<Int, Int>\nlinear_congruence(const std::vector<Int> &A, const std::vector<Int>\
    \ &B, const std::vector<Int> &M) {\n    Int r = 0, m = 1;\n    assert(A.size()\
    \ == M.size());\n    assert(B.size() == M.size());\n    for (int i = 0; i < (int)A.size();\
    \ i++) {\n        assert(M[i] > 0);\n        const Int ai = A[i] % M[i];\n   \
    \     Int a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i], a);\n        if\
    \ (b % d != 0) {\n            return std::make_pair(0, 0); // \u89E3\u306A\u3057\
    \n        }\n        Int t = b / d * mod_inverse<Int>(a / d, M[i] / d) % (M[i]\
    \ / d);\n        r += m * t;\n        m *= M[i] / d;\n    }\n    return std::make_pair((r\
    \ < 0 ? r + m : r), m);\n}\n\nint pow_mod(int x, long long n, int md) {\n    if\
    \ (md == 1) return 0;\n    long long ans = 1;\n    while (n > 0) {\n        if\
    \ (n & 1) ans = ans * x % md;\n        x = (long long)x * x % md;\n        n >>=\
    \ 1;\n    }\n    return ans;\n}\n#line 4 \"linear_algebra_matrix/linalg_longlong.hpp\"\
    \n#include <cstdlib>\n#line 6 \"linear_algebra_matrix/linalg_longlong.hpp\"\n\n\
    // CUT begin\ntemplate <typename lint, typename mdint>\nstd::vector<std::vector<lint>>\
    \ gauss_jordan(std::vector<std::vector<lint>> mtr, mdint mod) {\n    // Gauss-Jordan\
    \ elimination \u884C\u57FA\u672C\u5909\u5F62\u306E\u307F\u3092\u7528\u3044\u308B\
    \u30AC\u30A6\u30B9\u6D88\u53BB\u6CD5\n    int H = mtr.size(), W = mtr[0].size(),\
    \ c = 0;\n    for (int h = 0; h < H; h++) {\n        if (c == W) break;\n    \
    \    int piv = -1;\n        for (int j = h; j < H; j++)\n            if (mtr[j][c])\
    \ {\n                if (piv == -1 or abs(mtr[j][c]) > abs(mtr[piv][c])) piv =\
    \ j;\n            }\n        if (piv == -1) {\n            c++;\n            h--;\n\
    \            continue;\n        }\n        std::swap(mtr[piv], mtr[h]);\n    \
    \    if (h != piv) {\n            for (int w = 0; w < W; w++) {\n            \
    \    mtr[piv][w] =\n                    mtr[piv][w] ? mod - mtr[piv][w] : 0; //\
    \ To preserve sign of determinant\n            }\n        }\n        lint pivinv\
    \ = mod_inverse<lint>(mtr[h][c], mod);\n        for (int hh = 0; hh < H; hh++)\
    \ {\n            if (hh == h) continue;\n            lint coeff = mtr[hh][c] *\
    \ pivinv % mod;\n            for (int w = W - 1; w >= c; w--) {\n            \
    \    mtr[hh][w] = mtr[hh][w] - mtr[h][w] * coeff % mod;\n                if (mtr[hh][w]\
    \ < 0) mtr[hh][w] += mod;\n            }\n        }\n        c++;\n    }\n   \
    \ return mtr;\n}\n\ntemplate <typename lint>\nint rank_gauss_jordan(const std::vector<std::vector<lint>>\
    \ &mtr) // Rank of Gauss-Jordan eliminated matrix\n{\n    for (int h = (int)mtr.size()\
    \ - 1; h >= 0; h--) {\n        for (auto v : mtr[h])\n            if (v) return\
    \ h + 1;\n    }\n    return 0;\n}\n\ntemplate <typename lint, typename mdint>\n\
    lint mod_determinant(std::vector<std::vector<lint>> mtr, mdint mod) {\n    if\
    \ (mtr.empty()) return 1 % mod;\n    assert(mtr.size() == mtr[0].size());\n  \
    \  lint ans = 1;\n    mtr = gauss_jordan(mtr, mod);\n    for (int i = 0; i < (int)mtr.size();\
    \ i++) ans = ans * mtr[i][i] % mod;\n    return ans;\n}\n\ntemplate <typename\
    \ lint, typename mdint>\nstd::vector<std::vector<lint>>\nmatmul(const std::vector<std::vector<lint>>\
    \ &A, const std::vector<std::vector<lint>> &B, mdint mod) {\n    int H = A.size(),\
    \ W = B[0].size(), K = B.size();\n    std::vector<std::vector<lint>> C(H, std::vector<lint>(W));\n\
    \    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n  \
    \          for (int k = 0; k < K; k++) (C[i][j] += A[i][k] * B[k][j]) %= mod;\n\
    \        }\n    }\n    return C;\n}\n\ntemplate <typename lint, typename mdint>\n\
    std::vector<lint>\nmatmul(const std::vector<std::vector<lint>> &A, const std::vector<lint>\
    \ &v, mdint mod) {\n    std::vector<lint> res(A.size());\n    for (int i = 0;\
    \ i < (int)A.size(); i++) {\n        for (int j = 0; j < (int)v.size(); j++) (res[i]\
    \ += A[i][j] * v[j]) %= mod;\n    }\n    return res;\n}\n\ntemplate <typename\
    \ lint, typename powint, typename mdint>\nstd::vector<std::vector<lint>> matpower(std::vector<std::vector<lint>>\
    \ X, powint n, mdint mod) {\n    std::vector<std::vector<lint>> res(X.size(),\
    \ std::vector<lint>(X.size()));\n    for (int i = 0; i < (int)res.size(); i++)\
    \ res[i][i] = 1;\n    while (n) {\n        if (n & 1) res = matmul(res, X, mod);\n\
    \        X = matmul(X, X, mod);\n        n >>= 1;\n    }\n    return res;\n}\n\
    #line 2 \"linear_algebra_matrix/test/linalg_longlong.test.cpp\"\n#include <iostream>\n\
    #include <numeric>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624\"\
    \nusing namespace std;\n\ntemplate <typename T> istream &operator>>(istream &is,\
    \ vector<T> &vec) {\n    for (auto &v : vec) is >> v;\n    return is;\n}\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    using lint\
    \ = long long;\n\n    int N, T;\n    cin >> N;\n    vector<vector<lint>> A(N,\
    \ vector<lint>(N));\n    cin >> A;\n    vector<lint> v(N);\n    cin >> v >> T;\n\
    \    A = matpower(A, T, 2);\n    vector<vector<lint>> B = A;\n    for (int i =\
    \ 0; i < N; i++) B[i].push_back(v[i]);\n    B = gauss_jordan(B, 2);\n    for (int\
    \ i = 0; i < N; i++) {\n        if (accumulate(B[i].begin(), B[i].begin() + N,\
    \ 0) == 0 and B[i][N]) {\n            cout << \"none\\n\";\n            return\
    \ 0;\n        }\n    }\n    int rnk = rank_gauss_jordan(B);\n    if (rnk < N)\
    \ {\n        cout << \"ambiguous\\n\";\n        return 0;\n    }\n    vector<lint>\
    \ ret(N);\n    for (int i = N - 1; i >= 0; i--) {\n        int a = 0;\n      \
    \  for (int j = i + 1; j < N; j++) a += ret[j] * B[i][j];\n        ret[i] = (a\
    \ % 2 != B[i][N]);\n    }\n\n    for (int i = 0; i < N; i++) cout << ret[i] <<\
    \ (i + 1 == N ? '\\n' : ' ');\n}\n"
  code: "#include \"../linalg_longlong.hpp\"\n#include <iostream>\n#include <numeric>\n\
    #define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624\"\
    \nusing namespace std;\n\ntemplate <typename T> istream &operator>>(istream &is,\
    \ vector<T> &vec) {\n    for (auto &v : vec) is >> v;\n    return is;\n}\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    using lint\
    \ = long long;\n\n    int N, T;\n    cin >> N;\n    vector<vector<lint>> A(N,\
    \ vector<lint>(N));\n    cin >> A;\n    vector<lint> v(N);\n    cin >> v >> T;\n\
    \    A = matpower(A, T, 2);\n    vector<vector<lint>> B = A;\n    for (int i =\
    \ 0; i < N; i++) B[i].push_back(v[i]);\n    B = gauss_jordan(B, 2);\n    for (int\
    \ i = 0; i < N; i++) {\n        if (accumulate(B[i].begin(), B[i].begin() + N,\
    \ 0) == 0 and B[i][N]) {\n            cout << \"none\\n\";\n            return\
    \ 0;\n        }\n    }\n    int rnk = rank_gauss_jordan(B);\n    if (rnk < N)\
    \ {\n        cout << \"ambiguous\\n\";\n        return 0;\n    }\n    vector<lint>\
    \ ret(N);\n    for (int i = N - 1; i >= 0; i--) {\n        int a = 0;\n      \
    \  for (int j = i + 1; j < N; j++) a += ret[j] * B[i][j];\n        ret[i] = (a\
    \ % 2 != B[i][N]);\n    }\n\n    for (int i = 0; i < N; i++) cout << ret[i] <<\
    \ (i + 1 == N ? '\\n' : ' ');\n}\n"
  dependsOn:
  - linear_algebra_matrix/linalg_longlong.hpp
  - number/bare_mod_algebra.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/linalg_longlong.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/linalg_longlong.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/linalg_longlong.test.cpp
- /verify/linear_algebra_matrix/test/linalg_longlong.test.cpp.html
title: linear_algebra_matrix/test/linalg_longlong.test.cpp
---
