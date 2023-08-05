---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/sliding_window_aggregation.hpp
    title: data_structure/sliding_window_aggregation.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 2 \"modint.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <set>\n#include <vector>\n\ntemplate <int md> struct ModInt {\n    using\
    \ lint = long long;\n    constexpr static int mod() { return md; }\n    static\
    \ int get_primitive_root() {\n        static int primitive_root = 0;\n       \
    \ if (!primitive_root) {\n            primitive_root = [&]() {\n             \
    \   std::set<int> fac;\n                int v = md - 1;\n                for (lint\
    \ i = 2; i * i <= v; i++)\n                    while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < md; g++) {\n                    bool ok = true;\n               \
    \     for (auto i : fac)\n                        if (ModInt(g).pow((md - 1) /\
    \ i) == 1) {\n                            ok = false;\n                      \
    \      break;\n                        }\n                    if (ok) return g;\n\
    \                }\n                return -1;\n            }();\n        }\n\
    \        return primitive_root;\n    }\n    int val_;\n    int val() const noexcept\
    \ { return val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    constexpr\
    \ ModInt(lint v) { _setval(v % md + md); }\n    constexpr explicit operator bool()\
    \ const { return val_ != 0; }\n    constexpr ModInt operator+(const ModInt &x)\
    \ const {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    constexpr\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    constexpr\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    constexpr ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    constexpr ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md + x.val_);\n \
    \   }\n    friend constexpr ModInt operator-(lint a, const ModInt &x) {\n    \
    \    return ModInt()._setval(a % md - x.val_ + md);\n    }\n    friend constexpr\
    \ ModInt operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.val_ % md);\n    }\n    friend constexpr ModInt operator/(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.inv().val() % md);\n\
    \    }\n    constexpr bool operator==(const ModInt &x) const { return val_ ==\
    \ x.val_; }\n    constexpr bool operator!=(const ModInt &x) const { return val_\
    \ != x.val_; }\n    constexpr bool operator<(const ModInt &x) const {\n      \
    \  return val_ < x.val_;\n    } // To use std::map<ModInt, T>\n    friend std::istream\
    \ &operator>>(std::istream &is, ModInt &x) {\n        lint t;\n        return\
    \ is >> t, x = ModInt(t), is;\n    }\n    constexpr friend std::ostream &operator<<(std::ostream\
    \ &os, const ModInt &x) {\n        return os << x.val_;\n    }\n\n    constexpr\
    \ ModInt pow(lint n) const {\n        ModInt ans = 1, tmp = *this;\n        while\
    \ (n) {\n            if (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n\
    \        }\n        return ans;\n    }\n\n    static constexpr int cache_limit\
    \ = std::min(md, 1 << 21);\n    static std::vector<ModInt> facs, facinvs, invs;\n\
    \n    constexpr static void _precalculation(int N) {\n        const int l0 = facs.size();\n\
    \        if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n\n    constexpr ModInt inv() const {\n        if (this->val_ < cache_limit)\
    \ {\n            if (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n  \
    \          while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val_];\n        } else {\n            return\
    \ this->pow(md - 2);\n        }\n    }\n    constexpr ModInt fac() const {\n \
    \       while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \        return facs[this->val_];\n    }\n    constexpr ModInt facinv() const\
    \ {\n        while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facinvs[this->val_];\n    }\n    constexpr ModInt doublefac()\
    \ const {\n        lint k = (this->val_ + 1) / 2;\n        return (this->val_\
    \ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n        \
    \                        : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\n    constexpr\
    \ ModInt nCr(int r) const {\n        if (r < 0 or this->val_ < r) return ModInt(0);\n\
    \        return this->fac() * (*this - r).facinv() * ModInt(r).facinv();\n   \
    \ }\n\n    constexpr ModInt nPr(int r) const {\n        if (r < 0 or this->val_\
    \ < r) return ModInt(0);\n        return this->fac() * (*this - r).facinv();\n\
    \    }\n\n    static ModInt binom(int n, int r) {\n        static long long bruteforce_times\
    \ = 0;\n\n        if (r < 0 or n < r) return ModInt(0);\n        if (n <= bruteforce_times\
    \ or n < (int)facs.size()) return ModInt(n).nCr(r);\n\n        r = std::min(r,\
    \ n - r);\n\n        ModInt ret = ModInt(r).facinv();\n        for (int i = 0;\
    \ i < r; ++i) ret *= n - i;\n        bruteforce_times += r;\n\n        return\
    \ ret;\n    }\n\n    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1!\
    \ k_2! ... k_m!)\n    // Complexity: O(sum(ks))\n    template <class Vec> static\
    \ ModInt multinomial(const Vec &ks) {\n        ModInt ret{1};\n        int sum\
    \ = 0;\n        for (int k : ks) {\n            assert(k >= 0);\n            ret\
    \ *= ModInt(k).facinv(), sum += k;\n        }\n        return ret * ModInt(sum).fac();\n\
    \    }\n\n    // Catalan number, C_n = binom(2n, n) / (n + 1)\n    // C_0 = 1,\
    \ C_1 = 1, C_2 = 2, C_3 = 5, C_4 = 14, ...\n    // https://oeis.org/A000108\n\
    \    // Complexity: O(n)\n    static ModInt catalan(int n) {\n        if (n <\
    \ 0) return ModInt(0);\n        return ModInt(n * 2).fac() * ModInt(n + 1).facinv()\
    \ * ModInt(n).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val_\
    \ == 0) return 0;\n        if (md == 2) return val_;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 2 \"data_structure/sliding_window_aggregation.hpp\"\n#include <stack>\n\
    #include <utility>\n#line 5 \"data_structure/sliding_window_aggregation.hpp\"\n\
    \n// Sliding-Window Aggregation based queue\n// - `std::queue`-like data structure\
    \ with monoid operation\n// - Each operation is amortized O(1)\n// - Verification:\n\
    // https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077\n\
    // - Reference:\n// https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp\n\
    template <typename T_VAL, typename T_PROD, T_PROD (*val2prod)(T_VAL), T_PROD (*op)(T_PROD,\
    \ T_PROD)>\nstruct swag_queue {\n    std::stack<std::pair<T_VAL, T_PROD>, std::vector<std::pair<T_VAL,\
    \ T_PROD>>> front_stack,\n        back_stack;\n    T_PROD ID_;\n\n    swag_queue(T_PROD\
    \ id_prod) : ID_(id_prod) {}\n    bool empty() const { return front_stack.empty()\
    \ and back_stack.empty(); }\n    int size() const { return front_stack.size()\
    \ + back_stack.size(); }\n    T_PROD fold_all() const {\n        if (empty())\n\
    \            return ID_;\n        else if (front_stack.empty())\n            return\
    \ back_stack.top().second;\n        else if (back_stack.empty())\n           \
    \ return front_stack.top().second;\n        else\n            return op(front_stack.top().second,\
    \ back_stack.top().second);\n    }\n    void push(const T_VAL &x) {\n        if\
    \ (back_stack.empty())\n            back_stack.emplace(x, val2prod(x));\n    \
    \    else\n            back_stack.emplace(x, op(back_stack.top().second, val2prod(x)));\n\
    \    }\n    T_VAL pop() {\n        if (front_stack.empty()) {\n            front_stack.emplace(back_stack.top().first,\
    \ val2prod(back_stack.top().first));\n            back_stack.pop();\n        \
    \    while (!back_stack.empty()) {\n                T_VAL t = back_stack.top().first;\n\
    \                front_stack.emplace(t, op(val2prod(t), front_stack.top().second));\n\
    \                back_stack.pop();\n            }\n        }\n        T_VAL t\
    \ = front_stack.top().first;\n        front_stack.pop();\n        return t;\n\
    \    }\n};\n\ntemplate <typename T> T swag_op_id(T x) { return x; };\ntemplate\
    \ <typename T> T swag_op_linear_merge(T l, T r) {\n    return std::make_pair(l.first\
    \ * r.first, l.second * r.first + r.second);\n};\n\n// Linear function composition\n\
    // `f(x) = first * x + second`, operate most recently added function first\ntemplate\
    \ <typename T>\nstruct LinearFunctionQueue\n    : public swag_queue<std::pair<T,\
    \ T>, std::pair<T, T>, swag_op_id, swag_op_linear_merge> {\n    LinearFunctionQueue()\n\
    \        : swag_queue<std::pair<T, T>, std::pair<T, T>, swag_op_id, swag_op_linear_merge>::swag_queue(\n\
    \              std::pair<T, T>(1, 0)) {}\n};\n#line 3 \"data_structure/test/queue_operate_all_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n#line 5 \"data_structure/test/queue_operate_all_composite.test.cpp\"\nusing\
    \ namespace std;\n\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    LinearFunctionQueue<mint> swag;\n    int Q;\n\
    \    cin >> Q;\n    while (Q--) {\n        int q;\n        cin >> q;\n       \
    \ if (q == 0) {\n            mint a, b;\n            cin >> a >> b;\n        \
    \    swag.push({a, b});\n        }\n        if (q == 1) swag.pop();\n        if\
    \ (q == 2) {\n            mint x;\n            cin >> x;\n            pair<mint,\
    \ mint> f = swag.fold_all();\n            cout << (f.first * x + f.second).val()\
    \ << '\\n';\n        }\n    }\n}\n"
  code: "#include \"../../modint.hpp\"\n#include \"../sliding_window_aggregation.hpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n#include <iostream>\nusing namespace std;\n\nusing mint = ModInt<998244353>;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    LinearFunctionQueue<mint>\
    \ swag;\n    int Q;\n    cin >> Q;\n    while (Q--) {\n        int q;\n      \
    \  cin >> q;\n        if (q == 0) {\n            mint a, b;\n            cin >>\
    \ a >> b;\n            swag.push({a, b});\n        }\n        if (q == 1) swag.pop();\n\
    \        if (q == 2) {\n            mint x;\n            cin >> x;\n         \
    \   pair<mint, mint> f = swag.fold_all();\n            cout << (f.first * x +\
    \ f.second).val() << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - modint.hpp
  - data_structure/sliding_window_aggregation.hpp
  isVerificationFile: true
  path: data_structure/test/queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2023-08-05 18:05:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/queue_operate_all_composite.test.cpp
- /verify/data_structure/test/queue_operate_all_composite.test.cpp.html
title: data_structure/test/queue_operate_all_composite.test.cpp
---
