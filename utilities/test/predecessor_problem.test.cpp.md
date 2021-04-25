---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/integer_segments.hpp
    title: utilities/integer_segments.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/predecessor_problem
    links:
    - https://judge.yosupo.jp/problem/predecessor_problem
  bundledCode: "#line 2 \"utilities/integer_segments.hpp\"\n#include <iostream>\n\
    #include <map>\n#include <utility>\n\n// CUT begin\n// Add/erase ranges on \\\
    mathbb{Z}\n// Basic implementation idea: https://satanic0258.github.io/snippets/data-structure/SegmentMap.html\n\
    template <typename Int> struct integer_segments {\n    const Int INVALID = -1;\n\
    \    Int _sz;\n    std::map<Int, Int> mp;\n    integer_segments() : _sz(0) {}\n\
    \n    // Get the range [l, r] that satisfies l <= x <= r, or [INVALID, INVALID]\
    \ otherwise\n    std::pair<Int, Int> get(Int x) const {\n        auto itr = mp.upper_bound(x);\n\
    \        if (itr == mp.begin() or (--itr)->second < x) return std::make_pair(INVALID,\
    \ INVALID);\n        return *itr;\n    }\n\n    bool contains(Int x) const { return\
    \ lower_bound(x) == x; }\n\n    // Find the min. y in the set that satisfies x\
    \ <= y\n    Int lower_bound(Int x) const {\n        auto itr = mp.upper_bound(x);\n\
    \        if (itr != mp.begin() and std::prev(itr)->second >= x) return x;\n  \
    \      if (itr != mp.end()) return itr->first;\n        return INVALID;\n    }\n\
    \n    // Find the max. y in the set that satisfies y <= x\n    Int inv_lower_bound(Int\
    \ x) const {\n        auto itr = mp.upper_bound(x);\n        if (itr == mp.begin())\
    \ return INVALID;\n        if ((--itr)->second >= x) return x;\n        return\
    \ itr->second;\n    }\n\n    void _mp_upd(Int l, Int r) {\n        if (mp.count(l))\
    \ _sz -= mp[l] - l + 1;\n        mp[l] = r, _sz += r - l + 1;\n    }\n\n    //\
    \ Add {l, l + 1, ..., r} and return the merged segment which [l, r] belongs to\n\
    \    std::pair<Int, Int> insert(Int l, Int r) {\n        auto itl = mp.upper_bound(l),\
    \ itr = mp.upper_bound(r + 1);\n        if (itl != mp.begin() and (--itl)->second\
    \ < l - 1) { ++itl; }\n        if (itl != itr) {\n            l = std::min(l,\
    \ itl->first), r = std::max(r, std::prev(itr)->second);\n            for (auto\
    \ i = itl; i != itr; i++) _sz -= i->second - i->first + 1;\n            mp.erase(itl,\
    \ itr);\n        }\n        if (mp.count(l)) _sz -= mp[l] - l + 1;\n        _mp_upd(l,\
    \ r);\n        return std::make_pair(l, r);\n    }\n\n    // Remove {l, l + 1,\
    \ ..., r}\n    void remove(Int l, Int r) {\n        auto itl = mp.upper_bound(l),\
    \ itr = mp.upper_bound(r);\n        if (itl != mp.begin() and (--itl)->second\
    \ < l) { ++itl; }\n        if (itl == itr) { return; }\n        Int tl = std::min(l,\
    \ itl->first), tr = std::max(r, std::prev(itr)->second);\n        for (auto i\
    \ = itl; i != itr; i++) _sz -= i->second - i->first + 1;\n        mp.erase(itl,\
    \ itr);\n        if (tl < l) _mp_upd(tl, l - 1);\n        if (r < tr) _mp_upd(r\
    \ + 1, tr);\n    }\n\n    Int count() const { return _sz; }\n\n    // O((# of\
    \ segments))\n    Int find_by_order(Int k) const {\n        if (mp.empty()) return\
    \ -1;\n        Int hi = mp.begin()->first - 1;\n        for (const auto &p : mp)\
    \ {\n            const Int l = p.first, r = p.second;\n            hi = std::max(hi,\
    \ l - 1);\n            Int add = std::max(Int(0), r - hi);\n            if (add\
    \ >= k + 1) return hi + k + 1;\n            k -= add;\n            hi = std::max(hi,\
    \ r);\n        }\n        return -1;\n    }\n\n    // Count elements strictly\
    \ less than x, O((# of segments))\n    Int order_of_key(Int x) const {\n     \
    \   Int ret = 0;\n        for (auto p : x) {\n            if (p.first >= x) break;\n\
    \            ret += std::min(x - 1, p.second) - p.first + 1;\n        }\n    \
    \    return ret;\n    }\n\n    friend std::ostream &operator<<(std::ostream &os,\
    \ const integer_segments &x) {\n        os << '{';\n        for (auto &&p : x.mp)\
    \ os << '[' << p.first << ',' << p.second << \"],\";\n        return os << '}';\n\
    \    }\n};\n#line 3 \"utilities/test/predecessor_problem.test.cpp\"\n#include\
    \ <string>\nusing namespace std;\n#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N, Q;\n    string T;\n    cin >> N >> Q >> T;\n    integer_segments<int> seg;\n\
    \    T += '0';\n    int l = 0;\n    for (int i = 0; i < int(T.size()); i++) {\n\
    \        if (T[i] == '0') {\n            if (l <= i - 1) seg.insert(l, i - 1);\n\
    \            l = i + 1;\n        }\n    }\n    while (Q--) {\n        int c, k;\n\
    \        cin >> c >> k;\n        if (c == 0) seg.insert(k, k);\n        if (c\
    \ == 1) seg.remove(k, k);\n        if (c == 2) cout << seg.contains(k) << '\\\
    n';\n        if (c == 3) cout << seg.lower_bound(k) << '\\n';\n        if (c ==\
    \ 4) cout << seg.inv_lower_bound(k) << '\\n';\n    }\n}\n"
  code: "#include \"../integer_segments.hpp\"\n#include <iostream>\n#include <string>\n\
    using namespace std;\n#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N, Q;\n    string T;\n    cin >> N >> Q >> T;\n    integer_segments<int> seg;\n\
    \    T += '0';\n    int l = 0;\n    for (int i = 0; i < int(T.size()); i++) {\n\
    \        if (T[i] == '0') {\n            if (l <= i - 1) seg.insert(l, i - 1);\n\
    \            l = i + 1;\n        }\n    }\n    while (Q--) {\n        int c, k;\n\
    \        cin >> c >> k;\n        if (c == 0) seg.insert(k, k);\n        if (c\
    \ == 1) seg.remove(k, k);\n        if (c == 2) cout << seg.contains(k) << '\\\
    n';\n        if (c == 3) cout << seg.lower_bound(k) << '\\n';\n        if (c ==\
    \ 4) cout << seg.inv_lower_bound(k) << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/integer_segments.hpp
  isVerificationFile: true
  path: utilities/test/predecessor_problem.test.cpp
  requiredBy: []
  timestamp: '2021-04-25 18:25:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/predecessor_problem.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/predecessor_problem.test.cpp
- /verify/utilities/test/predecessor_problem.test.cpp.html
title: utilities/test/predecessor_problem.test.cpp
---
