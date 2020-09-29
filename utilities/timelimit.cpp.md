---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/timelimit.cpp\"\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\n\n\nint main()\n{\n    auto START = std::chrono::system_clock::now();\n\
    \    if (chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START).count() > 4900)\n    {\n        /* Calculation */\n\n        cout <<\
    \ 0 << endl;\n        return 0;\n    }\n}\n"
  code: "#include <bits/stdc++.h>\nusing namespace std;\n\n\nint main()\n{\n    auto\
    \ START = std::chrono::system_clock::now();\n    if (chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START).count() > 4900)\n    {\n        /* Calculation */\n\n        cout <<\
    \ 0 << endl;\n        return 0;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/timelimit.cpp
  requiredBy: []
  timestamp: '2020-09-29 18:47:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/timelimit.cpp
layout: document
redirect_from:
- /library/utilities/timelimit.cpp
- /library/utilities/timelimit.cpp.html
title: utilities/timelimit.cpp
---
