---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/integer_segments.test.cpp
    title: utilities/test/integer_segments.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://satanic0258.github.io/snippets/data-structure/SegmentMap.html>
  bundledCode: "#line 2 \"utilities/integer_segments.hpp\"\n#include <map>\n#include\
    \ <utility>\n\n// CUT begin\n// Add/erase ranges on \\mathbb{Z}\n// Basic implementation\
    \ idea: <https://satanic0258.github.io/snippets/data-structure/SegmentMap.html>\n\
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
    \ p.second) - p.first + 1;\n        }\n        return ret;\n    }\n};\n"
  code: "#pragma once\n#include <map>\n#include <utility>\n\n// CUT begin\n// Add/erase\
    \ ranges on \\mathbb{Z}\n// Basic implementation idea: <https://satanic0258.github.io/snippets/data-structure/SegmentMap.html>\n\
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
    \ p.second) - p.first + 1;\n        }\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/integer_segments.hpp
  requiredBy: []
  timestamp: '2020-12-05 03:41:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/integer_segments.test.cpp
documentation_of: utilities/integer_segments.hpp
layout: document
redirect_from:
- /library/utilities/integer_segments.hpp
- /library/utilities/integer_segments.hpp.html
title: utilities/integer_segments.hpp
---
