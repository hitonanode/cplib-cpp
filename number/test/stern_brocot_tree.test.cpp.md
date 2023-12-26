---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/stern_brocot_tree.hpp
    title: "Stern\u2013Brocot tree"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/stern_brocot_tree
    links:
    - https://judge.yosupo.jp/problem/stern_brocot_tree
  bundledCode: "#line 1 \"number/test/stern_brocot_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n#line 2 \"number/stern_brocot_tree.hpp\"\
    \n\n#include <algorithm>\n#include <utility>\n#include <vector>\n\n// Stern\u2013\
    Brocot tree\n// Implementation based on https://miscalc.hatenablog.com/entry/2023/12/22/213007\n\
    namespace SternBrocotTree {\n\nusing T = long long;\n\nstruct Node {\n    // Subtree\
    \ contains all rational numbers in (p/q, r/s)\n    T p = 0, q = 1, r = 1, s =\
    \ 0; // root is (0, \\infty)\n\n    // (p + r) / (q + s)\n    T num() const {\
    \ return p + r; }\n    T den() const { return q + s; }\n};\n\nenum class Direction\
    \ { Left, Right };\n\nstruct Move {\n    Direction dir;\n    T steps;\n};\n\n\
    Node apply(Node node, const Move &mv) {\n    if (mv.dir == Direction::Left) {\n\
    \        node.r += node.p * mv.steps;\n        node.s += node.q * mv.steps;\n\
    \    } else {\n        node.p += node.r * mv.steps;\n        node.q += node.s\
    \ * mv.steps;\n    }\n    return node;\n}\n\n// path from root to num/den\nstd::vector<Move>\
    \ encode_path(T num, T den) {\n    std::vector<Move> ret;\n    bool left = false;\n\
    \n    while (num != den) {\n        T steps = num / den;\n        if (den * steps\
    \ == num) --steps;\n        num -= steps * den;\n        if (steps) ret.push_back({left\
    \ ? Direction::Left : Direction::Right, steps});\n\n        std::swap(num, den);\n\
    \        left = !left;\n    }\n\n    return ret;\n}\n\nNode decode_path(const\
    \ std::vector<Move> &path) {\n    Node ret{0, 1, 1, 0};\n    for (const Move &mv\
    \ : path) ret = apply(ret, mv);\n\n    return ret;\n}\n\nstd::vector<Move> lca_path(const\
    \ std::vector<Move> &path1, const std::vector<Move> &path2) {\n    std::vector<Move>\
    \ ret_path;\n\n    int i1 = 0, i2 = 0;\n    T step1 = path1.empty() ? 0 : path1.front().steps;\n\
    \    T step2 = path2.empty() ? 0 : path2.front().steps;\n\n    while (i1 < (int)path1.size()\
    \ and i2 < (int)path2.size()) {\n        if (!step1) {\n            ++i1;\n  \
    \          if (i1 < (int)path1.size()) step1 = path1.at(i1).steps;\n        }\
    \ else if (!step2) {\n            ++i2;\n            if (i2 < (int)path2.size())\
    \ step2 = path2.at(i2).steps;\n        } else {\n            if (path1.at(i1).dir\
    \ != path2.at(i2).dir) break;\n            T steps = std::min(step1, step2);\n\
    \            step1 -= steps;\n            step2 -= steps;\n\n            if (ret_path.empty()\
    \ or ret_path.back().dir != path1.at(i1).dir) {\n                Move move{path1.at(i1).dir,\
    \ steps};\n                ret_path.push_back(move);\n            } else {\n \
    \               ret_path.back().steps += steps;\n            }\n        }\n  \
    \  }\n\n    return ret_path;\n}\n\n} // namespace SternBrocotTree\n#line 3 \"\
    number/test/stern_brocot_tree.test.cpp\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <string>\n#line 8 \"number/test/stern_brocot_tree.test.cpp\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \n    int Q;\n    cin >> Q;\n    while (Q--) {\n        string type;\n       \
    \ cin >> type;\n        if (type == \"ENCODE_PATH\") {\n            long long\
    \ a, b;\n            cin >> a >> b;\n\n            auto path = SternBrocotTree::encode_path(a,\
    \ b);\n\n            cout << path.size();\n            for (auto mv : path) {\n\
    \                cout << ' ' << (mv.dir == SternBrocotTree::Direction::Left ?\
    \ 'L' : 'R') << ' '\n                     << mv.steps;\n            }\n      \
    \      cout << '\\n';\n        } else if (type == \"DECODE_PATH\") {\n       \
    \     std::vector<SternBrocotTree::Move> path;\n            int k;\n         \
    \   cin >> k;\n            while (k--) {\n                char dir;\n        \
    \        long long steps;\n                cin >> dir >> steps;\n            \
    \    path.push_back({dir == 'L' ? SternBrocotTree::Direction::Left\n         \
    \                                  : SternBrocotTree::Direction::Right,\n    \
    \                            steps});\n            }\n\n            auto node\
    \ = SternBrocotTree::decode_path(path);\n            cout << node.num() << ' '\
    \ << node.den() << '\\n';\n        } else if (type == \"LCA\") {\n           \
    \ long long a, b, c, d;\n            cin >> a >> b >> c >> d;\n\n            const\
    \ auto path1 = SternBrocotTree::encode_path(a, b);\n            const auto path2\
    \ = SternBrocotTree::encode_path(c, d);\n            const auto path = SternBrocotTree::lca_path(path1,\
    \ path2);\n            const auto ret = SternBrocotTree::decode_path(path);\n\
    \            cout << ret.num() << ' ' << ret.den() << '\\n';\n        } else if\
    \ (type == \"ANCESTOR\") {\n            long long k, a, b;\n            cin >>\
    \ k >> a >> b;\n\n            auto path = SternBrocotTree::encode_path(a, b);\n\
    \n            SternBrocotTree::Node node;\n            for (const auto &mv : path)\
    \ {\n                long long steps = min(mv.steps, k);\n                k -=\
    \ steps;\n                node = SternBrocotTree::apply(node, {mv.dir, steps});\n\
    \            }\n\n            if (k) {\n                cout << \"-1\\n\";\n \
    \           } else {\n                cout << node.num() << ' ' << node.den()\
    \ << '\\n';\n            }\n        } else if (type == \"RANGE\") {\n        \
    \    long long a, b;\n            cin >> a >> b;\n\n            auto path = SternBrocotTree::encode_path(a,\
    \ b);\n            auto node = SternBrocotTree::decode_path(path);\n         \
    \   cout << node.p << ' ' << node.q << ' ' << node.r << ' ' << node.s << '\\n';\n\
    \        } else {\n            assert(false);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n#include\
    \ \"../stern_brocot_tree.hpp\"\n\n#include <cassert>\n#include <iostream>\n#include\
    \ <string>\n#include <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n\n    int Q;\n    cin >> Q;\n    while (Q--)\
    \ {\n        string type;\n        cin >> type;\n        if (type == \"ENCODE_PATH\"\
    ) {\n            long long a, b;\n            cin >> a >> b;\n\n            auto\
    \ path = SternBrocotTree::encode_path(a, b);\n\n            cout << path.size();\n\
    \            for (auto mv : path) {\n                cout << ' ' << (mv.dir ==\
    \ SternBrocotTree::Direction::Left ? 'L' : 'R') << ' '\n                     <<\
    \ mv.steps;\n            }\n            cout << '\\n';\n        } else if (type\
    \ == \"DECODE_PATH\") {\n            std::vector<SternBrocotTree::Move> path;\n\
    \            int k;\n            cin >> k;\n            while (k--) {\n      \
    \          char dir;\n                long long steps;\n                cin >>\
    \ dir >> steps;\n                path.push_back({dir == 'L' ? SternBrocotTree::Direction::Left\n\
    \                                           : SternBrocotTree::Direction::Right,\n\
    \                                steps});\n            }\n\n            auto node\
    \ = SternBrocotTree::decode_path(path);\n            cout << node.num() << ' '\
    \ << node.den() << '\\n';\n        } else if (type == \"LCA\") {\n           \
    \ long long a, b, c, d;\n            cin >> a >> b >> c >> d;\n\n            const\
    \ auto path1 = SternBrocotTree::encode_path(a, b);\n            const auto path2\
    \ = SternBrocotTree::encode_path(c, d);\n            const auto path = SternBrocotTree::lca_path(path1,\
    \ path2);\n            const auto ret = SternBrocotTree::decode_path(path);\n\
    \            cout << ret.num() << ' ' << ret.den() << '\\n';\n        } else if\
    \ (type == \"ANCESTOR\") {\n            long long k, a, b;\n            cin >>\
    \ k >> a >> b;\n\n            auto path = SternBrocotTree::encode_path(a, b);\n\
    \n            SternBrocotTree::Node node;\n            for (const auto &mv : path)\
    \ {\n                long long steps = min(mv.steps, k);\n                k -=\
    \ steps;\n                node = SternBrocotTree::apply(node, {mv.dir, steps});\n\
    \            }\n\n            if (k) {\n                cout << \"-1\\n\";\n \
    \           } else {\n                cout << node.num() << ' ' << node.den()\
    \ << '\\n';\n            }\n        } else if (type == \"RANGE\") {\n        \
    \    long long a, b;\n            cin >> a >> b;\n\n            auto path = SternBrocotTree::encode_path(a,\
    \ b);\n            auto node = SternBrocotTree::decode_path(path);\n         \
    \   cout << node.p << ' ' << node.q << ' ' << node.r << ' ' << node.s << '\\n';\n\
    \        } else {\n            assert(false);\n        }\n    }\n}\n"
  dependsOn:
  - number/stern_brocot_tree.hpp
  isVerificationFile: true
  path: number/test/stern_brocot_tree.test.cpp
  requiredBy: []
  timestamp: '2023-12-26 22:44:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/stern_brocot_tree.test.cpp
layout: document
redirect_from:
- /verify/number/test/stern_brocot_tree.test.cpp
- /verify/number/test/stern_brocot_tree.test.cpp.html
title: number/test/stern_brocot_tree.test.cpp
---
