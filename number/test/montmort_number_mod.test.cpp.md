---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/modint_runtime.hpp
    title: number/modint_runtime.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/montmort_number_mod
    links:
    - https://judge.yosupo.jp/problem/montmort_number_mod
  bundledCode: "#line 1 \"number/test/montmort_number_mod.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n#line 2 \"number/modint_runtime.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \nstruct ModIntRuntime {\nprivate:\n    static int md;\n\npublic:\n    using lint\
    \ = long long;\n    static int mod() { return md; }\n    int val_;\n    static\
    \ std::vector<ModIntRuntime> &facs() {\n        static std::vector<ModIntRuntime>\
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
    \    }\n    ModIntRuntime &_setval(lint v) {\n        val_ = (v >= md ? v - md\
    \ : v);\n        return *this;\n    }\n    int val() const noexcept { return val_;\
    \ }\n    ModIntRuntime() : val_(0) {}\n    ModIntRuntime(lint v) { _setval(v %\
    \ md + md); }\n    explicit operator bool() const { return val_ != 0; }\n    ModIntRuntime\
    \ operator+(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val_\
    \ + x.val_);\n    }\n    ModIntRuntime operator-(const ModIntRuntime &x) const\
    \ {\n        return ModIntRuntime()._setval((lint)val_ - x.val_ + md);\n    }\n\
    \    ModIntRuntime operator*(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    ModIntRuntime operator/(const ModIntRuntime &x)\
    \ const {\n        return ModIntRuntime()._setval((lint)val_ * x.inv().val() %\
    \ md);\n    }\n    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md\
    \ - val_); }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this\
    \ = *this + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return\
    \ *this = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x)\
    \ { return *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime\
    \ &x) { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a,\
    \ const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md + x.val_);\n\
    \    }\n    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) {\n\
    \        return ModIntRuntime()._setval(a % md - x.val_ + md);\n    }\n    friend\
    \ ModIntRuntime operator*(lint a, const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a\
    \ % md * x.val_ % md);\n    }\n    friend ModIntRuntime operator/(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md * x.inv().val()\
    \ % md);\n    }\n    bool operator==(const ModIntRuntime &x) const { return val_\
    \ == x.val_; }\n    bool operator!=(const ModIntRuntime &x) const { return val_\
    \ != x.val_; }\n    bool operator<(const ModIntRuntime &x) const {\n        return\
    \ val_ < x.val_;\n    } // To use std::map<ModIntRuntime, T>\n    friend std::istream\
    \ &operator>>(std::istream &is, ModIntRuntime &x) {\n        lint t;\n       \
    \ return is >> t, x = ModIntRuntime(t), is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const ModIntRuntime &x) {\n        return os << x.val_;\n    }\n\n    lint\
    \ power(lint n) const {\n        lint ans = 1, tmp = this->val_;\n        while\
    \ (n) {\n            if (n & 1) ans = ans * tmp % md;\n            tmp = tmp *\
    \ tmp % md;\n            n /= 2;\n        }\n        return ans;\n    }\n    ModIntRuntime\
    \ pow(lint n) const { return power(n); }\n    ModIntRuntime inv() const { return\
    \ this->pow(md - 2); }\n\n    static ModIntRuntime fac(int n) {\n        assert(n\
    \ >= 0);\n        if (n >= md) return ModIntRuntime(0);\n        int l0 = facs().size();\n\
    \        if (l0 > n) return facs()[n];\n        facs().resize(n + 1);\n      \
    \  for (int i = l0; i <= n; i++)\n            facs()[i] = (i == 0 ? ModIntRuntime(1)\
    \ : facs()[i - 1] * ModIntRuntime(i));\n        return facs()[n];\n    }\n\n \
    \   static ModIntRuntime facinv(int n) { return ModIntRuntime::fac(n).inv(); }\n\
    \n    static ModIntRuntime doublefac(int n) {\n        assert(n >= 0);\n     \
    \   if (n >= md) return ModIntRuntime(0);\n        long long k = (n + 1) / 2;\n\
    \        return (n & 1)\n                   ? ModIntRuntime::fac(k * 2) / (ModIntRuntime(2).pow(k)\
    \ * ModIntRuntime::fac(k))\n                   : ModIntRuntime::fac(k) * ModIntRuntime(2).pow(k);\n\
    \    }\n\n    static ModIntRuntime nCr(int n, int r) {\n        assert(n >= 0);\n\
    \        if (r < 0 or n < r) return ModIntRuntime(0);\n        return ModIntRuntime::fac(n)\
    \ / (ModIntRuntime::fac(r) * ModIntRuntime::fac(n - r));\n    }\n\n    static\
    \ ModIntRuntime nPr(int n, int r) {\n        assert(n >= 0);\n        if (r <\
    \ 0 or n < r) return ModIntRuntime(0);\n        return ModIntRuntime::fac(n) /\
    \ ModIntRuntime::fac(n - r);\n    }\n\n    ModIntRuntime sqrt() const {\n    \
    \    if (val_ == 0) return 0;\n        if (md == 2) return val_;\n        if (power((md\
    \ - 1) / 2) != 1) return 0;\n        ModIntRuntime b = 1;\n        while (b.power((md\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModIntRuntime z = b.power(m);\n   \
    \     while (y != 1) {\n            int j = 0;\n            ModIntRuntime t =\
    \ y;\n            while (t != 1) j++, t *= t;\n            z = z.power(1LL <<\
    \ (e - j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n   \
    \     }\n        return ModIntRuntime(std::min(x.val_, md - x.val_));\n    }\n\
    };\nint ModIntRuntime::md = 1;\n#line 4 \"number/test/montmort_number_mod.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    int N, M;\n    cin >> N >> M;\n  \
    \  ModIntRuntime::set_mod(M);\n    vector<ModIntRuntime> montmort(N + 1);\n  \
    \  montmort[0] = 1, montmort[1] = 0;\n    for (int i = 2; i <= N; i++) montmort[i]\
    \ = (montmort[i - 1] + montmort[i - 2]) * (i - 1);\n    for (int i = 1; i <= N;\
    \ i++) cout << montmort[i] << (i == N ? '\\n' : ' ');\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n\
    #include \"../modint_runtime.hpp\"\n#include <iostream>\nusing namespace std;\n\
    \nint main() {\n    int N, M;\n    cin >> N >> M;\n    ModIntRuntime::set_mod(M);\n\
    \    vector<ModIntRuntime> montmort(N + 1);\n    montmort[0] = 1, montmort[1]\
    \ = 0;\n    for (int i = 2; i <= N; i++) montmort[i] = (montmort[i - 1] + montmort[i\
    \ - 2]) * (i - 1);\n    for (int i = 1; i <= N; i++) cout << montmort[i] << (i\
    \ == N ? '\\n' : ' ');\n}\n"
  dependsOn:
  - number/modint_runtime.hpp
  isVerificationFile: true
  path: number/test/montmort_number_mod.test.cpp
  requiredBy: []
  timestamp: '2025-08-25 00:47:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/montmort_number_mod.test.cpp
layout: document
redirect_from:
- /verify/number/test/montmort_number_mod.test.cpp
- /verify/number/test/montmort_number_mod.test.cpp.html
title: number/test/montmort_number_mod.test.cpp
---
