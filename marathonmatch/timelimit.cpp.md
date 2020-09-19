---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"marathonmatch/timelimit.cpp\"\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n\nint main()\n{\n    auto START = std::chrono::system_clock::now();\n\
    \    if (chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START).count() > 4900)\n    {\n        /* Calculation */\n\n        cout <<\
    \ 0 << endl;\n        return 0;\n    }\n}\n"
  code: "#include <bits/stdc++.h>\nusing namespace std;\n\n\nint main()\n{\n    auto\
    \ START = std::chrono::system_clock::now();\n    if (chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START).count() > 4900)\n    {\n        /* Calculation */\n\n        cout <<\
    \ 0 << endl;\n        return 0;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: marathonmatch/timelimit.cpp
  requiredBy: []
  timestamp: '2019-08-10 15:16:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: marathonmatch/timelimit.cpp
layout: document
redirect_from:
- /library/marathonmatch/timelimit.cpp
- /library/marathonmatch/timelimit.cpp.html
title: marathonmatch/timelimit.cpp
---
