---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/palindromic_tree.yuki2606.test.cpp
    title: string/test/palindromic_tree.yuki2606.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/palindromic_tree.yuki263.test.cpp
    title: string/test/palindromic_tree.yuki263.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/palindromic_tree.hpp\"\n\n#include <map>\n#include\
    \ <string>\n#include <vector>\n\n// Palindromic tree / Eertree \uFF08\u56DE\u6587\
    \u6728\uFF09\nnamespace palindromic_tree {\n\ntemplate <class Key> class Node\
    \ {\n    int suffix_link_; // \u3053\u306E\u30CE\u30FC\u30C9\u304B\u3089\u306E\
    suffix link \uFF08suffix \u306E\u6700\u9577\u56DE\u6587\uFF09\n    int length_;\
    \ // \u3053\u306E\u30CE\u30FC\u30C9\u304C\u8868\u3059\u56DE\u6587\u306E\u9577\u3055\
    \u3002 -1 \u3068\u306A\u308B\u5834\u5408\u3082\u3042\u308B\u306E\u3067\u6CE8\u610F\
    \n    std::map<Key, int> children;\n\npublic:\n    explicit Node(int suffix_link,\
    \ int length) : suffix_link_(suffix_link), length_(length) {}\n\n    int suffix_link()\
    \ const { return suffix_link_; }\n\n    int length() const { return length_; }\n\
    \n    int get_child(Key c) const {\n        auto it = children.find(c);\n    \
    \    return (it == children.end()) ? -1 : it->second;\n    }\n\n    void set_child(int\
    \ c, int nxt_idx) { children[c] = nxt_idx; }\n\n    template <class OStream> friend\
    \ OStream &operator<<(OStream &os, const Node &node) {\n        os << \"Node(suffix_link=\"\
    \ << node.suffix_link() << \", length=\" << node.length()\n           << \", children={\"\
    ;\n        for (const auto &[c, nxt] : node.children) os << c << \"->\" << nxt\
    \ << \", \";\n        return os << \"})\";\n    }\n};\n\n// Palindromic tree\n\
    // nodes[0] \u306F\u9577\u3055 -1, nodes[1] \u306F\u9577\u3055 1 \u306E\u30C0\u30DF\
    \u30FC\u30CE\u30FC\u30C9\ntemplate <class Key> struct Tree {\n    std::vector<Node<Key>>\
    \ nodes;\n\n    Tree() { nodes = {Node<Key>(-1, -1), Node<Key>(0, 0)}; }\n\n \
    \   // nodes[cursor] \u306F s[0:i] \u306E suffix palindrome \u3092\u8868\u3059\
    \n    // \u672C\u95A2\u6570\u306F\u305D\u306E nodes[cursor] \u306E suffix palindrome\
    \ \u3067\u3042\u3063\u3066\u66F4\u306B s[0:(i + 1)] \u306E suffix link \u3068\u306A\
    \u308A\u3046\u308B\u6700\u9577\u306E\u3082\u306E\u3092\u8FD4\u3059\n    int find_next_suffix(const\
    \ std::vector<Key> &s, int i, int cursor) {\n        while (true) {\n        \
    \    if (cursor < 0) return 0;\n\n            const int cur_len = nodes.at(cursor).length();\n\
    \            const int opposite_pos = i - cur_len - 1;\n            if (opposite_pos\
    \ >= 0 and s.at(opposite_pos) == s.at(i)) return cursor;\n            cursor =\
    \ nodes.at(cursor).suffix_link();\n        }\n    }\n\n    // \u6587\u5B57\u5217\
    \ s \u3092\u8FFD\u52A0\u3059\u308B\u3002 Complexity: O(|s|)\n    // callback(i,\
    \ cursor) \u306F s[0:(i + 1)] \u304C\u8FFD\u52A0\u3055\u308C\u305F\u5F8C\u306E\
    \ nodes[cursor] \u306B\u5BFE\u3057\u3066\u884C\u3046\u51E6\u7406\n    template\
    \ <class Callback> void add_string(const std::vector<Key> &s, Callback callback)\
    \ {\n        int cursor = 1;\n\n        for (int i = 0; i < (int)s.size(); ++i)\
    \ {\n\n            cursor = find_next_suffix(s, i, cursor);\n\n            int\
    \ ch = nodes.at(cursor).get_child(s.at(i));\n\n            if (ch < 0) {\n   \
    \             const int nxt_cursor = nodes.size();\n                const int\
    \ new_length = nodes.at(cursor).length() + 2;\n\n                int new_suffix_link_par\
    \ = find_next_suffix(s, i, nodes.at(cursor).suffix_link());\n                int\
    \ new_suffix_link = nodes.at(new_suffix_link_par).get_child(s.at(i));\n      \
    \          if (new_suffix_link < 0) new_suffix_link = 1;\n\n                nodes.at(cursor).set_child(s.at(i),\
    \ nxt_cursor);\n                nodes.push_back(Node<Key>(new_suffix_link, new_length));\n\
    \                cursor = nxt_cursor;\n\n            } else {\n              \
    \  cursor = ch;\n            }\n\n            callback(i, cursor);\n        }\n\
    \    }\n\n    template <class Callback> void add_string(const std::string &s,\
    \ Callback callback) {\n        add_string(std::vector<Key>{s.cbegin(), s.cend()},\
    \ callback);\n    }\n\n    template <class Vec> void add_string(const Vec &s)\
    \ {\n        add_string(s, [](int, int) {});\n    }\n};\n\n} // namespace palindromic_tree\n"
  code: "#pragma once\n\n#include <map>\n#include <string>\n#include <vector>\n\n\
    // Palindromic tree / Eertree \uFF08\u56DE\u6587\u6728\uFF09\nnamespace palindromic_tree\
    \ {\n\ntemplate <class Key> class Node {\n    int suffix_link_; // \u3053\u306E\
    \u30CE\u30FC\u30C9\u304B\u3089\u306Esuffix link \uFF08suffix \u306E\u6700\u9577\
    \u56DE\u6587\uFF09\n    int length_; // \u3053\u306E\u30CE\u30FC\u30C9\u304C\u8868\
    \u3059\u56DE\u6587\u306E\u9577\u3055\u3002 -1 \u3068\u306A\u308B\u5834\u5408\u3082\
    \u3042\u308B\u306E\u3067\u6CE8\u610F\n    std::map<Key, int> children;\n\npublic:\n\
    \    explicit Node(int suffix_link, int length) : suffix_link_(suffix_link), length_(length)\
    \ {}\n\n    int suffix_link() const { return suffix_link_; }\n\n    int length()\
    \ const { return length_; }\n\n    int get_child(Key c) const {\n        auto\
    \ it = children.find(c);\n        return (it == children.end()) ? -1 : it->second;\n\
    \    }\n\n    void set_child(int c, int nxt_idx) { children[c] = nxt_idx; }\n\n\
    \    template <class OStream> friend OStream &operator<<(OStream &os, const Node\
    \ &node) {\n        os << \"Node(suffix_link=\" << node.suffix_link() << \", length=\"\
    \ << node.length()\n           << \", children={\";\n        for (const auto &[c,\
    \ nxt] : node.children) os << c << \"->\" << nxt << \", \";\n        return os\
    \ << \"})\";\n    }\n};\n\n// Palindromic tree\n// nodes[0] \u306F\u9577\u3055\
    \ -1, nodes[1] \u306F\u9577\u3055 1 \u306E\u30C0\u30DF\u30FC\u30CE\u30FC\u30C9\
    \ntemplate <class Key> struct Tree {\n    std::vector<Node<Key>> nodes;\n\n  \
    \  Tree() { nodes = {Node<Key>(-1, -1), Node<Key>(0, 0)}; }\n\n    // nodes[cursor]\
    \ \u306F s[0:i] \u306E suffix palindrome \u3092\u8868\u3059\n    // \u672C\u95A2\
    \u6570\u306F\u305D\u306E nodes[cursor] \u306E suffix palindrome \u3067\u3042\u3063\
    \u3066\u66F4\u306B s[0:(i + 1)] \u306E suffix link \u3068\u306A\u308A\u3046\u308B\
    \u6700\u9577\u306E\u3082\u306E\u3092\u8FD4\u3059\n    int find_next_suffix(const\
    \ std::vector<Key> &s, int i, int cursor) {\n        while (true) {\n        \
    \    if (cursor < 0) return 0;\n\n            const int cur_len = nodes.at(cursor).length();\n\
    \            const int opposite_pos = i - cur_len - 1;\n            if (opposite_pos\
    \ >= 0 and s.at(opposite_pos) == s.at(i)) return cursor;\n            cursor =\
    \ nodes.at(cursor).suffix_link();\n        }\n    }\n\n    // \u6587\u5B57\u5217\
    \ s \u3092\u8FFD\u52A0\u3059\u308B\u3002 Complexity: O(|s|)\n    // callback(i,\
    \ cursor) \u306F s[0:(i + 1)] \u304C\u8FFD\u52A0\u3055\u308C\u305F\u5F8C\u306E\
    \ nodes[cursor] \u306B\u5BFE\u3057\u3066\u884C\u3046\u51E6\u7406\n    template\
    \ <class Callback> void add_string(const std::vector<Key> &s, Callback callback)\
    \ {\n        int cursor = 1;\n\n        for (int i = 0; i < (int)s.size(); ++i)\
    \ {\n\n            cursor = find_next_suffix(s, i, cursor);\n\n            int\
    \ ch = nodes.at(cursor).get_child(s.at(i));\n\n            if (ch < 0) {\n   \
    \             const int nxt_cursor = nodes.size();\n                const int\
    \ new_length = nodes.at(cursor).length() + 2;\n\n                int new_suffix_link_par\
    \ = find_next_suffix(s, i, nodes.at(cursor).suffix_link());\n                int\
    \ new_suffix_link = nodes.at(new_suffix_link_par).get_child(s.at(i));\n      \
    \          if (new_suffix_link < 0) new_suffix_link = 1;\n\n                nodes.at(cursor).set_child(s.at(i),\
    \ nxt_cursor);\n                nodes.push_back(Node<Key>(new_suffix_link, new_length));\n\
    \                cursor = nxt_cursor;\n\n            } else {\n              \
    \  cursor = ch;\n            }\n\n            callback(i, cursor);\n        }\n\
    \    }\n\n    template <class Callback> void add_string(const std::string &s,\
    \ Callback callback) {\n        add_string(std::vector<Key>{s.cbegin(), s.cend()},\
    \ callback);\n    }\n\n    template <class Vec> void add_string(const Vec &s)\
    \ {\n        add_string(s, [](int, int) {});\n    }\n};\n\n} // namespace palindromic_tree\n"
  dependsOn: []
  isVerificationFile: false
  path: string/palindromic_tree.hpp
  requiredBy: []
  timestamp: '2024-05-03 18:26:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/palindromic_tree.yuki2606.test.cpp
  - string/test/palindromic_tree.yuki263.test.cpp
documentation_of: string/palindromic_tree.hpp
layout: document
title: "Palindromic tree / eertree \uFF08\u56DE\u6587\u6728\uFF09"
---

文字列に現れる回文を効率的に管理するデータ構造．与えられた文字列 $S$ に対して $O(|S| \log \sigma)$ $(\sigma = |\Sigma|)$ で構築可能．

## eertree とは

- 各頂点が，与えられた文字列の（連続）部分文字列である distinct な回文に対応する．
  - 例外として，長さ $-1$, $0$ の空文字列を表現するダミーの頂点がそれぞれ存在する．したがって頂点数は正確には回文の種類数 +2 となる．
  - 頂点数は $|S| + 2$ 以下である．
- 各頂点から，その回文の suffix である最長回文の頂点への辺 (suffix link) が生えている．
  - 例外として，長さ $0$ の空文字列のダミー頂点の suffix link は長さ $-1$ の空文字列へ生えている．
  - 長さ $-1$ の空文字列の suffix link は存在しない．つまり， suffix link を辺としたグラフはこの頂点を根とする根付き木となる．

## 使用方法

```cpp
string S = "sakanakanandaka";
palindromic_tree::Tree<char> tree;
tree.add_string(S);

// コールバック関数も使用可能．
// 第一引数は S 上の index (0, ..., |S| - 1), 第二引数は tree.nodes の index.
// 1 文字読む毎に tree 上のどこにいるか分かるので出現回数カウント等が可能．
vector<int> dp(S.size() + 2);
auto callback = [&](int str_idx, int node_idx) -> void { dp.at(node_idx)++; };

tree.add_string(S, callback);
```

## 問題例

- [No.263 Common Palindromes Extra - yukicoder](https://yukicoder.me/problems/no/263)
- [No.2606 Mirror Relay - yukicoder](https://yukicoder.me/problems/no/2606)

## 参考文献・リンク

- [1] M. Rubinchik and A. M. Shur, "EERTREE: An efficient data structure for processing palindromes in strings," European Journal of Combinatorics 68, 249-265, 2018. [arXiv](https://arxiv.org/abs/1506.04862)
- [Palindromic Tree - math314のブログ](https://math314.hateblo.jp/entry/2016/12/19/005919)
- [すごい！EERTREE！いごす - 誤読](https://mojashi.hatenablog.com/entry/2017/07/17/155520)
