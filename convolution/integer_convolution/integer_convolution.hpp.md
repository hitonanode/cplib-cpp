---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://yukicoder.me/submissions/385043>
    - https://yukicoder.me/submissions/385120>
  bundledCode: "#line 1 \"convolution/integer_convolution/integer_convolution.hpp\"\
    \n#include <vector>\n\n// f[n]\u306En >= 1\u306B\u5BFE\u3057\u3066\u3001\u5168\
    \u3066\u306E\u500D\u6570n*i\u306B\u5BFE\u3059\u308Bf[n*i]\u306E\u548C\u304C\u51FA\
    \u3066\u304F\u308B \u8A08\u7B97\u91CFO(NlogN)\ntemplate <typename T>\nvoid integer_zeta(std::vector<T>\
    \ &f)\n{\n    int N = f.size() - 1;\n    for (int i = 1; i <= N; i++) {\n    \
    \    for (int j = i * 2; j <= N; j += i) {\n            f[i] += f[j];\n      \
    \  }\n    }\n}\n\n// f[n]\u306B\u5BFE\u3057\u3066\u3001\u5168\u3066\u306En\u306E\
    \u500D\u6570n*i\u306B\u5BFE\u3059\u308Bf[n*i]\u306E\u548C\u304C\u51FA\u3066\u304F\
    \u308B \u8A08\u7B97\u91CFO(NloglogN)\n// \u7D20\u6570p\u6BCE\u306B\u51E6\u7406\
    \u3059\u308B\u9AD8\u901F\u30BC\u30FC\u30BF\u5909\u63DB\n// \u4F7F\u7528\u4F8B\
    \ <https://yukicoder.me/submissions/385043>\ntemplate <typename T>\nvoid fast_integer_zeta(std::vector<T>\
    \ &f)\n{\n    int N = f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n\
    \    for (int p = 2; p <= N; p++) if (is_prime[p]) {\n        for (int q = p *\
    \ 2; q <= N; q += p) is_prime[q] = 0;\n        for (int j = N / p * p; j > 0;\
    \ j -= p) f[j / p] += f[j];\n    }\n}\n\n// fast_integer_zeta\u306E\u9006\u6F14\
    \u7B97 O(NloglogN)\n// \u4F7F\u7528\u4F8B <https://yukicoder.me/submissions/385120>\n\
    template <typename T>\nvoid fast_integer_moebius(std::vector<T> &f)\n{\n    int\
    \ N = f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p\
    \ = 2; p <= N; p++) if (is_prime[p]) {\n        for (int q = p * 2; q <= N; q\
    \ += p) is_prime[q] = 0;\n        for (int j = p; j <= N; j += p) f[j / p] -=\
    \ f[j];\n    }\n}\n"
  code: "#include <vector>\n\n// f[n]\u306En >= 1\u306B\u5BFE\u3057\u3066\u3001\u5168\
    \u3066\u306E\u500D\u6570n*i\u306B\u5BFE\u3059\u308Bf[n*i]\u306E\u548C\u304C\u51FA\
    \u3066\u304F\u308B \u8A08\u7B97\u91CFO(NlogN)\ntemplate <typename T>\nvoid integer_zeta(std::vector<T>\
    \ &f)\n{\n    int N = f.size() - 1;\n    for (int i = 1; i <= N; i++) {\n    \
    \    for (int j = i * 2; j <= N; j += i) {\n            f[i] += f[j];\n      \
    \  }\n    }\n}\n\n// f[n]\u306B\u5BFE\u3057\u3066\u3001\u5168\u3066\u306En\u306E\
    \u500D\u6570n*i\u306B\u5BFE\u3059\u308Bf[n*i]\u306E\u548C\u304C\u51FA\u3066\u304F\
    \u308B \u8A08\u7B97\u91CFO(NloglogN)\n// \u7D20\u6570p\u6BCE\u306B\u51E6\u7406\
    \u3059\u308B\u9AD8\u901F\u30BC\u30FC\u30BF\u5909\u63DB\n// \u4F7F\u7528\u4F8B\
    \ <https://yukicoder.me/submissions/385043>\ntemplate <typename T>\nvoid fast_integer_zeta(std::vector<T>\
    \ &f)\n{\n    int N = f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n\
    \    for (int p = 2; p <= N; p++) if (is_prime[p]) {\n        for (int q = p *\
    \ 2; q <= N; q += p) is_prime[q] = 0;\n        for (int j = N / p * p; j > 0;\
    \ j -= p) f[j / p] += f[j];\n    }\n}\n\n// fast_integer_zeta\u306E\u9006\u6F14\
    \u7B97 O(NloglogN)\n// \u4F7F\u7528\u4F8B <https://yukicoder.me/submissions/385120>\n\
    template <typename T>\nvoid fast_integer_moebius(std::vector<T> &f)\n{\n    int\
    \ N = f.size() - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p\
    \ = 2; p <= N; p++) if (is_prime[p]) {\n        for (int q = p * 2; q <= N; q\
    \ += p) is_prime[q] = 0;\n        for (int j = p; j <= N; j += p) f[j / p] -=\
    \ f[j];\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: convolution/integer_convolution/integer_convolution.hpp
  requiredBy: []
  timestamp: '2020-04-05 20:29:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convolution/integer_convolution/integer_convolution.hpp
layout: document
redirect_from:
- /library/convolution/integer_convolution/integer_convolution.hpp
- /library/convolution/integer_convolution/integer_convolution.hpp.html
title: convolution/integer_convolution/integer_convolution.hpp
---
