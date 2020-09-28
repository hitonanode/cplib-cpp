---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modulus/modint_runtime.hpp
    title: modulus/modint_runtime.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"modulus/test/sqrt_modint_runtime.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\n#include <iostream>\n#line 3 \"\
    modulus/modint_runtime.hpp\"\n#include <vector>\n#include <set>\n\n// CUT begin\n\
    struct ModIntRuntime\n{\n    using lint = long long int;\n    static int get_mod()\
    \ { return mod; }\n    int val;\n    static int mod;\n    static std::vector<ModIntRuntime>\
    \ &facs()\n    {\n        static std::vector<ModIntRuntime> facs_;\n        return\
    \ facs_;\n    }\n    static int &get_primitive_root() {\n        static int primitive_root_\
    \ = 0;\n        if (!primitive_root_) {\n            primitive_root_ = [&](){\n\
    \                std::set<int> fac;\n                int v = mod - 1;\n      \
    \          for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < mod; g++) {\n                    bool ok = true;\n              \
    \      for (auto i : fac) if (ModIntRuntime(g).power((mod - 1) / i) == 1) { ok\
    \ = false; break; }\n                    if (ok) return g;\n                }\n\
    \                return -1;\n            }();\n        }\n        return primitive_root_;\n\
    \    }\n    static void set_mod(const int &m) {\n        if (mod != m) facs().clear();\n\
    \        mod = m;\n        get_primitive_root() = 0;\n    }\n    ModIntRuntime\
    \ &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }\n    ModIntRuntime()\
    \ : val(0) {}\n    ModIntRuntime(lint v) { _setval(v % mod + mod); }\n    explicit\
    \ operator bool() const { return val != 0; }\n    ModIntRuntime operator+(const\
    \ ModIntRuntime &x) const { return ModIntRuntime()._setval((lint)val + x.val);\
    \ }\n    ModIntRuntime operator-(const ModIntRuntime &x) const { return ModIntRuntime()._setval((lint)val\
    \ - x.val + mod); }\n    ModIntRuntime operator*(const ModIntRuntime &x) const\
    \ { return ModIntRuntime()._setval((lint)val * x.val % mod); }\n    ModIntRuntime\
    \ operator/(const ModIntRuntime &x) const { return ModIntRuntime()._setval((lint)val\
    \ * x.inv() % mod); }\n    ModIntRuntime operator-() const { return ModIntRuntime()._setval(mod\
    \ - val); }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this\
    \ = *this + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return\
    \ *this = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x)\
    \ { return *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime\
    \ &x) { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a,\
    \ const ModIntRuntime &x) { return ModIntRuntime()._setval(a % mod + x.val); }\n\
    \    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) { return ModIntRuntime()._setval(a\
    \ % mod - x.val + mod); }\n    friend ModIntRuntime operator*(lint a, const ModIntRuntime\
    \ &x) { return ModIntRuntime()._setval(a % mod * x.val % mod); }\n    friend ModIntRuntime\
    \ operator/(lint a, const ModIntRuntime &x) { return ModIntRuntime()._setval(a\
    \ % mod * x.inv() % mod); }\n    bool operator==(const ModIntRuntime &x) const\
    \ { return val == x.val; }\n    bool operator!=(const ModIntRuntime &x) const\
    \ { return val != x.val; }\n    bool operator<(const ModIntRuntime &x) const {\
    \ return val < x.val; }  // To use std::map<ModIntRuntime, T>\n    friend std::istream\
    \ &operator>>(std::istream &is, ModIntRuntime &x) { lint t; is >> t; x = ModIntRuntime(t);\
    \ return is; }\n    friend std::ostream &operator<<(std::ostream &os, const ModIntRuntime\
    \ &x) { os << x.val;  return os; }\n \n    lint power(lint n) const {\n      \
    \  lint ans = 1, tmp = this->val;\n        while (n) {\n            if (n & 1)\
    \ ans = ans * tmp % mod;\n            tmp = tmp * tmp % mod;\n            n /=\
    \ 2;\n        }\n        return ans;\n    }\n    lint inv() const { return this->power(mod\
    \ - 2); }\n    ModIntRuntime operator^(lint n) const { return ModIntRuntime(this->power(n));\
    \ }\n    ModIntRuntime &operator^=(lint n) { return *this = *this ^ n; }\n \n\
    \    ModIntRuntime fac() const {\n        int l0 = facs().size();\n        if\
    \ (l0 > this->val) return facs()[this->val];\n \n        facs().resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs()[i] = (i == 0 ? ModIntRuntime(1)\
    \ : facs()[i - 1] * ModIntRuntime(i));\n        return facs()[this->val];\n  \
    \  }\n \n    ModIntRuntime doublefac() const {\n        lint k = (this->val +\
    \ 1) / 2;\n        if (this->val & 1) return ModIntRuntime(k * 2).fac() / ModIntRuntime(2).power(k)\
    \ / ModIntRuntime(k).fac();\n        else return ModIntRuntime(k).fac() * ModIntRuntime(2).power(k);\n\
    \    }\n \n    ModIntRuntime nCr(const ModIntRuntime &r) const {\n        if (this->val\
    \ < r.val) return ModIntRuntime(0);\n        return this->fac() / ((*this - r).fac()\
    \ * r.fac());\n    }\n\n    ModIntRuntime sqrt() const {\n        if (val == 0)\
    \ return 0;\n        if (mod == 2) return val;\n        if (power((mod - 1) /\
    \ 2) != 1) return 0;\n        ModIntRuntime b = 1;\n        while (b.power((mod\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModIntRuntime z = b.power(m);\n   \
    \     while (y != 1) {\n            int j = 0;\n            ModIntRuntime t =\
    \ y;\n            while (t != 1) j++, t *= t;\n            z = z.power(1LL <<\
    \ (e - j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n   \
    \     }\n        return ModIntRuntime(std::min(x.val, mod - x.val));\n    }\n\
    };\nint ModIntRuntime::mod = 1;\n#line 4 \"modulus/test/sqrt_modint_runtime.test.cpp\"\
    \nusing namespace std;\n\nint main()\n{\n    int T;\n    cin >> T;\n    while\
    \ (T--) {\n        int Y, P;\n        cin >> Y >> P;\n        ModIntRuntime::mod\
    \ = P;\n        ModIntRuntime m = Y;\n        if (Y) {\n            m = m.sqrt();\n\
    \            cout << (m ? m.val : -1) << endl;\n        }\n        else cout <<\
    \ 0 << endl;\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n#include <iostream>\n\
    #include \"modulus/modint_runtime.hpp\"\nusing namespace std;\n\nint main()\n\
    {\n    int T;\n    cin >> T;\n    while (T--) {\n        int Y, P;\n        cin\
    \ >> Y >> P;\n        ModIntRuntime::mod = P;\n        ModIntRuntime m = Y;\n\
    \        if (Y) {\n            m = m.sqrt();\n            cout << (m ? m.val :\
    \ -1) << endl;\n        }\n        else cout << 0 << endl;\n    }\n}\n"
  dependsOn:
  - modulus/modint_runtime.hpp
  isVerificationFile: true
  path: modulus/test/sqrt_modint_runtime.test.cpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: modulus/test/sqrt_modint_runtime.test.cpp
layout: document
redirect_from:
- /verify/modulus/test/sqrt_modint_runtime.test.cpp
- /verify/modulus/test/sqrt_modint_runtime.test.cpp.html
title: modulus/test/sqrt_modint_runtime.test.cpp
---
