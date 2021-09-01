---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/matroids/matroid_example.hpp\"\n#include\
    \ <vector>\n\nstruct MatroidExample {\n    using Element = int;\n\n    int size()\
    \ const; // # of elements of set we consider\n\n    // If I is independent and\
    \ I + {e} is not, return elements of the circuit.\n    // If e \\in I, or I +\
    \ {e} is independent, return empty vector.\n    // If I is NOT independent, undefined.\n\
    \    template <class State = std::vector<bool>> void set(State I);\n    std::vector<Element>\
    \ circuit(Element e) const;\n};\n"
  code: "#pragma once\n#include <vector>\n\nstruct MatroidExample {\n    using Element\
    \ = int;\n\n    int size() const; // # of elements of set we consider\n\n    //\
    \ If I is independent and I + {e} is not, return elements of the circuit.\n  \
    \  // If e \\in I, or I + {e} is independent, return empty vector.\n    // If\
    \ I is NOT independent, undefined.\n    template <class State = std::vector<bool>>\
    \ void set(State I);\n    std::vector<Element> circuit(Element e) const;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/matroid_example.hpp
  requiredBy: []
  timestamp: '2021-09-01 23:53:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroids/matroid_example.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/matroids/matroid_example.hpp
- /library/combinatorial_opt/matroids/matroid_example.hpp.html
title: combinatorial_opt/matroids/matroid_example.hpp
---
