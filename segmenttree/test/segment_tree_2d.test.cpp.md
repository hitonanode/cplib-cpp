---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/segment_tree_2d.hpp
    title: segmenttree/segment_tree_2d.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068
  bundledCode: "#line 2 \"segmenttree/segment_tree_2d.hpp\"\n#include <iostream>\n\
    #include <vector>\n\n// CUT begin\n// 2D Segment Tree (point-update, range-get)\n\
    // - 0-indexed\n// - Conditions for operations:\n//   - merge_data: [TDATA, TDATA]\
    \ -> TDATA, e(defaultDATA, x) == x, e(x, y) == e(y, x)\n//   - data2ret: [TDATA,\
    \ TQUERY] -> TRET, f(defaultDATA, q) == defaultRET\n//   - merge_ret: [TRET, TRET]\
    \ -> TRET, g(defaultRET, x) == x, g(x, y) = g(y, x)\n//   - commutability f(e(x,\
    \ y), q) == g(f(x, q), f(y, q))\ntemplate <typename TDATA, typename TRET, typename\
    \ TQUERY, typename E, typename F, typename G>\nstruct SegmentTree2D {\n    int\
    \ H, W;\n    int hhead, whead;\n    TDATA defaultDATA;\n    TRET defaultRET;\n\
    \    E merge_data;\n    F data2ret;\n    G merge_ret;\n    int DH, DW;\n    std::vector<TDATA>\
    \ data;\n    inline TDATA &at(int h, int w) { return data[DW * h + w]; }\n\n \
    \   inline void _merge_w(int h, int w) {\n        if (2 * w + 2 < DW)\n      \
    \      at(h, w) = merge_data(at(h, 2 * w + 1), at(h, 2 * w + 2));\n        else\
    \ if (2 * w + 2 == DW)\n            at(h, w) = at(h, 2 * w + 1);\n        else\n\
    \            at(h, w) = defaultDATA;\n    }\n    inline void _merge_h(int h, int\
    \ w) {\n        if (2 * h + 2 < DH)\n            at(h, w) = merge_data(at(2 *\
    \ h + 1, w), at(2 * h + 2, w));\n        else if (2 * h + 2 == DH)\n         \
    \   at(h, w) = at(2 * h + 1, w);\n        else\n            at(h, w) = defaultDATA;\n\
    \    }\n    SegmentTree2D(const std::vector<std::vector<TDATA>> &mat, TDATA defaultDATA,\
    \ E merge_data,\n                  F data2ret, G merge_ret)\n        : H(mat.size()),\
    \ W(mat[0].size()), defaultDATA(defaultDATA),\n          defaultRET(data2ret(defaultDATA,\
    \ TQUERY(0))), merge_data(merge_data), data2ret(data2ret),\n          merge_ret(merge_ret)\
    \ {\n        int Htmp = 1, Wtmp = 1;\n        while (Htmp < H) Htmp <<= 1;\n \
    \       while (Wtmp < W) Wtmp <<= 1;\n        hhead = Htmp - 1, whead = Wtmp -\
    \ 1;\n        DH = hhead + H, DW = whead + W;\n        data.assign(DH * DW, defaultDATA);\n\
    \        for (int h = 0; h < H; h++)\n            for (int w = 0; w < W; w++)\
    \ { at(hhead + h, whead + w) = mat[h][w]; }\n        for (int h = DH - 1; h >=\
    \ hhead; h--) {\n            for (int w = whead - 1; w >= 0; w--) _merge_w(h,\
    \ w);\n        }\n        for (int h = hhead - 1; h >= 0; h--) {\n           \
    \ for (int w = 0; w < DW; w++) _merge_h(h, w);\n        }\n    }\n    void update(int\
    \ h, int w, TDATA x) {\n        h += hhead, w += whead;\n        at(h, w) = x;\n\
    \        for (int pos = h; pos;) {\n            pos = (pos - 1) / 2;\n       \
    \     _merge_h(pos, w);\n        }\n        for (int iw = w; iw;) {\n        \
    \    iw = (iw - 1) / 2;\n            for (int ih = h;;) {\n                _merge_w(ih,\
    \ iw);\n                if (!ih) break;\n                ih = (ih - 1) / 2;\n\
    \            }\n        }\n    }\n    TRET _get_h(int hl, int hr, int wl, int\
    \ wr, int lo, int hi, int id_, TQUERY q) {\n        if (hr <= lo or hi <= hl)\
    \ return defaultRET;\n        if (hl <= lo and hi <= hr) return _get_w(wl, wr,\
    \ 0, whead + 1, id_, 0, q);\n        return merge_ret(_get_h(hl, hr, wl, wr, lo,\
    \ (lo + hi) / 2, 2 * id_ + 1, q),\n                         _get_h(hl, hr, wl,\
    \ wr, (lo + hi) / 2, hi, 2 * id_ + 2, q));\n    }\n    TRET _get_w(int wl, int\
    \ wr, int lo, int hi, int id_h, int id_w, TQUERY q) {\n        if (wr <= lo or\
    \ hi <= wl) return defaultRET;\n        if (wl <= lo and hi <= wr) return data2ret(at(id_h,\
    \ id_w), q);\n        return merge_ret(_get_w(wl, wr, lo, (lo + hi) / 2, id_h,\
    \ 2 * id_w + 1, q),\n                         _get_w(wl, wr, (lo + hi) / 2, hi,\
    \ id_h, 2 * id_w + 2, q));\n    }\n    // [hl, hr) * [wl, wr)\n    TRET get(int\
    \ hl, int hr, int wl, int wr, TQUERY q) {\n        return _get_h(hl, hr, wl, wr,\
    \ 0, hhead + 1, 0, q);\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, SegmentTree2D s) {\n        os << \"[SegmentTree\" << s.H << \"*\" << s.W\
    \ << \"\\n\";\n        for (int h = 0; h < s.H; h++) {\n            os << \"[\"\
    ;\n            for (int w = 0; w < s.W; w++) os << s.at(h + s.hhead, w + s.whead)\
    \ << \",\";\n            os << \"]\\n\";\n        }\n        return os << \"]\"\
    ;\n    }\n};\n#line 2 \"segmenttree/test/segment_tree_2d.test.cpp\"\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068\"\n\n#line 5\
    \ \"segmenttree/test/segment_tree_2d.test.cpp\"\nusing namespace std;\n\nint main()\
    \ {\n    auto f = [](int l, int r) { return min(l, r); };\n    auto g = [](int\
    \ x, int q) { return x; };\n    while (true) {\n        int H, W, Q;\n       \
    \ cin >> H >> W >> Q;\n        vector<vector<int>> mat(H, vector<int>(W));\n \
    \       if (!H) break;\n        for (auto &vec : mat)\n            for (auto &x\
    \ : vec) cin >> x;\n        int INF = (1LL << 31) - 1;\n        SegmentTree2D<int,\
    \ int, int, decltype(f), decltype(g), decltype(f)> rmq(mat, INF, f, g, f);\n \
    \       while (Q--) {\n            int xl, yl, xr, yr;\n            cin >> xl\
    \ >> yl >> xr >> yr;\n            printf(\"%d\\n\", rmq.get(xl, xr + 1, yl, yr\
    \ + 1, -1));\n        }\n    }\n}\n"
  code: "#include \"../segment_tree_2d.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    auto f = [](int\
    \ l, int r) { return min(l, r); };\n    auto g = [](int x, int q) { return x;\
    \ };\n    while (true) {\n        int H, W, Q;\n        cin >> H >> W >> Q;\n\
    \        vector<vector<int>> mat(H, vector<int>(W));\n        if (!H) break;\n\
    \        for (auto &vec : mat)\n            for (auto &x : vec) cin >> x;\n  \
    \      int INF = (1LL << 31) - 1;\n        SegmentTree2D<int, int, int, decltype(f),\
    \ decltype(g), decltype(f)> rmq(mat, INF, f, g, f);\n        while (Q--) {\n \
    \           int xl, yl, xr, yr;\n            cin >> xl >> yl >> xr >> yr;\n  \
    \          printf(\"%d\\n\", rmq.get(xl, xr + 1, yl, yr + 1, -1));\n        }\n\
    \    }\n}\n"
  dependsOn:
  - segmenttree/segment_tree_2d.hpp
  isVerificationFile: true
  path: segmenttree/test/segment_tree_2d.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/segment_tree_2d.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/segment_tree_2d.test.cpp
- /verify/segmenttree/test/segment_tree_2d.test.cpp.html
title: segmenttree/test/segment_tree_2d.test.cpp
---
