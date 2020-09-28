---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convolution/convolutive_translation_2d.hpp
    title: convolution/convolutive_translation_2d.hpp
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/coeff_of_rational_function.hpp
    title: formal_power_series/coeff_of_rational_function.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/formal_power_series.hpp
    title: formal_power_series/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/multipoint_evaluation.hpp
    title: formal_power_series/multipoint_evaluation.hpp
  - icon: ':warning:'
    path: graph-tree/tree_isomorphism.hpp
    title: graph-tree/tree_isomorphism.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: convolution/test/ntt.test.cpp
    title: convolution/test/ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: convolution/test/ntt_arbitrary_mod.test.cpp
    title: convolution/test/ntt_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: convolution/test/subset_convolution.test.cpp
    title: convolution/test/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/bernoulli_number.test.cpp
    title: formal_power_series/test/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/coeff_of_rational_function.test.cpp
    title: formal_power_series/test/coeff_of_rational_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/division_number.test.cpp
    title: formal_power_series/test/division_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_exp.test.cpp
    title: formal_power_series/test/fps_exp.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_exp_modintruntime.test.cpp
    title: formal_power_series/test/fps_exp_modintruntime.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_inv.test.cpp
    title: formal_power_series/test/fps_inv.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_log.test.cpp
    title: formal_power_series/test/fps_log.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_pow.test.cpp
    title: formal_power_series/test/fps_pow.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_sqrt.test.cpp
    title: formal_power_series/test/fps_sqrt.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_sqrt_modintruntime.test.cpp
    title: formal_power_series/test/fps_sqrt_modintruntime.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/kitamasa.test.cpp
    title: formal_power_series/test/kitamasa.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp
    title: formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/polynomial_interpolation.test.cpp
    title: formal_power_series/test/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sharp_p_subset_sum.test.cpp
    title: formal_power_series/test/sharp_p_subset_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
    title: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
    title: linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
    title: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linear_recurrence.test.cpp
    title: linear_algebra_matrix/test/linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/system_of_linear_equations.test.cpp
    title: linear_algebra_matrix/test/system_of_linear_equations.test.cpp
  - icon: ':heavy_check_mark:'
    path: other_data_structures/test/queue_operate_all_composite.test.cpp
    title: other_data_structures/test/queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: random/test/rolling_hash_w_modint.test.cpp
    title: random/test/rolling_hash_w_modint.test.cpp
  - icon: ':x:'
    path: segmenttree/test/point-set-range-composite.test.cpp
    title: segmenttree/test/point-set-range-composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/range-affine-range-sum.test.cpp
    title: segmenttree/test/range-affine-range-sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modulus/modint_fixed.hpp\"\n#include <iostream>\n#include\
    \ <vector>\n#include <set>\n\n// CUT begin\ntemplate <int mod>\nstruct ModInt\n\
    {\n    using lint = long long;\n    static int get_mod() { return mod; }\n   \
    \ static int get_primitive_root() {\n        static int primitive_root = 0;\n\
    \        if (!primitive_root) {\n            primitive_root = [&](){\n       \
    \         std::set<int> fac;\n                int v = mod - 1;\n             \
    \   for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i), v /= i;\n\
    \                if (v > 1) fac.insert(v);\n                for (int g = 1; g\
    \ < mod; g++) {\n                    bool ok = true;\n                    for\
    \ (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false; break;\
    \ }\n                    if (ok) return g;\n                }\n              \
    \  return -1;\n            }();\n        }\n        return primitive_root;\n \
    \   }\n    int val;\n    constexpr ModInt() : val(0) {}\n    constexpr ModInt\
    \ &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }\n    constexpr\
    \ ModInt(lint v) { _setval(v % mod + mod); }\n    explicit operator bool() const\
    \ { return val != 0; }\n    constexpr ModInt operator+(const ModInt &x) const\
    \ { return ModInt()._setval((lint)val + x.val); }\n    constexpr ModInt operator-(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val - x.val + mod); }\n   \
    \ constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ * x.val % mod); }\n    constexpr ModInt operator/(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.inv() % mod); }\n    constexpr ModInt operator-()\
    \ const { return ModInt()._setval(mod - val); }\n    constexpr ModInt &operator+=(const\
    \ ModInt &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const\
    \ ModInt &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const\
    \ ModInt &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const\
    \ ModInt &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }\n    friend\
    \ constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod - x.val + mod); }\n    friend constexpr ModInt operator*(lint a, const\
    \ ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }\n    friend constexpr\
    \ ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.inv() % mod); }\n    constexpr bool operator==(const ModInt &x) const {\
    \ return val == x.val; }\n    constexpr bool operator!=(const ModInt &x) const\
    \ { return val != x.val; }\n    bool operator<(const ModInt &x) const { return\
    \ val < x.val; }  // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &x) { os << x.val;  return os; }\n\
    \    constexpr lint power(lint n) const {\n        lint ans = 1, tmp = this->val;\n\
    \        while (n) {\n            if (n & 1) ans = ans * tmp % mod;\n        \
    \    tmp = tmp * tmp % mod;\n            n /= 2;\n        }\n        return ans;\n\
    \    }\n    constexpr lint inv() const { return this->power(mod - 2); }\n    constexpr\
    \ ModInt operator^(lint n) const { return ModInt(this->power(n)); }\n    constexpr\
    \ ModInt &operator^=(lint n) { return *this = *this ^ n; }\n\n    inline ModInt\
    \ fac() const {\n        static std::vector<ModInt> facs;\n        int l0 = facs.size();\n\
    \        if (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
    \ : facs[i - 1] * ModInt(i));\n        return facs[this->val];\n    }\n\n    ModInt\
    \ doublefac() const {\n        lint k = (this->val + 1) / 2;\n        if (this->val\
    \ & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();\n  \
    \      else return ModInt(k).fac() * ModInt(2).power(k);\n    }\n\n    ModInt\
    \ nCr(const ModInt &r) const {\n        if (this->val < r.val) return ModInt(0);\n\
    \        return this->fac() / ((*this - r).fac() * r.fac());\n    }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (power((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.power((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.power(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e -\
    \ j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n\n// constexpr\
    \ lint MOD = 998244353;\n// using mint = ModInt<MOD>;\n"
  code: "#pragma once\n#include <iostream>\n#include <vector>\n#include <set>\n\n\
    // CUT begin\ntemplate <int mod>\nstruct ModInt\n{\n    using lint = long long;\n\
    \    static int get_mod() { return mod; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&](){\n                std::set<int> fac;\n   \
    \             int v = mod - 1;\n                for (lint i = 2; i * i <= v; i++)\
    \ while (v % i == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n\
    \                for (int g = 1; g < mod; g++) {\n                    bool ok\
    \ = true;\n                    for (auto i : fac) if (ModInt(g).power((mod - 1)\
    \ / i) == 1) { ok = false; break; }\n                    if (ok) return g;\n \
    \               }\n                return -1;\n            }();\n        }\n \
    \       return primitive_root;\n    }\n    int val;\n    constexpr ModInt() :\
    \ val(0) {}\n    constexpr ModInt &_setval(lint v) { val = (v >= mod ? v - mod\
    \ : v); return *this; }\n    constexpr ModInt(lint v) { _setval(v % mod + mod);\
    \ }\n    explicit operator bool() const { return val != 0; }\n    constexpr ModInt\
    \ operator+(const ModInt &x) const { return ModInt()._setval((lint)val + x.val);\
    \ }\n    constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + mod); }\n    constexpr ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % mod); }\n    constexpr ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }\n \
    \   constexpr ModInt operator-() const { return ModInt()._setval(mod - val); }\n\
    \    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x;\
    \ }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) { return\
    \ ModInt()._setval(a % mod + x.val); }\n    friend constexpr ModInt operator-(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod - x.val + mod); }\n  \
    \  friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod * x.val % mod); }\n    friend constexpr ModInt operator/(lint a, const\
    \ ModInt &x) { return ModInt()._setval(a % mod * x.inv() % mod); }\n    constexpr\
    \ bool operator==(const ModInt &x) const { return val == x.val; }\n    constexpr\
    \ bool operator!=(const ModInt &x) const { return val != x.val; }\n    bool operator<(const\
    \ ModInt &x) const { return val < x.val; }  // To use std::map<ModInt, T>\n  \
    \  friend std::istream &operator>>(std::istream &is, ModInt &x) { lint t; is >>\
    \ t; x = ModInt(t); return is; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const ModInt &x) { os << x.val;  return os; }\n    constexpr lint power(lint\
    \ n) const {\n        lint ans = 1, tmp = this->val;\n        while (n) {\n  \
    \          if (n & 1) ans = ans * tmp % mod;\n            tmp = tmp * tmp % mod;\n\
    \            n /= 2;\n        }\n        return ans;\n    }\n    constexpr lint\
    \ inv() const { return this->power(mod - 2); }\n    constexpr ModInt operator^(lint\
    \ n) const { return ModInt(this->power(n)); }\n    constexpr ModInt &operator^=(lint\
    \ n) { return *this = *this ^ n; }\n\n    inline ModInt fac() const {\n      \
    \  static std::vector<ModInt> facs;\n        int l0 = facs.size();\n        if\
    \ (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val +\
    \ 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
    \ : facs[i - 1] * ModInt(i));\n        return facs[this->val];\n    }\n\n    ModInt\
    \ doublefac() const {\n        lint k = (this->val + 1) / 2;\n        if (this->val\
    \ & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();\n  \
    \      else return ModInt(k).fac() * ModInt(2).power(k);\n    }\n\n    ModInt\
    \ nCr(const ModInt &r) const {\n        if (this->val < r.val) return ModInt(0);\n\
    \        return this->fac() / ((*this - r).fac() * r.fac());\n    }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (power((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.power((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.power(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e -\
    \ j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n\n// constexpr\
    \ lint MOD = 998244353;\n// using mint = ModInt<MOD>;\n"
  dependsOn: []
  isVerificationFile: false
  path: modulus/modint_fixed.hpp
  requiredBy:
  - formal_power_series/coeff_of_rational_function.hpp
  - formal_power_series/formal_power_series.hpp
  - formal_power_series/multipoint_evaluation.hpp
  - convolution/ntt.hpp
  - convolution/convolutive_translation_2d.hpp
  - graph-tree/tree_isomorphism.hpp
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - segmenttree/test/point-set-range-composite.test.cpp
  - segmenttree/test/range-affine-range-sum.test.cpp
  - formal_power_series/test/fps_pow.test.cpp
  - formal_power_series/test/polynomial_interpolation.test.cpp
  - formal_power_series/test/fps_inv.test.cpp
  - formal_power_series/test/coeff_of_rational_function.test.cpp
  - formal_power_series/test/fps_exp_modintruntime.test.cpp
  - formal_power_series/test/fps_exp.test.cpp
  - formal_power_series/test/kitamasa.test.cpp
  - formal_power_series/test/sharp_p_subset_sum.test.cpp
  - formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp
  - formal_power_series/test/bernoulli_number.test.cpp
  - formal_power_series/test/division_number.test.cpp
  - formal_power_series/test/fps_sqrt.test.cpp
  - formal_power_series/test/fps_log.test.cpp
  - formal_power_series/test/fps_sqrt_modintruntime.test.cpp
  - convolution/test/subset_convolution.test.cpp
  - convolution/test/ntt.test.cpp
  - convolution/test/ntt_arbitrary_mod.test.cpp
  - other_data_structures/test/queue_operate_all_composite.test.cpp
  - random/test/rolling_hash_w_modint.test.cpp
  - linear_algebra_matrix/test/system_of_linear_equations.test.cpp
  - linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  - linear_algebra_matrix/test/linear_recurrence.test.cpp
  - linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
  - linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
documentation_of: modulus/modint_fixed.hpp
layout: document
redirect_from:
- /library/modulus/modint_fixed.hpp
- /library/modulus/modint_fixed.hpp.html
title: modulus/modint_fixed.hpp
---
