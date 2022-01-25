---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/matrix.hpp
    title: linear_algebra_matrix/matrix.hpp
  - icon: ':heavy_check_mark:'
    path: number/min_max_semiring.hpp
    title: "Min-max semiring\uFF08(min, max) \u534A\u74B0\uFF09"
  - icon: ':heavy_check_mark:'
    path: number/min_plus_semiring.hpp
    title: "Min-plus semiring / tropical semiring\uFF08(min, +) \u534A\u74B0\u30FB\
      \u30C8\u30ED\u30D4\u30AB\u30EB\u534A\u74B0\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1340
    links:
    - https://yukicoder.me/problems/no/1340
  bundledCode: "#line 1 \"linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1340\"\n\n#line 1 \"number/min_max_semiring.hpp\"\
    \n#include <limits>\n\n// min-max \u534A\u74B0\uFF08\u52A0\u6CD5\u304C min, \u4E57\
    \u6CD5\u304C max, \u96F6\u5143\u304C INF, \u5358\u4F4D\u5143\u304C -INF\uFF09\n\
    // Verified: abc236g\ntemplate <class T> struct min_max_semiring {\n    T val;\n\
    \    min_max_semiring() : val(std::numeric_limits<T>::max()) {\n        static_assert(std::numeric_limits<T>::max()\
    \ > 0,\n                      \"std::numeric_limits<>::max() must be properly\
    \ defined\");\n    }\n    min_max_semiring(T x) : val(x) {}\n    static min_max_semiring\
    \ id() { return T(std::numeric_limits<T>::min()); }\n    static min_max_semiring\
    \ max() { return T(); }\n    min_max_semiring operator+(const min_max_semiring\
    \ &r) const {\n        return (this->val > r.val ? r.val : this->val);\n    }\n\
    \    min_max_semiring &operator+=(const min_max_semiring &r) { return *this =\
    \ *this + r; }\n    min_max_semiring operator*(const min_max_semiring &r) const\
    \ {\n        return (this->val < r.val ? r.val : this->val);\n    }\n    min_max_semiring\
    \ &operator*=(const min_max_semiring &r) { return *this = *this * r; }\n    bool\
    \ operator==(const min_max_semiring &r) const { return this->val == r.val; }\n\
    \    bool operator!=(const min_max_semiring &r) const { return !(*this == r);\
    \ }\n    template <class OStream> friend OStream &operator<<(OStream &os, const\
    \ min_max_semiring &x) {\n        return os << x.val;\n    }\n};\n#line 2 \"number/min_plus_semiring.hpp\"\
    \n\n// min-plus \u534A\u74B0\u30FB\u30C8\u30ED\u30D4\u30AB\u30EB\u534A\u74B0\uFF08\
    \u52A0\u6CD5\u304C min, \u4E57\u6CD5\u304C plus, \u96F6\u5143\u304C INF, \u5358\
    \u4F4D\u5143\u304C 0\uFF09\n// INF = numeric_limits<T>::max() / 2 \u3092\u8D85\
    \u3048\u305F\u3089 INF \u306B clamp \u3059\u308B\n// Verified: https://yukicoder.me/problems/no/1340\n\
    template <class T> struct min_plus_semiring {\n    T val;\n    static const T\
    \ _T_inf() {\n        static_assert(std::numeric_limits<T>::max() > 0,\n     \
    \                 \"std::numeric_limits<>::max() must be properly defined\");\n\
    \        return std::numeric_limits<T>::max() / 2;\n    }\n    min_plus_semiring()\
    \ : val(_T_inf()) {}\n    min_plus_semiring(T x) : val(x) {}\n    static min_plus_semiring\
    \ id() { return min_plus_semiring(0); }\n    min_plus_semiring operator+(const\
    \ min_plus_semiring &r) const {\n        return (this->val > r.val ? r.val : this->val);\n\
    \    }\n    min_plus_semiring &operator+=(const min_plus_semiring &r) { return\
    \ *this = *this + r; }\n    min_plus_semiring operator*(const min_plus_semiring\
    \ &r) const {\n        if (this->val == _T_inf() or r.val == _T_inf()) return\
    \ min_plus_semiring();\n        T tmp = this->val + r.val; // Watch out for overflow\n\
    \        return _T_inf() < tmp ? min_plus_semiring() : min_plus_semiring(tmp);\n\
    \    }\n    min_plus_semiring &operator*=(const min_plus_semiring &r) { return\
    \ *this = *this * r; }\n    bool operator==(const min_plus_semiring &r) const\
    \ { return this->val == r.val; }\n    bool operator!=(const min_plus_semiring\
    \ &r) const { return !(*this == r); }\n    bool operator<(const min_plus_semiring\
    \ &x) const { return this->val < x.val; }\n    bool operator>(const min_plus_semiring\
    \ &x) const { return this->val > x.val; }\n    template <class OStream> friend\
    \ OStream &operator<<(OStream &os, const min_plus_semiring &x) {\n        return\
    \ os << x.val;\n    }\n};\n#line 2 \"linear_algebra_matrix/matrix.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <iterator>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\nstruct has_id_method_impl\
    \ {\n    template <class T_> static auto check(T_ *) -> decltype(T_::id(), std::true_type());\n\
    \    template <class T_> static auto check(...) -> std::false_type;\n};\ntemplate\
    \ <class T_> struct has_id_method : decltype(has_id_method_impl::check<T_>(nullptr))\
    \ {};\n\ntemplate <typename T> struct matrix {\n    int H, W;\n    std::vector<T>\
    \ elem;\n    typename std::vector<T>::iterator operator[](int i) { return elem.begin()\
    \ + i * W; }\n    inline T &at(int i, int j) { return elem[i * W + j]; }\n   \
    \ inline T get(int i, int j) const { return elem[i * W + j]; }\n    int height()\
    \ const { return H; }\n    int width() const { return W; }\n    std::vector<std::vector<T>>\
    \ vecvec() const {\n        std::vector<std::vector<T>> ret(H);\n        for (int\
    \ i = 0; i < H; i++) {\n            std::copy(elem.begin() + i * W, elem.begin()\
    \ + (i + 1) * W, std::back_inserter(ret[i]));\n        }\n        return ret;\n\
    \    }\n    operator std::vector<std::vector<T>>() const { return vecvec(); }\n\
    \    matrix() = default;\n    matrix(int H, int W) : H(H), W(W), elem(H * W) {}\n\
    \    matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.size() ?\
    \ d[0].size() : 0) {\n        for (auto &raw : d) std::copy(raw.begin(), raw.end(),\
    \ std::back_inserter(elem));\n    }\n\n    template <typename T2, typename std::enable_if<has_id_method<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2::id();\n    }\n   \
    \ template <typename T2, typename std::enable_if<!has_id_method<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2(1);\n    }\n\n    static\
    \ matrix Identity(int N) {\n        matrix ret(N, N);\n        for (int i = 0;\
    \ i < N; i++) ret.at(i, i) = _T_id<T>();\n        return ret;\n    }\n\n    matrix\
    \ operator-() const {\n        matrix ret(H, W);\n        for (int i = 0; i <\
    \ H * W; i++) ret.elem[i] = -elem[i];\n        return ret;\n    }\n    matrix\
    \ operator*(const T &v) const {\n        matrix ret = *this;\n        for (auto\
    \ &x : ret.elem) x *= v;\n        return ret;\n    }\n    matrix operator/(const\
    \ T &v) const {\n        matrix ret = *this;\n        const T vinv = _T_id<T>()\
    \ / v;\n        for (auto &x : ret.elem) x *= vinv;\n        return ret;\n   \
    \ }\n    matrix operator+(const matrix &r) const {\n        matrix ret = *this;\n\
    \        for (int i = 0; i < H * W; i++) ret.elem[i] += r.elem[i];\n        return\
    \ ret;\n    }\n    matrix operator-(const matrix &r) const {\n        matrix ret\
    \ = *this;\n        for (int i = 0; i < H * W; i++) ret.elem[i] -= r.elem[i];\n\
    \        return ret;\n    }\n    matrix operator*(const matrix &r) const {\n \
    \       matrix ret(H, r.W);\n        for (int i = 0; i < H; i++) {\n         \
    \   for (int k = 0; k < W; k++) {\n                for (int j = 0; j < r.W; j++)\
    \ ret.at(i, j) += this->get(i, k) * r.get(k, j);\n            }\n        }\n \
    \       return ret;\n    }\n    matrix &operator*=(const T &v) { return *this\
    \ = *this * v; }\n    matrix &operator/=(const T &v) { return *this = *this /\
    \ v; }\n    matrix &operator+=(const matrix &r) { return *this = *this + r; }\n\
    \    matrix &operator-=(const matrix &r) { return *this = *this - r; }\n    matrix\
    \ &operator*=(const matrix &r) { return *this = *this * r; }\n    bool operator==(const\
    \ matrix &r) const { return H == r.H and W == r.W and elem == r.elem; }\n    bool\
    \ operator!=(const matrix &r) const { return H != r.H or W != r.W or elem != r.elem;\
    \ }\n    bool operator<(const matrix &r) const { return elem < r.elem; }\n   \
    \ matrix pow(int64_t n) const {\n        matrix ret = Identity(H);\n        bool\
    \ ret_is_id = true;\n        if (n == 0) return ret;\n        for (int i = 63\
    \ - __builtin_clzll(n); i >= 0; i--) {\n            if (!ret_is_id) ret *= ret;\n\
    \            if ((n >> i) & 1) ret *= (*this), ret_is_id = false;\n        }\n\
    \        return ret;\n    }\n    std::vector<T> pow_vec(int64_t n, std::vector<T>\
    \ vec) const {\n        matrix x = *this;\n        while (n) {\n            if\
    \ (n & 1) vec = x * vec;\n            x *= x;\n            n >>= 1;\n        }\n\
    \        return vec;\n    };\n    matrix transpose() const {\n        matrix ret(W,\
    \ H);\n        for (int i = 0; i < H; i++) {\n            for (int j = 0; j <\
    \ W; j++) ret.at(j, i) = this->get(i, j);\n        }\n        return ret;\n  \
    \  }\n    // Gauss-Jordan elimination\n    // - Require inverse for every non-zero\
    \ element\n    // - Complexity: O(H^2 W)\n    template <typename T2, typename\
    \ std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>\n    static\
    \ int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {\n        int\
    \ piv = -1;\n        for (int j = h; j < mtr.H; j++) {\n            if (mtr.get(j,\
    \ c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))\n \
    \               piv = j;\n        }\n        return piv;\n    }\n    template\
    \ <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type\
    \ * = nullptr>\n    static int choose_pivot(const matrix<T2> &mtr, int h, int\
    \ c) noexcept {\n        for (int j = h; j < mtr.H; j++) {\n            if (mtr.get(j,\
    \ c) != 0) return j;\n        }\n        return -1;\n    }\n    matrix gauss_jordan()\
    \ const {\n        int c = 0;\n        matrix mtr(*this);\n        std::vector<int>\
    \ ws;\n        ws.reserve(W);\n        for (int h = 0; h < H; h++) {\n       \
    \     if (c == W) break;\n            int piv = choose_pivot(mtr, h, c);\n   \
    \         if (piv == -1) {\n                c++;\n                h--;\n     \
    \           continue;\n            }\n            if (h != piv) {\n          \
    \      for (int w = 0; w < W; w++) {\n                    std::swap(mtr[piv][w],\
    \ mtr[h][w]);\n                    mtr.at(piv, w) *= -1; // To preserve sign of\
    \ determinant\n                }\n            }\n            ws.clear();\n   \
    \         for (int w = c; w < W; w++) {\n                if (mtr.at(h, w) != 0)\
    \ ws.emplace_back(w);\n            }\n            const T hcinv = _T_id<T>() /\
    \ mtr.at(h, c);\n            for (int hh = 0; hh < H; hh++)\n                if\
    \ (hh != h) {\n                    const T coeff = mtr.at(hh, c) * hcinv;\n  \
    \                  for (auto w : ws) mtr.at(hh, w) -= mtr.at(h, w) * coeff;\n\
    \                    mtr.at(hh, c) = 0;\n                }\n            c++;\n\
    \        }\n        return mtr;\n    }\n    int rank_of_gauss_jordan() const {\n\
    \        for (int i = H * W - 1; i >= 0; i--) {\n            if (elem[i] != 0)\
    \ return i / W + 1;\n        }\n        return 0;\n    }\n    T determinant_of_upper_triangle()\
    \ const {\n        T ret = _T_id<T>();\n        for (int i = 0; i < H; i++) ret\
    \ *= get(i, i);\n        return ret;\n    }\n    int inverse() {\n        assert(H\
    \ == W);\n        std::vector<std::vector<T>> ret = Identity(H), tmp = *this;\n\
    \        int rank = 0;\n        for (int i = 0; i < H; i++) {\n            int\
    \ ti = i;\n            while (ti < H and tmp[ti][i] == 0) ti++;\n            if\
    \ (ti == H) {\n                continue;\n            } else {\n             \
    \   rank++;\n            }\n            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);\n\
    \            T inv = _T_id<T>() / tmp[i][i];\n            for (int j = 0; j <\
    \ W; j++) ret[i][j] *= inv;\n            for (int j = i + 1; j < W; j++) tmp[i][j]\
    \ *= inv;\n            for (int h = 0; h < H; h++) {\n                if (i ==\
    \ h) continue;\n                const T c = -tmp[h][i];\n                for (int\
    \ j = 0; j < W; j++) ret[h][j] += ret[i][j] * c;\n                for (int j =\
    \ i + 1; j < W; j++) tmp[h][j] += tmp[i][j] * c;\n            }\n        }\n \
    \       *this = ret;\n        return rank;\n    }\n    friend std::vector<T> operator*(const\
    \ matrix &m, const std::vector<T> &v) {\n        assert(m.W == int(v.size()));\n\
    \        std::vector<T> ret(m.H);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) ret[i] += m.get(i, j) * v[j];\n    \
    \    }\n        return ret;\n    }\n    friend std::vector<T> operator*(const\
    \ std::vector<T> &v, const matrix &m) {\n        assert(int(v.size()) == m.H);\n\
    \        std::vector<T> ret(m.W);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) ret[j] += v[i] * m.get(i, j);\n    \
    \    }\n        return ret;\n    }\n    std::vector<T> prod(const std::vector<T>\
    \ &v) const { return (*this) * v; }\n    std::vector<T> prod_left(const std::vector<T>\
    \ &v) const { return v * (*this); }\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const matrix &x) {\n        os << \"[(\" << x.H <<\
    \ \" * \" << x.W << \" matrix)\";\n        os << \"\\n[column sums: \";\n    \
    \    for (int j = 0; j < x.W; j++) {\n            T s = 0;\n            for (int\
    \ i = 0; i < x.H; i++) s += x.get(i, j);\n            os << s << \",\";\n    \
    \    }\n        os << \"]\";\n        for (int i = 0; i < x.H; i++) {\n      \
    \      os << \"\\n[\";\n            for (int j = 0; j < x.W; j++) os << x.get(i,\
    \ j) << \",\";\n            os << \"]\";\n        }\n        os << \"]\\n\";\n\
    \        return os;\n    }\n    template <class IStream> friend IStream &operator>>(IStream\
    \ &is, matrix &x) {\n        for (auto &v : x.elem) is >> v;\n        return is;\n\
    \    }\n};\n#line 6 \"linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp\"\
    \n\n#line 9 \"linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp\"\n\
    #include <iostream>\n#line 11 \"linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp\"\
    \nusing namespace std;\n\ntemplate <class Semiring> int solve(int N, const vector<pair<int,\
    \ int>> &edges, long long T) {\n    matrix<Semiring> mat(N, N);\n    for (auto\
    \ edge : edges) mat[edge.second][edge.first] = Semiring::id();\n    vector<Semiring>\
    \ initvec(N, Semiring());\n    initvec[0] = Semiring::id();\n    vector<Semiring>\
    \ vec = mat.pow_vec(T, initvec);\n    return count(vec.begin(), vec.end(), Semiring::id());\n\
    }\n\nint main() {\n    int N, M;\n    long long T;\n    cin >> N >> M >> T;\n\
    \    vector<pair<int, int>> edges;\n    while (M--) {\n        int a, b;\n   \
    \     cin >> a >> b;\n        edges.emplace_back(a, b);\n    }\n\n    auto sol1\
    \ = solve<min_max_semiring<int>>(N, edges, T);\n    auto sol2 = solve<min_plus_semiring<int>>(N,\
    \ edges, T);\n    assert(sol1 == sol2);\n    cout << sol1 << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1340\"\n\n#include \"\
    ../../number/min_max_semiring.hpp\"\n#include \"../../number/min_plus_semiring.hpp\"\
    \n#include \"../matrix.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <iostream>\n#include <utility>\nusing namespace std;\n\ntemplate <class Semiring>\
    \ int solve(int N, const vector<pair<int, int>> &edges, long long T) {\n    matrix<Semiring>\
    \ mat(N, N);\n    for (auto edge : edges) mat[edge.second][edge.first] = Semiring::id();\n\
    \    vector<Semiring> initvec(N, Semiring());\n    initvec[0] = Semiring::id();\n\
    \    vector<Semiring> vec = mat.pow_vec(T, initvec);\n    return count(vec.begin(),\
    \ vec.end(), Semiring::id());\n}\n\nint main() {\n    int N, M;\n    long long\
    \ T;\n    cin >> N >> M >> T;\n    vector<pair<int, int>> edges;\n    while (M--)\
    \ {\n        int a, b;\n        cin >> a >> b;\n        edges.emplace_back(a,\
    \ b);\n    }\n\n    auto sol1 = solve<min_max_semiring<int>>(N, edges, T);\n \
    \   auto sol2 = solve<min_plus_semiring<int>>(N, edges, T);\n    assert(sol1 ==\
    \ sol2);\n    cout << sol1 << '\\n';\n}\n"
  dependsOn:
  - number/min_max_semiring.hpp
  - number/min_plus_semiring.hpp
  - linear_algebra_matrix/matrix.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
  requiredBy: []
  timestamp: '2022-01-25 23:27:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
- /verify/linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp.html
title: linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
---
