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
    \ <utility>\n\n// CUT begin\n// Add/erase ranges on \\mathbb{Z}\n// Reference:\
    \ <https://satanic0258.github.io/snippets/data-structure/SegmentMap.html> (Almost\
    \ transcribed from this code)\ntemplate <typename Int> struct integer_segments\
    \ {\n    const Int INVALID = -1;\n    std::map<Int, Int> mp;\n    integer_segments()\
    \ = default;\n\n    // Get the range [l, r] that satisfies l <= x <= r, or [INVALID,\
    \ INVALID] otherwise\n    std::pair<Int, Int> get(Int x) const {\n        auto\
    \ itr = mp.upper_bound(x);\n        if (itr == mp.begin() or (--itr)->second <\
    \ x) { return std::make_pair(INVALID, INVALID); }\n        return *itr;\n    }\n\
    \n    // Add {l, l + 1, ..., r} and return the merged segment which [l, r] belongs\
    \ to\n    std::pair<Int, Int> insert(Int l, Int r) {\n        auto itl = mp.upper_bound(l),\
    \ itr = mp.upper_bound(r + 1);\n        if (itl != mp.begin() and (--itl)->second\
    \ < l - 1) { ++itl; }\n        if (itl != itr) {\n            l = std::min(l,\
    \ itl->first), r = std::max(r, std::prev(itr)->second);\n            mp.erase(itl,\
    \ itr);\n        }\n        mp[l] = r;\n        return std::make_pair(l, r);\n\
    \    }\n\n    // Remove {l, l + 1, ..., r}\n    void remove(Int l, Int r) {\n\
    \        auto itl = mp.upper_bound(l), itr = mp.upper_bound(r);\n        if (itl\
    \ != mp.begin() and (--itl)->second < l) { ++itl; }\n        if (itl == itr) {\
    \ return; }\n        Int tl = std::min(l, itl->first), tr = std::max(r, std::prev(itr)->second);\n\
    \        mp.erase(itl, itr);\n        if (tl < l) { mp[tl] = l - 1; }\n      \
    \  if (r < tr) { mp[r + 1] = tr; }\n    }\n};\n"
  code: "#pragma once\n#include <map>\n#include <utility>\n\n// CUT begin\n// Add/erase\
    \ ranges on \\mathbb{Z}\n// Reference: <https://satanic0258.github.io/snippets/data-structure/SegmentMap.html>\
    \ (Almost transcribed from this code)\ntemplate <typename Int> struct integer_segments\
    \ {\n    const Int INVALID = -1;\n    std::map<Int, Int> mp;\n    integer_segments()\
    \ = default;\n\n    // Get the range [l, r] that satisfies l <= x <= r, or [INVALID,\
    \ INVALID] otherwise\n    std::pair<Int, Int> get(Int x) const {\n        auto\
    \ itr = mp.upper_bound(x);\n        if (itr == mp.begin() or (--itr)->second <\
    \ x) { return std::make_pair(INVALID, INVALID); }\n        return *itr;\n    }\n\
    \n    // Add {l, l + 1, ..., r} and return the merged segment which [l, r] belongs\
    \ to\n    std::pair<Int, Int> insert(Int l, Int r) {\n        auto itl = mp.upper_bound(l),\
    \ itr = mp.upper_bound(r + 1);\n        if (itl != mp.begin() and (--itl)->second\
    \ < l - 1) { ++itl; }\n        if (itl != itr) {\n            l = std::min(l,\
    \ itl->first), r = std::max(r, std::prev(itr)->second);\n            mp.erase(itl,\
    \ itr);\n        }\n        mp[l] = r;\n        return std::make_pair(l, r);\n\
    \    }\n\n    // Remove {l, l + 1, ..., r}\n    void remove(Int l, Int r) {\n\
    \        auto itl = mp.upper_bound(l), itr = mp.upper_bound(r);\n        if (itl\
    \ != mp.begin() and (--itl)->second < l) { ++itl; }\n        if (itl == itr) {\
    \ return; }\n        Int tl = std::min(l, itl->first), tr = std::max(r, std::prev(itr)->second);\n\
    \        mp.erase(itl, itr);\n        if (tl < l) { mp[tl] = l - 1; }\n      \
    \  if (r < tr) { mp[r + 1] = tr; }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/integer_segments.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
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
