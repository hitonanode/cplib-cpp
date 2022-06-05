---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/product_embedding.test.cpp
    title: utilities/test/product_embedding.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/product_embedding.hpp\"\n#include <cassert>\n\
    #include <fstream>\n#include <vector>\n\n// \u7D50\u5408\u6CD5\u5247\u304C\u6210\
    \u7ACB\u3059\u308B\u8981\u7D20\u306E\u5217\u306B\u3064\u3044\u3066\u9023\u7D9A\
    \u90E8\u5206\u5217\u306E\u7A4D\u3092\u524D\u8A08\u7B97\u3092\u5229\u7528\u3057\
    \u9AD8\u901F\u306B\u6C42\u3081\u308B\ntemplate <class S, S (*op)(S, S), S (*e)(),\
    \ S (*getter)(long long), int Bucket>\nstruct product_embedding {\n    std::vector<S>\
    \ pre_; // pre_[i] = S[i * Bucket] * ... * S[(i + 1) * Bucket - 1]\n\n    product_embedding(std::vector<S>\
    \ pre) : pre_(pre) {}\n\n    S prod(long long l, long long r) { // S[l] * ...\
    \ * S[r - 1]\n        assert(0 <= l);\n        assert(l <= r);\n        assert(r\
    \ <= (long long)Bucket * (long long)pre_.size());\n\n        if (r - l <= Bucket)\
    \ {\n            S ret = e();\n            while (l < r) ret = op(ret, getter(l++));\n\
    \            return ret;\n        }\n\n        long long lb = (l + Bucket - 1)\
    \ / Bucket, rb = r / Bucket;\n        S ret = e();\n        for (long long i =\
    \ l; i < lb * Bucket; ++i) ret = op(ret, getter(i));\n        for (int i = lb;\
    \ i < rb; ++i) ret = op(ret, pre_[i]);\n        for (long long i = rb * Bucket;\
    \ i < r; ++i) ret = op(ret, getter(i));\n        return ret;\n    }\n\n    static\
    \ void prerun(std::string filename, long long upper_lim) {\n        std::ofstream\
    \ ofs(filename);\n\n        long long cur = 0;\n        long long num_bucket =\
    \ (upper_lim + Bucket - 1) / Bucket;\n\n        ofs << \"({\";\n        while\
    \ (num_bucket--) {\n            S p = e();\n            for (int t = 0; t < Bucket;\
    \ ++t) { p = op(p, getter(cur++)); }\n            ofs << p;\n            if (num_bucket)\
    \ ofs << \",\";\n        }\n        ofs << \"});\";\n    }\n};\n/* Usage:\nusing\
    \ S = int;\nconstexpr S md = 1000000007;\nS op(S l, S r) { return (long long)l\
    \ * r % md; }\nS e() { return 1; }\nS getter(long long i) { return i + 1 >= md\
    \ ? (i + 1) % md : i + 1; }\nusing PE = product_embedding<S, op, e, getter, 500000>;\n\
    \nint main() {\n    PE::prerun(\"tmp.txt\", md);  // -> copy & paste the content\
    \ of dumped file\n}\n*/\n"
  code: "#pragma once\n#include <cassert>\n#include <fstream>\n#include <vector>\n\
    \n// \u7D50\u5408\u6CD5\u5247\u304C\u6210\u7ACB\u3059\u308B\u8981\u7D20\u306E\u5217\
    \u306B\u3064\u3044\u3066\u9023\u7D9A\u90E8\u5206\u5217\u306E\u7A4D\u3092\u524D\
    \u8A08\u7B97\u3092\u5229\u7528\u3057\u9AD8\u901F\u306B\u6C42\u3081\u308B\ntemplate\
    \ <class S, S (*op)(S, S), S (*e)(), S (*getter)(long long), int Bucket>\nstruct\
    \ product_embedding {\n    std::vector<S> pre_; // pre_[i] = S[i * Bucket] * ...\
    \ * S[(i + 1) * Bucket - 1]\n\n    product_embedding(std::vector<S> pre) : pre_(pre)\
    \ {}\n\n    S prod(long long l, long long r) { // S[l] * ... * S[r - 1]\n    \
    \    assert(0 <= l);\n        assert(l <= r);\n        assert(r <= (long long)Bucket\
    \ * (long long)pre_.size());\n\n        if (r - l <= Bucket) {\n            S\
    \ ret = e();\n            while (l < r) ret = op(ret, getter(l++));\n        \
    \    return ret;\n        }\n\n        long long lb = (l + Bucket - 1) / Bucket,\
    \ rb = r / Bucket;\n        S ret = e();\n        for (long long i = l; i < lb\
    \ * Bucket; ++i) ret = op(ret, getter(i));\n        for (int i = lb; i < rb; ++i)\
    \ ret = op(ret, pre_[i]);\n        for (long long i = rb * Bucket; i < r; ++i)\
    \ ret = op(ret, getter(i));\n        return ret;\n    }\n\n    static void prerun(std::string\
    \ filename, long long upper_lim) {\n        std::ofstream ofs(filename);\n\n \
    \       long long cur = 0;\n        long long num_bucket = (upper_lim + Bucket\
    \ - 1) / Bucket;\n\n        ofs << \"({\";\n        while (num_bucket--) {\n \
    \           S p = e();\n            for (int t = 0; t < Bucket; ++t) { p = op(p,\
    \ getter(cur++)); }\n            ofs << p;\n            if (num_bucket) ofs <<\
    \ \",\";\n        }\n        ofs << \"});\";\n    }\n};\n/* Usage:\nusing S =\
    \ int;\nconstexpr S md = 1000000007;\nS op(S l, S r) { return (long long)l * r\
    \ % md; }\nS e() { return 1; }\nS getter(long long i) { return i + 1 >= md ? (i\
    \ + 1) % md : i + 1; }\nusing PE = product_embedding<S, op, e, getter, 500000>;\n\
    \nint main() {\n    PE::prerun(\"tmp.txt\", md);  // -> copy & paste the content\
    \ of dumped file\n}\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/product_embedding.hpp
  requiredBy: []
  timestamp: '2022-06-05 22:26:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/product_embedding.test.cpp
documentation_of: utilities/product_embedding.hpp
layout: document
title: "Static range product query with precalculation \uFF08\u524D\u8A08\u7B97\u57CB\
  \u3081\u8FBC\u307F\uFF09"
---

$\bmod$ 階乗などの計算を前計算して埋め込み， ${}_n \mathrm{P}_r$ などのクエリに高速で結果を返す．

## できること

（結合法則を満たす）乗法が定義された要素の列 $f(0), f(1), \dots$ を考える．$f(i)$ たちの値は陽には持たないが，$i$ の値を与えると $f(i)$ は十分高速に求められるものとする．バケットサイズとして正の整数 $B$ を定める．$F(k) = f(Bk) f(Bk + 1) \cdots f((B + 1)k - 1)$ の値を各 $k$ について前計算しておけば，任意のクエリ $(l, r)$ について $f(l) f(l + 1) \cdots f(r - 1)$ の値が $O(B + (r - l) / B)$ で求まる．

本コードは前計算した $F(k)$ の値の一覧をテキストファイルに出力する機能，およびこの前計算された結果を元に $f(l) \cdots f(r - 1)$ の値を計算するメソッドを提供する．

## 使用方法

「問題例」に挙げた階乗クエリを高速に処理したいケースで述べる．

まず前計算として，以下のようなコードを書いてコンパイルし実行する．

```cpp
using S = int;
constexpr S md = 1000000007;
S op(S l, S r) { return (long long)l * r % md; }
S e() { return 1; }
S getter(long long i) { return i + 1 >= md ? (i + 1) % md : i + 1; }  // f(i) = i + 1
using PE = product_embedding<S, op, e, getter, 500000>;

int main() {
    PE::prerun("tmp.txt", len);  // 0 <= l <= r <= len までのクエリ (l, r) の実行を保証する．
}
```

すると，`tmp.txt` というテキストファイルが生成されるので，その中身を用いて改めて `PE` クラスのインスタンスを生成し，これを用いて問題を解く．

```cpp
int main() {
    PE pe({154425679,765215884,239137314, ..., 899058414,0}); // 「PE pe」以降は tmp.txt のコピペで OK

    int ret = pe.prod(l, r);  // f(l) * ... * f(r - 1) = (l + 1) * ... * r の計算結果
}
```

## 問題例

- [No.502 階乗を計算するだけ - yukicoder](https://yukicoder.me/problems/no/502)
- [SRM 830 Div.1 1000 RedAndBlueShades](https://community.topcoder.com/stat?c=problem_statement&pm=17600) : 階乗のほか，$f(i) = 2i + 1$ 型の列に関する range product も使用される（考察により省くことも可能）．
