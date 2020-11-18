---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: other_data_structures/sliding_window_aggregation.hpp
    title: other_data_structures/sliding_window_aggregation.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <int mod> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    static int get_mod() { return mod; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&]() {\n                std::set<int> fac;\n\
    \                int v = mod - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < mod;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).power((mod - 1) / i) == 1) {\n\
    \                            ok = false;\n                            break;\n\
    \                        }\n                    if (ok) return g;\n          \
    \      }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) {\n        val = (v >= mod ? v - mod : v);\n\
    \        return *this;\n    }\n    MDCONST ModInt(lint v) { _setval(v % mod +\
    \ mod); }\n    explicit operator bool() const { return val != 0; }\n    MDCONST\
    \ ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + mod); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % mod); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }\n \
    \   MDCONST ModInt operator-() const { return ModInt()._setval(mod - val); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt\
    \ &x) { return ModInt()._setval(a % mod - x.val + mod); }\n    friend MDCONST\
    \ ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.val % mod); }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) { return ModInt()._setval(a % mod * x.inv() % mod); }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST lint power(lint n) const {\n        lint ans = 1,\
    \ tmp = this->val;\n        while (n) {\n            if (n & 1) ans = ans * tmp\
    \ % mod;\n            tmp = tmp * tmp % mod, n /= 2;\n        }\n        return\
    \ ans;\n    }\n    MDCONST ModInt pow(lint n) const { return power(n); }\n   \
    \ MDCONST lint inv() const { return this->power(mod - 2); }\n    ModInt fac()\
    \ const {\n        static std::vector<ModInt> facs;\n        int l0 = facs.size();\n\
    \        if (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
    \ : facs[i - 1] * ModInt(i));\n        return facs[this->val];\n    }\n\n    ModInt\
    \ doublefac() const {\n        lint k = (this->val + 1) / 2;\n        return (this->val\
    \ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac()) : ModInt(k).fac()\
    \ * ModInt(2).pow(k);\n    }\n    ModInt nCr(const ModInt &r) const { return (this->val\
    \ < r.val) ? 0 : this->fac() / ((*this - r).fac() * r.fac()); }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (power((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.power((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.power(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e -\
    \ j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"other_data_structures/sliding_window_aggregation.hpp\"\
    \n#include <stack>\n#include <utility>\nusing namespace std;\n\n// CUT begin\n\
    // Sliding-Window Aggregation based queue\n// - `std::queue`-like data structure\
    \ with monoid operation\n// - Each operation is amortized O(1)\n// - Verification:\
    \ <https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>\n\
    // - Reference: <https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>\n\
    template <typename T_VAL, typename T_PROD, typename VAL2PROD, typename MERGE>\
    \ struct SlidingWindowAggregation {\n    stack<pair<T_VAL, T_PROD>> front_stack,\
    \ back_stack;\n    VAL2PROD val2prod;\n    MERGE merge;\n    T_PROD ID_;\n\n \
    \   SlidingWindowAggregation(VAL2PROD v2p, MERGE pp2p, T_PROD id_prod) : val2prod(v2p),\
    \ merge(pp2p), ID_(id_prod) {}\n    bool empty() const { return front_stack.empty()\
    \ and back_stack.empty(); }\n    int size() const { return front_stack.size()\
    \ + back_stack.size(); }\n    T_PROD fold_all() const {\n        if (empty())\n\
    \            return ID_;\n        else if (front_stack.empty())\n            return\
    \ back_stack.top().second;\n        else if (back_stack.empty())\n           \
    \ return front_stack.top().second;\n        else\n            return merge(front_stack.top().second,\
    \ back_stack.top().second);\n    }\n    void push(const T_VAL &x) {\n        if\
    \ (back_stack.empty())\n            back_stack.emplace(x, val2prod(x));\n    \
    \    else\n            back_stack.emplace(x, merge(back_stack.top().second, val2prod(x)));\n\
    \    }\n    T_VAL pop() {\n        if (front_stack.empty()) {\n            front_stack.emplace(back_stack.top().first,\
    \ val2prod(back_stack.top().first));\n            back_stack.pop();\n        \
    \    while (!back_stack.empty()) {\n                T_VAL t = back_stack.top().first;\n\
    \                front_stack.emplace(t, merge(val2prod(t), front_stack.top().second));\n\
    \                back_stack.pop();\n            }\n        }\n        T_VAL t\
    \ = front_stack.top().first;\n        front_stack.pop();\n        return t;\n\
    \    }\n};\n\nauto swag_op_id = [](auto x) { return x; };\nauto swag_op_linear_merge\
    \ = [](auto l, auto r) { return make_pair(l.first * r.first, l.second * r.first\
    \ + r.second); };\n\n// Linear function composition\n// `f(x) = first * x + second`,\
    \ operate most recently added function first\ntemplate <typename T> struct LinearFunctionQueue\
    \ : public SlidingWindowAggregation<pair<T, T>, pair<T, T>, decltype(swag_op_id),\
    \ decltype(swag_op_linear_merge)> {\n    LinearFunctionQueue() : SlidingWindowAggregation<pair<T,\
    \ T>, pair<T, T>, decltype(swag_op_id), decltype(swag_op_linear_merge)>::SlidingWindowAggregation(swag_op_id,\
    \ swag_op_linear_merge, pair<T, T>(1, 0)) {}\n};\n#line 3 \"other_data_structures/test/queue_operate_all_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n#line 5 \"other_data_structures/test/queue_operate_all_composite.test.cpp\"\n\
    \nusing mint = ModInt<998244353>;\nint main() {\n    LinearFunctionQueue<mint>\
    \ swag;\n    int Q;\n    cin >> Q;\n    while (Q--) {\n        int q;\n      \
    \  cin >> q;\n        if (q == 0) {\n            mint a, b;\n            cin >>\
    \ a >> b;\n            swag.push({a, b});\n        }\n        if (q == 1) swag.pop();\n\
    \        if (q == 2) {\n            mint x;\n            cin >> x;\n         \
    \   pair<mint, mint> f = swag.fold_all();\n            printf(\"%d\\n\", (f.first\
    \ * x + f.second).val);\n        }\n    }\n}\n"
  code: "#include \"modint.hpp\"\n#include \"other_data_structures/sliding_window_aggregation.hpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n#include <iostream>\n\nusing mint = ModInt<998244353>;\nint main() {\n    LinearFunctionQueue<mint>\
    \ swag;\n    int Q;\n    cin >> Q;\n    while (Q--) {\n        int q;\n      \
    \  cin >> q;\n        if (q == 0) {\n            mint a, b;\n            cin >>\
    \ a >> b;\n            swag.push({a, b});\n        }\n        if (q == 1) swag.pop();\n\
    \        if (q == 2) {\n            mint x;\n            cin >> x;\n         \
    \   pair<mint, mint> f = swag.fold_all();\n            printf(\"%d\\n\", (f.first\
    \ * x + f.second).val);\n        }\n    }\n}\n"
  dependsOn:
  - modint.hpp
  - other_data_structures/sliding_window_aggregation.hpp
  isVerificationFile: true
  path: other_data_structures/test/queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_data_structures/test/queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/other_data_structures/test/queue_operate_all_composite.test.cpp
- /verify/other_data_structures/test/queue_operate_all_composite.test.cpp.html
title: other_data_structures/test/queue_operate_all_composite.test.cpp
---
