---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: '#line 2 "utilities/gnu_pbds.hpp"


    // CUT begin

    #include <ext/pb_ds/assoc_container.hpp>

    #include <ext/pb_ds/tag_and_trait.hpp>

    #include <ext/pb_ds/tree_policy.hpp>

    using namespace __gnu_pbds; // find_by_order(), order_of_key()

    template <typename TK> using pbds_set = tree<TK, null_type, less<TK>, rb_tree_tag,
    tree_order_statistics_node_update>;

    template <typename TK, typename TV> using pbds_map = tree<TK, TV, less<TK>, rb_tree_tag,
    tree_order_statistics_node_update>;

    '
  code: '#pragma once


    // CUT begin

    #include <ext/pb_ds/assoc_container.hpp>

    #include <ext/pb_ds/tag_and_trait.hpp>

    #include <ext/pb_ds/tree_policy.hpp>

    using namespace __gnu_pbds; // find_by_order(), order_of_key()

    template <typename TK> using pbds_set = tree<TK, null_type, less<TK>, rb_tree_tag,
    tree_order_statistics_node_update>;

    template <typename TK, typename TV> using pbds_map = tree<TK, TV, less<TK>, rb_tree_tag,
    tree_order_statistics_node_update>;

    '
  dependsOn: []
  isVerificationFile: false
  path: utilities/gnu_pbds.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/gnu_pbds.hpp
layout: document
redirect_from:
- /library/utilities/gnu_pbds.hpp
- /library/utilities/gnu_pbds.hpp.html
title: utilities/gnu_pbds.hpp
---
