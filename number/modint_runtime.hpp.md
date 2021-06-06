---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: convolution/test/ntt.test.cpp
    title: convolution/test/ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: convolution/test/ntt_arbitrary_mod.test.cpp
    title: convolution/test/ntt_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_exp_modintruntime.test.cpp
    title: formal_power_series/test/fps_exp_modintruntime.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_sqrt_modintruntime.test.cpp
    title: formal_power_series/test/fps_sqrt_modintruntime.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/chromatic_number.test.cpp
    title: graph/test/chromatic_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
    title: linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
    title: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/montmort_number_mod.test.cpp
    title: number/test/montmort_number_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/sqrt_modint_runtime.test.cpp
    title: number/test/sqrt_modint_runtime.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/modint_runtime.hpp\"\n#include <iostream>\n#include\
    \ <set>\n#include <vector>\n\n// CUT begin\nstruct ModIntRuntime {\nprivate:\n\
    \    static int md;\n\npublic:\n    using lint = long long;\n    static int mod()\
    \ { return md; }\n    int val;\n    static std::vector<ModIntRuntime> &facs()\
    \ {\n        static std::vector<ModIntRuntime> facs_;\n        return facs_;\n\
    \    }\n    static int &get_primitive_root() {\n        static int primitive_root_\
    \ = 0;\n        if (!primitive_root_) {\n            primitive_root_ = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModIntRuntime(g).power((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root_;\n    }\n    static void set_mod(const int\
    \ &m) {\n        if (md != m) facs().clear();\n        md = m;\n        get_primitive_root()\
    \ = 0;\n    }\n    ModIntRuntime &_setval(lint v) {\n        val = (v >= md ?\
    \ v - md : v);\n        return *this;\n    }\n    ModIntRuntime() : val(0) {}\n\
    \    ModIntRuntime(lint v) { _setval(v % md + md); }\n    explicit operator bool()\
    \ const { return val != 0; }\n    ModIntRuntime operator+(const ModIntRuntime\
    \ &x) const {\n        return ModIntRuntime()._setval((lint)val + x.val);\n  \
    \  }\n    ModIntRuntime operator-(const ModIntRuntime &x) const {\n        return\
    \ ModIntRuntime()._setval((lint)val - x.val + md);\n    }\n    ModIntRuntime operator*(const\
    \ ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val\
    \ * x.val % md);\n    }\n    ModIntRuntime operator/(const ModIntRuntime &x) const\
    \ {\n        return ModIntRuntime()._setval((lint)val * x.inv() % md);\n    }\n\
    \    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md - val);\
    \ }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this = *this\
    \ + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return *this\
    \ = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x) { return\
    \ *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime &x)\
    \ { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md + x.val);\n\
    \    }\n    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) {\n\
    \        return ModIntRuntime()._setval(a % md - x.val + md);\n    }\n    friend\
    \ ModIntRuntime operator*(lint a, const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a\
    \ % md * x.val % md);\n    }\n    friend ModIntRuntime operator/(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md * x.inv()\
    \ % md);\n    }\n    bool operator==(const ModIntRuntime &x) const { return val\
    \ == x.val; }\n    bool operator!=(const ModIntRuntime &x) const { return val\
    \ != x.val; }\n    bool operator<(const ModIntRuntime &x) const { return val <\
    \ x.val; } // To use std::map<ModIntRuntime, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModIntRuntime &x) {\n        lint t;\n        return is >> t, x = ModIntRuntime(t),\
    \ is;\n    }\n    friend std::ostream &operator<<(std::ostream &os, const ModIntRuntime\
    \ &x) { return os << x.val; }\n\n    lint power(lint n) const {\n        lint\
    \ ans = 1, tmp = this->val;\n        while (n) {\n            if (n & 1) ans =\
    \ ans * tmp % md;\n            tmp = tmp * tmp % md;\n            n /= 2;\n  \
    \      }\n        return ans;\n    }\n    ModIntRuntime pow(lint n) const { return\
    \ power(n); }\n    lint inv() const { return this->power(md - 2); }\n\n    ModIntRuntime\
    \ fac() const {\n        int l0 = facs().size();\n        if (l0 > this->val)\
    \ return facs()[this->val];\n\n        facs().resize(this->val + 1);\n       \
    \ for (int i = l0; i <= this->val; i++)\n            facs()[i] = (i == 0 ? ModIntRuntime(1)\
    \ : facs()[i - 1] * ModIntRuntime(i));\n        return facs()[this->val];\n  \
    \  }\n\n    ModIntRuntime doublefac() const {\n        lint k = (this->val + 1)\
    \ / 2;\n        return (this->val & 1) ? ModIntRuntime(k * 2).fac() / (ModIntRuntime(2).pow(k)\
    \ * ModIntRuntime(k).fac())\n                               : ModIntRuntime(k).fac()\
    \ * ModIntRuntime(2).pow(k);\n    }\n\n    ModIntRuntime nCr(const ModIntRuntime\
    \ &r) const {\n        return (this->val < r.val) ? ModIntRuntime(0) : this->fac()\
    \ / ((*this - r).fac() * r.fac());\n    }\n\n    ModIntRuntime sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (power((md - 1) / 2) != 1) return 0;\n        ModIntRuntime b = 1;\n       \
    \ while (b.power((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n\
    \        while (m % 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModIntRuntime\
    \ z = b.power(m);\n        while (y != 1) {\n            int j = 0;\n        \
    \    ModIntRuntime t = y;\n            while (t != 1) j++, t *= t;\n         \
    \   z = z.power(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n  \
    \          e = j;\n        }\n        return ModIntRuntime(std::min(x.val, md\
    \ - x.val));\n    }\n};\nint ModIntRuntime::md = 1;\n"
  code: "#pragma once\n#include <iostream>\n#include <set>\n#include <vector>\n\n\
    // CUT begin\nstruct ModIntRuntime {\nprivate:\n    static int md;\n\npublic:\n\
    \    using lint = long long;\n    static int mod() { return md; }\n    int val;\n\
    \    static std::vector<ModIntRuntime> &facs() {\n        static std::vector<ModIntRuntime>\
    \ facs_;\n        return facs_;\n    }\n    static int &get_primitive_root() {\n\
    \        static int primitive_root_ = 0;\n        if (!primitive_root_) {\n  \
    \          primitive_root_ = [&]() {\n                std::set<int> fac;\n   \
    \             int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModIntRuntime(g).power((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root_;\n    }\n    static void set_mod(const int &m) {\n        if\
    \ (md != m) facs().clear();\n        md = m;\n        get_primitive_root() = 0;\n\
    \    }\n    ModIntRuntime &_setval(lint v) {\n        val = (v >= md ? v - md\
    \ : v);\n        return *this;\n    }\n    ModIntRuntime() : val(0) {}\n    ModIntRuntime(lint\
    \ v) { _setval(v % md + md); }\n    explicit operator bool() const { return val\
    \ != 0; }\n    ModIntRuntime operator+(const ModIntRuntime &x) const {\n     \
    \   return ModIntRuntime()._setval((lint)val + x.val);\n    }\n    ModIntRuntime\
    \ operator-(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val\
    \ - x.val + md);\n    }\n    ModIntRuntime operator*(const ModIntRuntime &x) const\
    \ {\n        return ModIntRuntime()._setval((lint)val * x.val % md);\n    }\n\
    \    ModIntRuntime operator/(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val\
    \ * x.inv() % md);\n    }\n    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md\
    \ - val); }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this\
    \ = *this + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return\
    \ *this = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x)\
    \ { return *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime\
    \ &x) { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a,\
    \ const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md + x.val);\n\
    \    }\n    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) {\n\
    \        return ModIntRuntime()._setval(a % md - x.val + md);\n    }\n    friend\
    \ ModIntRuntime operator*(lint a, const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a\
    \ % md * x.val % md);\n    }\n    friend ModIntRuntime operator/(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md * x.inv()\
    \ % md);\n    }\n    bool operator==(const ModIntRuntime &x) const { return val\
    \ == x.val; }\n    bool operator!=(const ModIntRuntime &x) const { return val\
    \ != x.val; }\n    bool operator<(const ModIntRuntime &x) const { return val <\
    \ x.val; } // To use std::map<ModIntRuntime, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModIntRuntime &x) {\n        lint t;\n        return is >> t, x = ModIntRuntime(t),\
    \ is;\n    }\n    friend std::ostream &operator<<(std::ostream &os, const ModIntRuntime\
    \ &x) { return os << x.val; }\n\n    lint power(lint n) const {\n        lint\
    \ ans = 1, tmp = this->val;\n        while (n) {\n            if (n & 1) ans =\
    \ ans * tmp % md;\n            tmp = tmp * tmp % md;\n            n /= 2;\n  \
    \      }\n        return ans;\n    }\n    ModIntRuntime pow(lint n) const { return\
    \ power(n); }\n    lint inv() const { return this->power(md - 2); }\n\n    ModIntRuntime\
    \ fac() const {\n        int l0 = facs().size();\n        if (l0 > this->val)\
    \ return facs()[this->val];\n\n        facs().resize(this->val + 1);\n       \
    \ for (int i = l0; i <= this->val; i++)\n            facs()[i] = (i == 0 ? ModIntRuntime(1)\
    \ : facs()[i - 1] * ModIntRuntime(i));\n        return facs()[this->val];\n  \
    \  }\n\n    ModIntRuntime doublefac() const {\n        lint k = (this->val + 1)\
    \ / 2;\n        return (this->val & 1) ? ModIntRuntime(k * 2).fac() / (ModIntRuntime(2).pow(k)\
    \ * ModIntRuntime(k).fac())\n                               : ModIntRuntime(k).fac()\
    \ * ModIntRuntime(2).pow(k);\n    }\n\n    ModIntRuntime nCr(const ModIntRuntime\
    \ &r) const {\n        return (this->val < r.val) ? ModIntRuntime(0) : this->fac()\
    \ / ((*this - r).fac() * r.fac());\n    }\n\n    ModIntRuntime sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (power((md - 1) / 2) != 1) return 0;\n        ModIntRuntime b = 1;\n       \
    \ while (b.power((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n\
    \        while (m % 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModIntRuntime\
    \ z = b.power(m);\n        while (y != 1) {\n            int j = 0;\n        \
    \    ModIntRuntime t = y;\n            while (t != 1) j++, t *= t;\n         \
    \   z = z.power(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n  \
    \          e = j;\n        }\n        return ModIntRuntime(std::min(x.val, md\
    \ - x.val));\n    }\n};\nint ModIntRuntime::md = 1;\n"
  dependsOn: []
  isVerificationFile: false
  path: number/modint_runtime.hpp
  requiredBy: []
  timestamp: '2021-06-06 14:54:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
  - linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  - convolution/test/ntt.test.cpp
  - convolution/test/ntt_arbitrary_mod.test.cpp
  - formal_power_series/test/fps_sqrt_modintruntime.test.cpp
  - formal_power_series/test/fps_exp_modintruntime.test.cpp
  - number/test/montmort_number_mod.test.cpp
  - number/test/sqrt_modint_runtime.test.cpp
  - graph/test/chromatic_number.test.cpp
documentation_of: number/modint_runtime.hpp
layout: document
redirect_from:
- /library/number/modint_runtime.hpp
- /library/number/modint_runtime.hpp.html
title: number/modint_runtime.hpp
---
