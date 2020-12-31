---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/light_forward_list.hpp
    title: other_data_structures/light_forward_list.hpp
  - icon: ':heavy_check_mark:'
    path: string/incremental_matching.hpp
    title: string/incremental_matching.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
  bundledCode: "#line 1 \"string/test/incremental_matching.test.cpp\"\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing lint = long long;\nusing pint = pair<int, int>;\n\
    using plint = pair<lint, lint>;\nstruct fast_ios {\n    fast_ios() { cin.tie(nullptr),\
    \ ios::sync_with_stdio(false), cout << fixed << setprecision(20); };\n} fast_ios_;\n\
    #define ALL(x) (x).begin(), (x).end()\n#define FOR(i, begin, end) for (int i =\
    \ (begin), i##_end_ = (end); i < i##_end_; i++)\n#define IFOR(i, begin, end) for\
    \ (int i = (end)-1, i##_begin_ = (begin); i >= i##_begin_; i--)\n#define REP(i,\
    \ n) FOR(i, 0, n)\n#define IREP(i, n) IFOR(i, 0, n)\ntemplate <typename T, typename\
    \ V> void ndarray(vector<T> &vec, const V &val, int len) { vec.assign(len, val);\
    \ }\ntemplate <typename T, typename V, typename... Args> void ndarray(vector<T>\
    \ &vec, const V &val, int len, Args... args) {\n    vec.resize(len), for_each(begin(vec),\
    \ end(vec), [&](T &v) { ndarray(v, val, args...); });\n}\ntemplate <typename T>\
    \ bool chmax(T &m, const T q) {\n    if (m < q) {\n        m = q;\n        return\
    \ true;\n    } else\n        return false;\n}\ntemplate <typename T> bool chmin(T\
    \ &m, const T q) {\n    if (m > q) {\n        m = q;\n        return true;\n \
    \   } else\n        return false;\n}\nint floor_lg(long long x) { return x <=\
    \ 0 ? -1 : 63 - __builtin_clzll(x); }\ntemplate <typename T1, typename T2> pair<T1,\
    \ T2> operator+(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first\
    \ + r.first, l.second + r.second); }\ntemplate <typename T1, typename T2> pair<T1,\
    \ T2> operator-(const pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first\
    \ - r.first, l.second - r.second); }\ntemplate <typename T> vector<T> sort_unique(vector<T>\
    \ vec) {\n    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()),\
    \ vec.end());\n    return vec;\n}\ntemplate <typename T> istream &operator>>(istream\
    \ &is, vector<T> &vec) {\n    for (auto &v : vec) is >> v;\n    return is;\n}\n\
    template <typename T> ostream &operator<<(ostream &os, const vector<T> &vec) {\n\
    \    os << '[';\n    for (auto v : vec) os << v << ',';\n    os << ']';\n    return\
    \ os;\n}\ntemplate <typename T, size_t sz> ostream &operator<<(ostream &os, const\
    \ array<T, sz> &arr) {\n    os << '[';\n    for (auto v : arr) os << v << ',';\n\
    \    os << ']';\n    return os;\n}\n#if __cplusplus >= 201703L\ntemplate <typename...\
    \ T> istream &operator>>(istream &is, tuple<T...> &tpl) {\n    std::apply([&is](auto\
    \ &&... args) { ((is >> args), ...); }, tpl);\n    return is;\n}\ntemplate <typename...\
    \ T> ostream &operator<<(ostream &os, const tuple<T...> &tpl) {\n    std::apply([&os](auto\
    \ &&... args) { ((os << args << ','), ...); }, tpl);\n    return os;\n}\n#endif\n\
    template <typename T> ostream &operator<<(ostream &os, const deque<T> &vec) {\n\
    \    os << \"deq[\";\n    for (auto v : vec) os << v << ',';\n    os << ']';\n\
    \    return os;\n}\ntemplate <typename T> ostream &operator<<(ostream &os, const\
    \ set<T> &vec) {\n    os << '{';\n    for (auto v : vec) os << v << ',';\n   \
    \ os << '}';\n    return os;\n}\ntemplate <typename T, typename TH> ostream &operator<<(ostream\
    \ &os, const unordered_set<T, TH> &vec) {\n    os << '{';\n    for (auto v : vec)\
    \ os << v << ',';\n    os << '}';\n    return os;\n}\ntemplate <typename T> ostream\
    \ &operator<<(ostream &os, const multiset<T> &vec) {\n    os << '{';\n    for\
    \ (auto v : vec) os << v << ',';\n    os << '}';\n    return os;\n}\ntemplate\
    \ <typename T> ostream &operator<<(ostream &os, const unordered_multiset<T> &vec)\
    \ {\n    os << '{';\n    for (auto v : vec) os << v << ',';\n    os << '}';\n\
    \    return os;\n}\ntemplate <typename T1, typename T2> ostream &operator<<(ostream\
    \ &os, const pair<T1, T2> &pa) {\n    os << '(' << pa.first << ',' << pa.second\
    \ << ')';\n    return os;\n}\ntemplate <typename TK, typename TV> ostream &operator<<(ostream\
    \ &os, const map<TK, TV> &mp) {\n    os << '{';\n    for (auto v : mp) os << v.first\
    \ << \"=>\" << v.second << ',';\n    os << '}';\n    return os;\n}\ntemplate <typename\
    \ TK, typename TV, typename TH> ostream &operator<<(ostream &os, const unordered_map<TK,\
    \ TV, TH> &mp) {\n    os << '{';\n    for (auto v : mp) os << v.first << \"=>\"\
    \ << v.second << ',';\n    os << '}';\n    return os;\n}\n#ifdef HITONANODE_LOCAL\n\
    const string COLOR_RESET = \"\\033[0m\", BRIGHT_GREEN = \"\\033[1;32m\", BRIGHT_RED\
    \ = \"\\033[1;31m\", BRIGHT_CYAN = \"\\033[1;36m\", NORMAL_CROSSED = \"\\033[0;9;37m\"\
    , RED_BACKGROUND = \"\\033[1;41m\", NORMAL_FAINT = \"\\033[0;2m\";\n#define dbg(x)\
    \ cerr << BRIGHT_CYAN << #x << COLOR_RESET << \" = \" << (x) << NORMAL_FAINT <<\
    \ \" (L\" << __LINE__ << \") \" << __FILE__ << COLOR_RESET << endl\n#else\n#define\
    \ dbg(x)                                                                     \
    \                                                                            \
    \                                                                            \
    \                                                                            \
    \                                                                            \
    \            \\\n    {}\n#endif\n\n#line 3 \"other_data_structures/light_forward_list.hpp\"\
    \n\n// CUT begin\n// Simple forward_list for MLE-sensitive situations\n// Verify:\
    \ <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\ntemplate\
    \ <typename T> struct light_forward_list {\n    static std::vector<unsigned> ptr;\n\
    \    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {0};\n\
    #line 8 \"string/incremental_matching.hpp\"\n\n// CUT begin\n// [1] B. Meyer,\
    \ \"Incremental String Matching,\" Information Processing Letters, 21(5), 1985.\n\
    //\n// (Dynamic version of Aho-Corasick algorithm)\n// Complexity:\n// - add():\
    \ O(|keyword_i|)\n// - match() : O(\\sum_i |keyword_i| + |str|)\ntemplate <class\
    \ T, int (*char2int)(char)> struct IncrementalMatching {\n    const int D;\n \
    \   std::vector<T> node;\n    IncrementalMatching(int D_) : D(D_), node(1, D)\
    \ {}\n\n    void enter_child(int n, int nn, int c) {\n        complete_failure(n,\
    \ nn, c);\n        node[n].setch(c, nn);\n        int fnn = node[nn].fail;\n \
    \       node[fnn].inv_fail.insert(nn);\n        complete_inverse(n, nn, c);\n\
    \    }\n\n    void complete_inverse(const int y, const int nn, const int c) {\n\
    \        for (auto x : node[y].inv_fail) {\n            const int xx = node[x].Goto(c);\n\
    \            if (xx) {\n                const int fxx = node[xx].fail;\n     \
    \           node[fxx].inv_fail.erase(xx);\n                node[xx].fail = nn,\
    \ node[nn].inv_fail.insert(xx);\n            } else {\n                complete_inverse(x,\
    \ nn, c);\n            }\n        }\n    }\n\n    std::vector<int> endpos;\n \
    \   int add(const std::string &keyword) { // Enter_in_tree() in [1]\n        assert(keyword.length()\
    \ > 0);\n        int n = 0;\n        for (const auto &cc : keyword) {\n      \
    \      int c = char2int(cc), nn = node[n].Goto(c);\n            if (!nn) {\n \
    \               nn = node.size();\n                node.emplace_back(D), enter_child(n,\
    \ nn, c);\n            }\n            n = nn;\n        }\n        return endpos.push_back(n),\
    \ n;\n    }\n\n    void complete_failure(int n, int nn, int c) {\n        int\
    \ m = n, Tmc = node[m].Goto(c);\n        while (m and !Tmc) m = node[m].fail,\
    \ Tmc = node[m].Goto(c);\n        node[nn].fail = Tmc;\n    }\n\n    std::vector<int>\
    \ visorder; // BFS order of node ids\n    void build_bfs() {         // Build_failure()\
    \ in [1]\n        visorder.clear();\n        for (int c = 0; c < D; c++) {\n \
    \           int u = node[0].Goto(c);\n            if (u) visorder.push_back(u);\n\
    \        }\n        for (size_t p = 0; p < visorder.size(); p++) {\n         \
    \   int n = visorder[p];\n            for (int c = 0; c < D; c++) {\n        \
    \        const int nn = node[n].Goto(c);\n                if (nn) visorder.push_back(nn);\n\
    \            }\n        }\n    }\n\n    int step(int now, int d) {\n        while\
    \ (now and !node[now].Goto(d)) now = node[now].fail;\n        return node[now].Goto(d);\n\
    \    }\n\n    // Count occurences of each added keyword in `str`\n    std::vector<int>\
    \ match(const std::string &str) {\n        std::vector<int> freq(node.size());\n\
    \        int now = 0;\n        for (const auto &c : str) freq[now = step(now,\
    \ char2int(c))]++;\n\n        for (auto i = visorder.rbegin(); i != visorder.rend();\
    \ i++) freq[node[*i].fail] += freq[*i];\n        std::vector<int> ret;\n     \
    \   for (auto x : endpos) ret.push_back(freq[x]);\n        return ret;\n    }\n\
    };\n\nstruct TrieNodeFL {\n    static const int B = 8, mask = (1 << B) - 1;\n\
    \    light_forward_list<unsigned> chlist; // \u4E0B\u4F4D B bits \u304C\u6587\u5B57\
    \u7A2E\uFF0C\u4E0A\u4F4D bit \u304C\u884C\u304D\u5148\n    std::unordered_set<int>\
    \ inv_fail;\n    int fail;\n    TrieNodeFL(int = 0) : fail(0) {}\n    int Goto(int\
    \ c) {\n        for (const auto x : chlist) {\n            if ((x & mask) == c)\
    \ return x >> B;\n        }\n        return 0;\n    }\n    void setch(int c, int\
    \ i) { chlist.push_front(c + (i << B)); }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, TrieNodeFL &x) {\n        os << '[' << x.fail << '/';\n        for (const\
    \ auto c : x.chlist) os << '(' << (c & mask) << ',' << (c >> B) << \"),\";\n \
    \       return os << ']';\n    }\n\n    struct iterator {\n        light_forward_list<unsigned>::iterator\
    \ iter;\n        iterator operator++() { return {++iter}; }\n        std::pair<int,\
    \ int> operator*() {\n            unsigned val = *iter;\n            return std::make_pair(val\
    \ & mask, val >> B); // (char, next_pos)\n        }\n        bool operator!=(const\
    \ iterator &rhs) { return iter != rhs.iter; }\n    };\n    iterator begin() {\
    \ return {chlist.begin()}; }\n    iterator end() { return {chlist.end()}; }\n\
    };\n\nint c2i_0aA(char c) { return isdigit(c) ? c - '0' : islower(c) ? c - 'a'\
    \ + 10 : c - 'A' + 36; }\n#line 121 \"string/test/incremental_matching.test.cpp\"\
    \nusing namespace std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    IncrementalMatching<TrieNodeFL,\
    \ c2i_0aA> trie(62);\n    string T, P;\n    int Q;\n    cin >> T >> Q;\n    while\
    \ (Q--) cin >> P, trie.add(P);\n    dbg(trie.node);\n\n    trie.build_bfs();\n\
    \    auto v = trie.match(T);\n    dbg(v);\n    for (auto n : v) cout << !!n <<\
    \ '\\n';\n}\n"
  code: "#include <bits/stdc++.h>\nusing namespace std;\nusing lint = long long;\n\
    using pint = pair<int, int>;\nusing plint = pair<lint, lint>;\nstruct fast_ios\
    \ {\n    fast_ios() { cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed\
    \ << setprecision(20); };\n} fast_ios_;\n#define ALL(x) (x).begin(), (x).end()\n\
    #define FOR(i, begin, end) for (int i = (begin), i##_end_ = (end); i < i##_end_;\
    \ i++)\n#define IFOR(i, begin, end) for (int i = (end)-1, i##_begin_ = (begin);\
    \ i >= i##_begin_; i--)\n#define REP(i, n) FOR(i, 0, n)\n#define IREP(i, n) IFOR(i,\
    \ 0, n)\ntemplate <typename T, typename V> void ndarray(vector<T> &vec, const\
    \ V &val, int len) { vec.assign(len, val); }\ntemplate <typename T, typename V,\
    \ typename... Args> void ndarray(vector<T> &vec, const V &val, int len, Args...\
    \ args) {\n    vec.resize(len), for_each(begin(vec), end(vec), [&](T &v) { ndarray(v,\
    \ val, args...); });\n}\ntemplate <typename T> bool chmax(T &m, const T q) {\n\
    \    if (m < q) {\n        m = q;\n        return true;\n    } else\n        return\
    \ false;\n}\ntemplate <typename T> bool chmin(T &m, const T q) {\n    if (m >\
    \ q) {\n        m = q;\n        return true;\n    } else\n        return false;\n\
    }\nint floor_lg(long long x) { return x <= 0 ? -1 : 63 - __builtin_clzll(x); }\n\
    template <typename T1, typename T2> pair<T1, T2> operator+(const pair<T1, T2>\
    \ &l, const pair<T1, T2> &r) { return make_pair(l.first + r.first, l.second +\
    \ r.second); }\ntemplate <typename T1, typename T2> pair<T1, T2> operator-(const\
    \ pair<T1, T2> &l, const pair<T1, T2> &r) { return make_pair(l.first - r.first,\
    \ l.second - r.second); }\ntemplate <typename T> vector<T> sort_unique(vector<T>\
    \ vec) {\n    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()),\
    \ vec.end());\n    return vec;\n}\ntemplate <typename T> istream &operator>>(istream\
    \ &is, vector<T> &vec) {\n    for (auto &v : vec) is >> v;\n    return is;\n}\n\
    template <typename T> ostream &operator<<(ostream &os, const vector<T> &vec) {\n\
    \    os << '[';\n    for (auto v : vec) os << v << ',';\n    os << ']';\n    return\
    \ os;\n}\ntemplate <typename T, size_t sz> ostream &operator<<(ostream &os, const\
    \ array<T, sz> &arr) {\n    os << '[';\n    for (auto v : arr) os << v << ',';\n\
    \    os << ']';\n    return os;\n}\n#if __cplusplus >= 201703L\ntemplate <typename...\
    \ T> istream &operator>>(istream &is, tuple<T...> &tpl) {\n    std::apply([&is](auto\
    \ &&... args) { ((is >> args), ...); }, tpl);\n    return is;\n}\ntemplate <typename...\
    \ T> ostream &operator<<(ostream &os, const tuple<T...> &tpl) {\n    std::apply([&os](auto\
    \ &&... args) { ((os << args << ','), ...); }, tpl);\n    return os;\n}\n#endif\n\
    template <typename T> ostream &operator<<(ostream &os, const deque<T> &vec) {\n\
    \    os << \"deq[\";\n    for (auto v : vec) os << v << ',';\n    os << ']';\n\
    \    return os;\n}\ntemplate <typename T> ostream &operator<<(ostream &os, const\
    \ set<T> &vec) {\n    os << '{';\n    for (auto v : vec) os << v << ',';\n   \
    \ os << '}';\n    return os;\n}\ntemplate <typename T, typename TH> ostream &operator<<(ostream\
    \ &os, const unordered_set<T, TH> &vec) {\n    os << '{';\n    for (auto v : vec)\
    \ os << v << ',';\n    os << '}';\n    return os;\n}\ntemplate <typename T> ostream\
    \ &operator<<(ostream &os, const multiset<T> &vec) {\n    os << '{';\n    for\
    \ (auto v : vec) os << v << ',';\n    os << '}';\n    return os;\n}\ntemplate\
    \ <typename T> ostream &operator<<(ostream &os, const unordered_multiset<T> &vec)\
    \ {\n    os << '{';\n    for (auto v : vec) os << v << ',';\n    os << '}';\n\
    \    return os;\n}\ntemplate <typename T1, typename T2> ostream &operator<<(ostream\
    \ &os, const pair<T1, T2> &pa) {\n    os << '(' << pa.first << ',' << pa.second\
    \ << ')';\n    return os;\n}\ntemplate <typename TK, typename TV> ostream &operator<<(ostream\
    \ &os, const map<TK, TV> &mp) {\n    os << '{';\n    for (auto v : mp) os << v.first\
    \ << \"=>\" << v.second << ',';\n    os << '}';\n    return os;\n}\ntemplate <typename\
    \ TK, typename TV, typename TH> ostream &operator<<(ostream &os, const unordered_map<TK,\
    \ TV, TH> &mp) {\n    os << '{';\n    for (auto v : mp) os << v.first << \"=>\"\
    \ << v.second << ',';\n    os << '}';\n    return os;\n}\n#ifdef HITONANODE_LOCAL\n\
    const string COLOR_RESET = \"\\033[0m\", BRIGHT_GREEN = \"\\033[1;32m\", BRIGHT_RED\
    \ = \"\\033[1;31m\", BRIGHT_CYAN = \"\\033[1;36m\", NORMAL_CROSSED = \"\\033[0;9;37m\"\
    , RED_BACKGROUND = \"\\033[1;41m\", NORMAL_FAINT = \"\\033[0;2m\";\n#define dbg(x)\
    \ cerr << BRIGHT_CYAN << #x << COLOR_RESET << \" = \" << (x) << NORMAL_FAINT <<\
    \ \" (L\" << __LINE__ << \") \" << __FILE__ << COLOR_RESET << endl\n#else\n#define\
    \ dbg(x)                                                                     \
    \                                                                            \
    \                                                                            \
    \                                                                            \
    \                                                                            \
    \            \\\n    {}\n#endif\n\n#include \"../incremental_matching.hpp\"\n\
    #include <iostream>\nusing namespace std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    IncrementalMatching<TrieNodeFL,\
    \ c2i_0aA> trie(62);\n    string T, P;\n    int Q;\n    cin >> T >> Q;\n    while\
    \ (Q--) cin >> P, trie.add(P);\n    dbg(trie.node);\n\n    trie.build_bfs();\n\
    \    auto v = trie.match(T);\n    dbg(v);\n    for (auto n : v) cout << !!n <<\
    \ '\\n';\n}\n"
  dependsOn:
  - string/incremental_matching.hpp
  - other_data_structures/light_forward_list.hpp
  isVerificationFile: true
  path: string/test/incremental_matching.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 02:53:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/incremental_matching.test.cpp
layout: document
redirect_from:
- /verify/string/test/incremental_matching.test.cpp
- /verify/string/test/incremental_matching.test.cpp.html
title: string/test/incremental_matching.test.cpp
---
