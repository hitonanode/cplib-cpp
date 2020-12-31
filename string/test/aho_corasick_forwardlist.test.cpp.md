---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../other_data_structures/light_forward_list.hpp:\
    \ line -1: no such header\n"
  code: "#include \"../aho_corasick.hpp\"\n#include <iostream>\nusing namespace std;\n\
    #define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    AhoCorasick<TrieNodeFL,\
    \ c2i0aA> trie(62);\n    string T, P;\n    int Q;\n    cin >> T >> Q;\n    while\
    \ (Q--) cin >> P, trie.add(P);\n\n    trie.build_aho_corasick();\n    for (auto\
    \ n : trie.match(T)) cout << !!n << '\\n';\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: string/test/aho_corasick_forwardlist.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: string/test/aho_corasick_forwardlist.test.cpp
layout: document
redirect_from:
- /verify/string/test/aho_corasick_forwardlist.test.cpp
- /verify/string/test/aho_corasick_forwardlist.test.cpp.html
title: string/test/aho_corasick_forwardlist.test.cpp
---
