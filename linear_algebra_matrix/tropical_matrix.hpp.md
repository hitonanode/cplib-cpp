---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/ddcc2020-final/submissions/16941701>
  bundledCode: "#line 1 \"linear_algebra_matrix/tropical_matrix.hpp\"\n#include <cassert>\n\
    #include <iostream>\n#include <limits>\n#include <vector>\n\n// CUT begin\n//\
    \ Tropical matrix\n// Verify: <https://atcoder.jp/contests/ddcc2020-final/submissions/16941701>\n\
    // A[j][i] = \"length of shortest parh i -> j of graph A\"\n// (B * A)[k][i] =\
    \ min_j (B[k][j] + A[j][i])\ntemplate <typename T>\nstruct tropical_matrix\n{\n\
    \    constexpr static T INF = std::numeric_limits<T>::max() / 2;\n    static bool\
    \ _chmin(T &m, const T q)\n    {\n        if (m > q)\n        {\n            m\
    \ = q;\n            return true;\n        }\n        return false;\n    }\n  \
    \  int H, W;\n    std::vector<T> elem;\n    typename std::vector<T>::iterator\
    \ operator[](int i) { return elem.begin() + i * W; }\n    inline T &at(int i,\
    \ int j) { return elem[i * W + j]; }\n    inline T get(int i, int j) const { return\
    \ elem[i * W + j]; }\n    operator std::vector<std::vector<T>>() const {\n   \
    \     std::vector<std::vector<T>> ret(H);\n        for (int i = 0; i < H; i++)\
    \ std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));\n\
    \        return ret;\n    }\n\n    tropical_matrix(int H = 0, int W = 0) : H(H),\
    \ W(W), elem(H * W, INF) {}\n    tropical_matrix(const std::vector<std::vector<T>>\
    \ &d) : H(d.size()), W(d.size() ? d[0].size() : 0)\n    {\n        for (auto &raw\
    \ : d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));\n    }\n\n\
    \    static tropical_matrix Identity(int N)\n    {\n        tropical_matrix ret(N,\
    \ N);\n        for (int i = 0; i < N; i++) ret.at(i, i) = 0;\n        return ret;\n\
    \    }\n\n    tropical_matrix operator+(const tropical_matrix &r) const\n    {\n\
    \        tropical_matrix ret(H, W);\n        for (int i = 0; i < H * W; i++) _chmin(ret.elem[i],\
    \ r.elem[i]);\n        return ret;\n    }\n    tropical_matrix operator*(const\
    \ tropical_matrix &r) const\n    {\n        tropical_matrix ret(H, r.W);\n   \
    \     for (int i = 0; i < H; i++) {\n            for (int k = 0; k < W; k++) {\n\
    \                for (int j = 0; j < r.W; j++) {\n                    _chmin(ret.at(i,\
    \ j), this->get(i, k) + r.get(k, j));\n                }\n            }\n    \
    \    }\n        return ret;\n    }\n    tropical_matrix &operator+=(const tropical_matrix\
    \ &r) { return *this = *this + r; }\n    tropical_matrix &operator*=(const tropical_matrix\
    \ &r) { return *this = *this * r; }\n    bool operator==(const tropical_matrix\
    \ &r) const { return H == r.H and W == r.W and elem == r.elem; }\n    bool operator!=(const\
    \ tropical_matrix &r) const { return H != r.H or W != r.W or elem != r.elem; }\n\
    \    bool operator<(const tropical_matrix &r) const { return elem < r.elem; }\n\
    \    tropical_matrix pow(int64_t n) const\n    {\n        tropical_matrix ret\
    \ = Identity(H);\n        if (n == 0) return ret;\n        for (int i = 63 - __builtin_clzll(n);\
    \ i >= 0; i--) {\n            ret *= ret;\n            if ((n >> i) & 1) ret *=\
    \ (*this);\n        }\n        return ret;\n    }\n    tropical_matrix transpose()\
    \ const\n    {\n        tropical_matrix ret(W, H);\n        for (int i = 0; i\
    \ < H; i++) for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i, j);\n    \
    \    return ret;\n    }\n    friend std::vector<T> operator*(const tropical_matrix\
    \ &m, const std::vector<T> &v)\n    {\n        assert(m.W == int(v.size()));\n\
    \        std::vector<T> ret(m.H, m.INF);\n        for (int i = 0; i < m.H; i++)\
    \ {\n            for (int j = 0; j < m.W; j++) {\n                _chmin(ret[i],\
    \ m.get(i, j) + v[j]);\n            }\n        }\n        return ret;\n    }\n\
    \    friend std::vector<T> operator*(const std::vector<T> &v, const tropical_matrix\
    \ &m)\n    {\n        assert(int(v.size()) == m.H);\n        std::vector<T> ret(m.W,\
    \ m.INF);\n        for (int i = 0; i < m.H; i++) {\n            for (int j = 0;\
    \ j < m.W; j++) {\n                _chmin(ret[j], v[i] + m.get(i, j));\n     \
    \       }\n        }\n        return ret;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const tropical_matrix &x)\n    {\n        os << \"[(\" << x.H << \" * \"\
    \ << x.W << \" matrix)\";\n        for (int i = 0; i < x.H; i++) {\n         \
    \   os << \"\\n[\";\n            for (int j = 0; j < x.W; j++) os << x.get(i,\
    \ j) << \",\";\n            os << \"]\";\n        }\n        os << \"]\\n\";\n\
    \        return os;\n    }\n    friend std::istream &operator>>(std::istream &is,\
    \ tropical_matrix &x)\n    {\n        for (auto &v : x.elem) is >> v;\n      \
    \  return is;\n    }\n};\n"
  code: "#include <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n// CUT begin\n// Tropical matrix\n// Verify: <https://atcoder.jp/contests/ddcc2020-final/submissions/16941701>\n\
    // A[j][i] = \"length of shortest parh i -> j of graph A\"\n// (B * A)[k][i] =\
    \ min_j (B[k][j] + A[j][i])\ntemplate <typename T>\nstruct tropical_matrix\n{\n\
    \    constexpr static T INF = std::numeric_limits<T>::max() / 2;\n    static bool\
    \ _chmin(T &m, const T q)\n    {\n        if (m > q)\n        {\n            m\
    \ = q;\n            return true;\n        }\n        return false;\n    }\n  \
    \  int H, W;\n    std::vector<T> elem;\n    typename std::vector<T>::iterator\
    \ operator[](int i) { return elem.begin() + i * W; }\n    inline T &at(int i,\
    \ int j) { return elem[i * W + j]; }\n    inline T get(int i, int j) const { return\
    \ elem[i * W + j]; }\n    operator std::vector<std::vector<T>>() const {\n   \
    \     std::vector<std::vector<T>> ret(H);\n        for (int i = 0; i < H; i++)\
    \ std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));\n\
    \        return ret;\n    }\n\n    tropical_matrix(int H = 0, int W = 0) : H(H),\
    \ W(W), elem(H * W, INF) {}\n    tropical_matrix(const std::vector<std::vector<T>>\
    \ &d) : H(d.size()), W(d.size() ? d[0].size() : 0)\n    {\n        for (auto &raw\
    \ : d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));\n    }\n\n\
    \    static tropical_matrix Identity(int N)\n    {\n        tropical_matrix ret(N,\
    \ N);\n        for (int i = 0; i < N; i++) ret.at(i, i) = 0;\n        return ret;\n\
    \    }\n\n    tropical_matrix operator+(const tropical_matrix &r) const\n    {\n\
    \        tropical_matrix ret(H, W);\n        for (int i = 0; i < H * W; i++) _chmin(ret.elem[i],\
    \ r.elem[i]);\n        return ret;\n    }\n    tropical_matrix operator*(const\
    \ tropical_matrix &r) const\n    {\n        tropical_matrix ret(H, r.W);\n   \
    \     for (int i = 0; i < H; i++) {\n            for (int k = 0; k < W; k++) {\n\
    \                for (int j = 0; j < r.W; j++) {\n                    _chmin(ret.at(i,\
    \ j), this->get(i, k) + r.get(k, j));\n                }\n            }\n    \
    \    }\n        return ret;\n    }\n    tropical_matrix &operator+=(const tropical_matrix\
    \ &r) { return *this = *this + r; }\n    tropical_matrix &operator*=(const tropical_matrix\
    \ &r) { return *this = *this * r; }\n    bool operator==(const tropical_matrix\
    \ &r) const { return H == r.H and W == r.W and elem == r.elem; }\n    bool operator!=(const\
    \ tropical_matrix &r) const { return H != r.H or W != r.W or elem != r.elem; }\n\
    \    bool operator<(const tropical_matrix &r) const { return elem < r.elem; }\n\
    \    tropical_matrix pow(int64_t n) const\n    {\n        tropical_matrix ret\
    \ = Identity(H);\n        if (n == 0) return ret;\n        for (int i = 63 - __builtin_clzll(n);\
    \ i >= 0; i--) {\n            ret *= ret;\n            if ((n >> i) & 1) ret *=\
    \ (*this);\n        }\n        return ret;\n    }\n    tropical_matrix transpose()\
    \ const\n    {\n        tropical_matrix ret(W, H);\n        for (int i = 0; i\
    \ < H; i++) for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i, j);\n    \
    \    return ret;\n    }\n    friend std::vector<T> operator*(const tropical_matrix\
    \ &m, const std::vector<T> &v)\n    {\n        assert(m.W == int(v.size()));\n\
    \        std::vector<T> ret(m.H, m.INF);\n        for (int i = 0; i < m.H; i++)\
    \ {\n            for (int j = 0; j < m.W; j++) {\n                _chmin(ret[i],\
    \ m.get(i, j) + v[j]);\n            }\n        }\n        return ret;\n    }\n\
    \    friend std::vector<T> operator*(const std::vector<T> &v, const tropical_matrix\
    \ &m)\n    {\n        assert(int(v.size()) == m.H);\n        std::vector<T> ret(m.W,\
    \ m.INF);\n        for (int i = 0; i < m.H; i++) {\n            for (int j = 0;\
    \ j < m.W; j++) {\n                _chmin(ret[j], v[i] + m.get(i, j));\n     \
    \       }\n        }\n        return ret;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const tropical_matrix &x)\n    {\n        os << \"[(\" << x.H << \" * \"\
    \ << x.W << \" matrix)\";\n        for (int i = 0; i < x.H; i++) {\n         \
    \   os << \"\\n[\";\n            for (int j = 0; j < x.W; j++) os << x.get(i,\
    \ j) << \",\";\n            os << \"]\";\n        }\n        os << \"]\\n\";\n\
    \        return os;\n    }\n    friend std::istream &operator>>(std::istream &is,\
    \ tropical_matrix &x)\n    {\n        for (auto &v : x.elem) is >> v;\n      \
    \  return is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/tropical_matrix.hpp
  requiredBy: []
  timestamp: '2020-09-21 23:53:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: linear_algebra_matrix/tropical_matrix.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/tropical_matrix.hpp
- /library/linear_algebra_matrix/tropical_matrix.hpp.html
title: linear_algebra_matrix/tropical_matrix.hpp
---
