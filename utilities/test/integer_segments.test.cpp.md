---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/integer_segments.hpp
    title: utilities/integer_segments.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/674
    links:
    - https://yukicoder.me/problems/no/674
  bundledCode: "#line 1 \"utilities/test/integer_segments.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/674\"\n#line 2 \"utilities/integer_segments.hpp\"\
    \n#include <map>\n#include <utility>\n\n// CUT begin\n// Add/erase ranges on \\\
    mathbb{Z}\n// Basic implementation idea: <https://satanic0258.github.io/snippets/data-structure/SegmentMap.html>\n\
    template <typename Int> struct integer_segments {\n    const Int INVALID = -1;\n\
    \    Int _sz;\n    std::map<Int, Int> mp;\n    integer_segments() : _sz(0) {}\n\
    \n    // Get the range [l, r] that satisfies l <= x <= r, or [INVALID, INVALID]\
    \ otherwise\n    std::pair<Int, Int> get(Int x) const {\n        auto itr = mp.upper_bound(x);\n\
    \        if (itr == mp.begin() or (--itr)->second < x) return std::make_pair(INVALID,\
    \ INVALID);\n        return *itr;\n    }\n\n    void _mp_upd(Int l, Int r) {\n\
    \        if (mp.count(l)) _sz -= mp[l] - l + 1;\n        mp[l] = r, _sz += r -\
    \ l + 1;\n    }\n\n    // Add {l, l + 1, ..., r} and return the merged segment\
    \ which [l, r] belongs to\n    std::pair<Int, Int> insert(Int l, Int r) {\n  \
    \      auto itl = mp.upper_bound(l), itr = mp.upper_bound(r + 1);\n        if\
    \ (itl != mp.begin() and (--itl)->second < l - 1) { ++itl; }\n        if (itl\
    \ != itr) {\n            l = std::min(l, itl->first), r = std::max(r, std::prev(itr)->second);\n\
    \            for (auto i = itl; i != itr; i++) _sz -= i->second - i->first + 1;\n\
    \            mp.erase(itl, itr);\n        }\n        if (mp.count(l)) _sz -= mp[l]\
    \ - l + 1;\n        _mp_upd(l, r);\n        return std::make_pair(l, r);\n   \
    \ }\n\n    // Remove {l, l + 1, ..., r}\n    void remove(Int l, Int r) {\n   \
    \     auto itl = mp.upper_bound(l), itr = mp.upper_bound(r);\n        if (itl\
    \ != mp.begin() and (--itl)->second < l) { ++itl; }\n        if (itl == itr) {\
    \ return; }\n        Int tl = std::min(l, itl->first), tr = std::max(r, std::prev(itr)->second);\n\
    \        for (auto i = itl; i != itr; i++) _sz -= i->second - i->first + 1;\n\
    \        mp.erase(itl, itr);\n        if (tl < l) _mp_upd(tl, l - 1);\n      \
    \  if (r < tr) _mp_upd(r + 1, tr);\n    }\n\n    Int count() const { return _sz;\
    \ }\n\n    // O((# of segments))\n    Int find_by_order(Int k) const {\n     \
    \   if (mp.empty()) return -1;\n        Int hi = mp.begin()->first - 1;\n    \
    \    for (const auto &p : mp) {\n            const Int l = p.first, r = p.second;\n\
    \            hi = std::max(hi, l - 1);\n            Int add = std::max(Int(0),\
    \ r - hi);\n            if (add >= k + 1) return hi + k + 1;\n            k -=\
    \ add;\n            hi = std::max(hi, r);\n        }\n        return -1;\n   \
    \ }\n\n    // Count elements strictly less than x, O((# of segments))\n    Int\
    \ order_of_key(Int x) const {\n        Int ret = 0;\n        for (auto p : x)\
    \ {\n            if (p.first >= x) break;\n            ret += std::min(x - 1,\
    \ p.second) - p.first + 1;\n        }\n        return ret;\n    }\n};\n#line 3\
    \ \"utilities/test/integer_segments.test.cpp\"\n\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   long long D;\n    int Q;\n    cin >> D >> Q;\n    integer_segments<long long>\
    \ seg;\n\n    long long ret = 0;\n    while (Q--) {\n        long long a, b;\n\
    \        cin >> a >> b;\n        auto lr = seg.insert(a, b);\n        ret = max(ret,\
    \ lr.second - lr.first + 1);\n        cout << ret << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/674\"\n#include \"../integer_segments.hpp\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    long long D;\n    int Q;\n    cin >> D >>\
    \ Q;\n    integer_segments<long long> seg;\n\n    long long ret = 0;\n    while\
    \ (Q--) {\n        long long a, b;\n        cin >> a >> b;\n        auto lr =\
    \ seg.insert(a, b);\n        ret = max(ret, lr.second - lr.first + 1);\n     \
    \   cout << ret << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/integer_segments.hpp
  isVerificationFile: true
  path: utilities/test/integer_segments.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 15:35:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/integer_segments.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/integer_segments.test.cpp
- /verify/utilities/test/integer_segments.test.cpp.html
title: utilities/test/integer_segments.test.cpp
---
