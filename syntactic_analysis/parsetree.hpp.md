---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/bitflyer2018-final-open/submissions/3529930>
  bundledCode: "#line 2 \"syntactic_analysis/parsetree.hpp\"\n#include <string>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// \u69CB\u6587\u89E3\u6790\
    \u6728\u306E\u69CB\u7BC9\n// Verification: codeFlyer E\n// Example: <https://atcoder.jp/contests/bitflyer2018-final-open/submissions/3529930>\n\
    struct Parser {\n    // \u69CB\u6587\u6728\u60C5\u5831\n    int root_id;\n   \
    \ std::vector<std::pair<int, int>> child;\n    std::string S;\n\n    // \u6728\
    \u306E\u30CE\u30FC\u30C9\u306E\u60C5\u5831\uFF08\u554F\u984C\u6BCE\u306B\u66F8\
    \u304D\u63DB\u3048\u308B\uFF09\n    struct Node {\n        long long val, val2;\n\
    \        char type;\n        int a_id;\n        Node() {}\n        Node(char type,\
    \ int a_id) : type(type), a_id(a_id) {}\n    };\n    std::vector<Node> node;\n\
    \n    int len;\n    void allocate(int newlen) {\n        len = newlen;\n     \
    \   child.assign(len, std::make_pair(-1, -1));\n        node.assign(len, {});\n\
    \    }\n\n    Parser(int initlen, std::string &str) : S(str) { allocate(initlen);\
    \ }\n\n    int nodeNow = 0;\n    int _new_node() { return nodeNow++; }\n\n   \
    \ int a_now;\n    int iter;\n    int interpret() {\n        iter = a_now = 0;\n\
    \        return root_id = expr(iter);\n    }\n\n    int expr(int &begin) {\n \
    \       int left = term(begin);\n        while (S[begin] == '+' || S[begin] ==\
    \ '-') {\n            char nxt_token = S[begin];\n            int new_node = _new_node();\n\
    \            begin++;\n            int right = term(begin);\n            node[new_node].type\
    \ = nxt_token;\n            child[new_node] = std::make_pair(left, right);\n \
    \           left = new_node;\n        }\n        return left;\n    }\n\n    int\
    \ term(int &begin) {\n        int left = value(begin);\n        while (S[begin]\
    \ == '*') {\n            int new_node = _new_node();\n            begin++;\n \
    \           int right = value(begin);\n            node[new_node].type = '*';\n\
    \            child[new_node] = std::make_pair(left, right);\n            left\
    \ = new_node;\n        }\n        return left;\n    }\n\n    int value(int &begin)\
    \ {\n        if (S[begin] == '(') {\n            begin++;\n            int ret\
    \ = expr(begin);\n            begin++;\n            return ret;\n        } else\
    \ {\n            int ret = _new_node();\n            node[ret].type = 'a';\n \
    \           node[ret].a_id = a_now++;\n            begin++;\n            return\
    \ ret;\n        }\n    }\n\n    void dfs(int now) {\n        int l = child[now].first,\
    \ r = child[now].second;\n        /* operations for node[now], node[l], node[r]\
    \ here */\n        if (l >= 0) dfs(child[now].first);\n        if (r >= 0) dfs(child[now].second);\n\
    \        /* operations for node[now], node[l], node[r] here */\n    }\n};\n\n\
    /* example usage\nstd::string S;\nParser parser(200000, S);\nauto root = parser.interpret();\n\
    parser.dfs(root);\n*/\n"
  code: "#pragma once\n#include <string>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// \u69CB\u6587\u89E3\u6790\u6728\u306E\u69CB\u7BC9\n// Verification:\
    \ codeFlyer E\n// Example: <https://atcoder.jp/contests/bitflyer2018-final-open/submissions/3529930>\n\
    struct Parser {\n    // \u69CB\u6587\u6728\u60C5\u5831\n    int root_id;\n   \
    \ std::vector<std::pair<int, int>> child;\n    std::string S;\n\n    // \u6728\
    \u306E\u30CE\u30FC\u30C9\u306E\u60C5\u5831\uFF08\u554F\u984C\u6BCE\u306B\u66F8\
    \u304D\u63DB\u3048\u308B\uFF09\n    struct Node {\n        long long val, val2;\n\
    \        char type;\n        int a_id;\n        Node() {}\n        Node(char type,\
    \ int a_id) : type(type), a_id(a_id) {}\n    };\n    std::vector<Node> node;\n\
    \n    int len;\n    void allocate(int newlen) {\n        len = newlen;\n     \
    \   child.assign(len, std::make_pair(-1, -1));\n        node.assign(len, {});\n\
    \    }\n\n    Parser(int initlen, std::string &str) : S(str) { allocate(initlen);\
    \ }\n\n    int nodeNow = 0;\n    int _new_node() { return nodeNow++; }\n\n   \
    \ int a_now;\n    int iter;\n    int interpret() {\n        iter = a_now = 0;\n\
    \        return root_id = expr(iter);\n    }\n\n    int expr(int &begin) {\n \
    \       int left = term(begin);\n        while (S[begin] == '+' || S[begin] ==\
    \ '-') {\n            char nxt_token = S[begin];\n            int new_node = _new_node();\n\
    \            begin++;\n            int right = term(begin);\n            node[new_node].type\
    \ = nxt_token;\n            child[new_node] = std::make_pair(left, right);\n \
    \           left = new_node;\n        }\n        return left;\n    }\n\n    int\
    \ term(int &begin) {\n        int left = value(begin);\n        while (S[begin]\
    \ == '*') {\n            int new_node = _new_node();\n            begin++;\n \
    \           int right = value(begin);\n            node[new_node].type = '*';\n\
    \            child[new_node] = std::make_pair(left, right);\n            left\
    \ = new_node;\n        }\n        return left;\n    }\n\n    int value(int &begin)\
    \ {\n        if (S[begin] == '(') {\n            begin++;\n            int ret\
    \ = expr(begin);\n            begin++;\n            return ret;\n        } else\
    \ {\n            int ret = _new_node();\n            node[ret].type = 'a';\n \
    \           node[ret].a_id = a_now++;\n            begin++;\n            return\
    \ ret;\n        }\n    }\n\n    void dfs(int now) {\n        int l = child[now].first,\
    \ r = child[now].second;\n        /* operations for node[now], node[l], node[r]\
    \ here */\n        if (l >= 0) dfs(child[now].first);\n        if (r >= 0) dfs(child[now].second);\n\
    \        /* operations for node[now], node[l], node[r] here */\n    }\n};\n\n\
    /* example usage\nstd::string S;\nParser parser(200000, S);\nauto root = parser.interpret();\n\
    parser.dfs(root);\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: syntactic_analysis/parsetree.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: syntactic_analysis/parsetree.hpp
layout: document
redirect_from:
- /library/syntactic_analysis/parsetree.hpp
- /library/syntactic_analysis/parsetree.hpp.html
title: syntactic_analysis/parsetree.hpp
---
