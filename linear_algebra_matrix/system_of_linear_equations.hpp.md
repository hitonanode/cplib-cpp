---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: linear_algebra_matrix/linalg_modint.hpp
    title: linear_algebra_matrix/linalg_modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: linear_algebra_matrix/test/system_of_linear_equations.test.cpp
    title: linear_algebra_matrix/test/system_of_linear_equations.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"linear_algebra_matrix/linalg_modint.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <iterator>\n#include <vector>\n\
    \n// CUT begin\ntemplate <typename T>\nstruct matrix\n{\n    int H, W;\n    std::vector<T>\
    \ elem;\n    typename std::vector<T>::iterator operator[](int i) { return elem.begin()\
    \ + i * W; }\n    inline T &at(int i, int j) { return elem[i * W + j]; }\n   \
    \ inline T get(int i, int j) const { return elem[i * W + j]; }\n    operator std::vector<std::vector<T>>()\
    \ const {\n        std::vector<std::vector<T>> ret(H);\n        for (int i = 0;\
    \ i < H; i++) std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));\n\
    \        return ret;\n    }\n\n    matrix() = default;\n    matrix(int H, int\
    \ W) : H(H), W(W), elem(H * W) {}\n    matrix(const std::vector<std::vector<T>>\
    \ &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {\n        for (auto &raw :\
    \ d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));\n    }\n\n \
    \   static matrix Identity(int N) {\n        matrix ret(N, N);\n        for (int\
    \ i = 0; i < N; i++) ret.at(i, i) = 1;\n        return ret;\n    }\n\n    matrix\
    \ operator-() const { matrix ret(H, W); for (int i = 0; i < H * W; i++) ret.elem[i]\
    \ = -elem[i]; return ret; }\n    matrix operator*(const T &v) const { matrix ret\
    \ = *this; for (auto &x : ret.elem) x *= v; return ret; }\n    matrix operator/(const\
    \ T &v) const { matrix ret = *this; for (auto &x : ret.elem) x /= v; return ret;\
    \ }\n    matrix operator+(const matrix &r) const { matrix ret = *this; for (int\
    \ i = 0; i < H * W; i++) ret.elem[i] += r.elem[i]; return ret; }\n    matrix operator-(const\
    \ matrix &r) const { matrix ret = *this; for (int i = 0; i < H * W; i++) ret.elem[i]\
    \ -= r.elem[i]; return ret; }\n    matrix operator*(const matrix &r) const {\n\
    \        matrix ret(H, r.W);\n        for (int i = 0; i < H; i++) {\n        \
    \    for (int k = 0; k < W; k++) {\n                for (int j = 0; j < r.W; j++)\
    \ {\n                    ret.at(i, j) += this->get(i, k) * r.get(k, j);\n    \
    \            }\n            }\n        }\n        return ret;\n    }\n    matrix\
    \ &operator*=(const T &v) { return *this = *this * v; }\n    matrix &operator/=(const\
    \ T &v) { return *this = *this / v; }\n    matrix &operator+=(const matrix &r)\
    \ { return *this = *this + r; }\n    matrix &operator-=(const matrix &r) { return\
    \ *this = *this - r; }\n    matrix &operator*=(const matrix &r) { return *this\
    \ = *this * r; }\n    bool operator==(const matrix &r) const { return H == r.H\
    \ and W == r.W and elem == r.elem; }\n    bool operator!=(const matrix &r) const\
    \ { return H != r.H or W != r.W or elem != r.elem; }\n    bool operator<(const\
    \ matrix &r) const { return elem < r.elem; }\n    matrix pow(int64_t n) const\
    \ {\n        matrix ret = Identity(H);\n        if (n == 0) return ret;\n    \
    \    for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {\n            ret *=\
    \ ret;\n            if ((n >> i) & 1) ret *= (*this);\n        }\n        return\
    \ ret;\n    }\n    matrix transpose() const {\n        matrix ret(W, H);\n   \
    \     for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i,\
    \ j);\n        return ret;\n    }\n    // Gauss-Jordan elimination\n    // - Require\
    \ inverse for every non-zero element\n    // - Complexity: O(H^2 W)\n    matrix\
    \ gauss_jordan() const {\n        int c = 0;\n        matrix mtr(*this);\n   \
    \     for (int h = 0; h < H; h++) {\n            if (c == W) break;\n        \
    \    int piv = -1;\n            for (int j = h; j < H; j++) if (mtr.get(j, c))\
    \ {\n                piv = j;\n                break;\n            }\n       \
    \     if (piv == -1) { c++; h--; continue; }\n            if (h != piv) {\n  \
    \              for (int w = 0; w < W; w++) {\n                    std::swap(mtr[piv][w],\
    \ mtr[h][w]);\n                    mtr.at(piv, w) *= -1; // To preserve sign of\
    \ determinant\n                }\n            }\n            for (int hh = 0;\
    \ hh < H; hh++) if (hh != h) {\n                T coeff = mtr.at(hh, c) * mtr.at(h,\
    \ c).inv();\n                for (int w = W - 1; w >= c; w--) {\n            \
    \        mtr.at(hh, w) -= mtr.at(h, w) * coeff;\n                }\n         \
    \   }\n            c++;\n        }\n        return mtr;\n    }\n    int rank_of_gauss_jordan()\
    \ const {\n        for (int i = H * W - 1; i >= 0; i--) if (elem[i]) return i\
    \ / W + 1;\n        return 0;\n    }\n    T determinant_of_upper_triangle() const\
    \ {\n        T ret = 1;\n        for (int i = 0; i < H; i++) ret *= get(i, i);\n\
    \        return ret;\n    }\n    int inverse() {\n        assert(H == W);\n  \
    \      std::vector<std::vector<T>> ret = Identity(H), tmp = *this;\n        int\
    \ rank = 0;\n        for (int i = 0; i < H; i++) {\n            int ti = i;\n\
    \            while (ti < H and tmp[ti][i] == 0) ti++;\n            if (ti == H)\
    \ continue;\n            else rank++;\n            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);\n\
    \            T inv = tmp[i][i].inv();\n            for (int j = 0; j < W; j++)\
    \ {\n                ret[i][j] *= inv;\n            }\n            for (int j\
    \ = i + 1; j < W; j++) {\n                tmp[i][j] *= inv;\n            }\n \
    \           for (int h = 0; h < H; h++) {\n                if (i == h) continue;\n\
    \                const T c = -tmp[h][i];\n                for (int j = 0; j <\
    \ W; j++) {\n                    ret[h][j] += ret[i][j] * c;\n               \
    \ }\n                for (int j = i + 1; j < W; j++) {\n                    tmp[h][j]\
    \ += tmp[i][j] * c;\n                }\n            }\n        }\n        *this\
    \ = ret;\n        return rank;\n    }\n    friend std::vector<T> operator*(const\
    \ matrix &m, const std::vector<T> &v) {\n        assert(m.W == int(v.size()));\n\
    \        std::vector<T> ret(m.H);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) {\n                ret[i] += m.get(i,\
    \ j) * v[j];\n            }\n        }\n        return ret;\n    }\n    friend\
    \ std::vector<T> operator*(const std::vector<T> &v, const matrix &m) {\n     \
    \   assert(int(v.size()) == m.H);\n        std::vector<T> ret(m.W);\n        for\
    \ (int i = 0; i < m.H; i++) {\n            for (int j = 0; j < m.W; j++) {\n \
    \               ret[j] += v[i] * m.get(i, j);\n            }\n        }\n    \
    \    return ret;\n    }\n    friend std::ostream &operator<<(std::ostream &os,\
    \ const matrix &x) {\n        os << \"[(\" << x.H << \" * \" << x.W << \" matrix)\"\
    ;\n        os << \"\\n[column sums: \";\n        for (int j = 0; j < x.W; j++)\
    \ {\n            T s = 0;\n            for (int i = 0; i < x.H; i++) s += x.get(i,\
    \ j);\n            os << s << \",\";\n        }\n        os << \"]\";\n      \
    \  for (int i = 0; i < x.H; i++) {\n            os << \"\\n[\";\n            for\
    \ (int j = 0; j < x.W; j++) os << x.get(i, j) << \",\";\n            os << \"\
    ]\";\n        }\n        os << \"]\\n\";\n        return os;\n    }\n    friend\
    \ std::istream &operator>>(std::istream &is, matrix &x) {\n        for (auto &v\
    \ : x.elem) is >> v;\n        return is;\n    }\n};\n\n\n// Fibonacci numbers\
    \ f(n) = af(n - 1) + bf(n - 2)\n// Example (a = b = 1): 0=>1, 1=>1, 2=>2, 3=>3,\
    \ 4=>5, ...\ntemplate <typename T>\nT Fibonacci(long long int k, int a = 1, int\
    \ b = 1)\n{\n    matrix<T> mat(2, 2);\n    mat[0][1] = 1;\n    mat[1][0] = b;\n\
    \    mat[1][1] = a;\n    return mat.pow(k + 1)[0][1];\n}\n#line 3 \"linear_algebra_matrix/system_of_linear_equations.hpp\"\
    \n#include <utility>\n#line 5 \"linear_algebra_matrix/system_of_linear_equations.hpp\"\
    \n\n// CUT begin\n// Solve Ax = b for T = ModInt<PRIME>\n// - retval: {one of\
    \ the solution, {freedoms}} (if solution exists)\n//           {{}, {}} (otherwise)\n\
    // Complexity:\n// - Yield one of the possible solutions: O(H^2 W) (H: # of eqs.,\
    \ W: # of variables)\n// - Enumerate all of the bases: O(HW(H + W))\ntemplate\
    \ <typename T>\nstd::pair<std::vector<T>, std::vector<std::vector<T>>>\nsystem_of_linear_equations(matrix<T>\
    \ A, std::vector<T> b)\n{\n    int H = A.H, W = A.W;\n    matrix<T> M(H, W + 1);\n\
    \    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) M[i][j]\
    \ = A[i][j];\n        M[i][W] = b[i];\n    }\n    M = M.gauss_jordan();\n    std::vector<int>\
    \ ss(W, -1);\n    for (int i = 0; i < H; i++) {\n        int j = 0;\n        while\
    \ (j <= W and M[i][j] == 0) j++;\n        if (j == W) { // No solution\n     \
    \       return {{}, {}};\n        }\n        if (j < W) ss[j] = i;\n    }\n  \
    \  std::vector<T> x(W);\n    std::vector<std::vector<T>> D;\n    for (int j =\
    \ 0; j < W; j++) {\n        if (ss[j] == -1) {\n            std::vector<T> d(W);\n\
    \            d[j] = 1;\n            for (int jj = 0; jj < j; jj++) if (ss[jj]\
    \ != -1) d[jj] = -M[ss[jj]][j] / M[ss[jj]][jj];\n            D.emplace_back(d);\n\
    \        }\n        else x[j] = M[ss[j]][W] / M[ss[j]][j];\n    }\n    return\
    \ std::make_pair(x, D);\n}\n"
  code: "#pragma once\n#include \"linear_algebra_matrix/linalg_modint.hpp\"\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// Solve Ax = b for T = ModInt<PRIME>\n\
    // - retval: {one of the solution, {freedoms}} (if solution exists)\n//      \
    \     {{}, {}} (otherwise)\n// Complexity:\n// - Yield one of the possible solutions:\
    \ O(H^2 W) (H: # of eqs., W: # of variables)\n// - Enumerate all of the bases:\
    \ O(HW(H + W))\ntemplate <typename T>\nstd::pair<std::vector<T>, std::vector<std::vector<T>>>\n\
    system_of_linear_equations(matrix<T> A, std::vector<T> b)\n{\n    int H = A.H,\
    \ W = A.W;\n    matrix<T> M(H, W + 1);\n    for (int i = 0; i < H; i++) {\n  \
    \      for (int j = 0; j < W; j++) M[i][j] = A[i][j];\n        M[i][W] = b[i];\n\
    \    }\n    M = M.gauss_jordan();\n    std::vector<int> ss(W, -1);\n    for (int\
    \ i = 0; i < H; i++) {\n        int j = 0;\n        while (j <= W and M[i][j]\
    \ == 0) j++;\n        if (j == W) { // No solution\n            return {{}, {}};\n\
    \        }\n        if (j < W) ss[j] = i;\n    }\n    std::vector<T> x(W);\n \
    \   std::vector<std::vector<T>> D;\n    for (int j = 0; j < W; j++) {\n      \
    \  if (ss[j] == -1) {\n            std::vector<T> d(W);\n            d[j] = 1;\n\
    \            for (int jj = 0; jj < j; jj++) if (ss[jj] != -1) d[jj] = -M[ss[jj]][j]\
    \ / M[ss[jj]][jj];\n            D.emplace_back(d);\n        }\n        else x[j]\
    \ = M[ss[j]][W] / M[ss[j]][j];\n    }\n    return std::make_pair(x, D);\n}\n"
  dependsOn:
  - linear_algebra_matrix/linalg_modint.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/system_of_linear_equations.hpp
  requiredBy: []
  timestamp: '2020-10-15 00:04:43+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - linear_algebra_matrix/test/system_of_linear_equations.test.cpp
documentation_of: linear_algebra_matrix/system_of_linear_equations.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/system_of_linear_equations.hpp
- /library/linear_algebra_matrix/system_of_linear_equations.hpp.html
title: linear_algebra_matrix/system_of_linear_equations.hpp
---
