---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: matroid/vector_matroid.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2a6c9c56c5dd30cd2db2c415985dabce">matroid</a>
* <a href="{{ site.github.repository_url }}/blob/master/matroid/vector_matroid.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 11:29:17+09:00




## Depends on

* :warning: <a href="matroid.hpp.html">matroid/matroid.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "matroid/matroid.hpp"
#pragma once
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;


// Vector matroid on F2 : linearly independent vectors
// VDIM: max. dimension of vector space
// Verified: SRM526.5 1000 (Used only for linear independence check)
template <int VDIM>
struct F2VectorMatroid
{
    int M; // # of vectors
    vector<bitset<VDIM>> mat;
    mutable vector<unordered_map<State, vector<Element>>> cache;
    F2VectorMatroid() = default;
    F2VectorMatroid(const vector<bitset<VDIM>> &bitmat) : M(bitmat.size()), mat(bitmat), cache(bitmat.size()) {}

    // If I is independent and I + {e} is not, return elements of the circuit.
    // If e \in I, or I + {e} is independent, return empty vector.
    // If I is NOT independent, undefined.
    vector<Element> circuit(const State &I, const Element &e) const
    {
        assert(int(I.size()) == M and e < M);
        if (I[e]) return {};
        if (cache[e].count(I)) return cache[e][I];
        vector<bitset<VDIM + 1>> A(VDIM);
        vector<int> eid;
        for (int i = 0; i < M; i++) {
            if (!I[i]) continue;
            for (int j = 0; j < VDIM; j++) A[j][eid.size()] = mat[i][j];
            eid.push_back(i);
            if (eid.size() > VDIM) return {};
        }
        int n = eid.size();
        for (int j = 0; j < VDIM; j++) A[j][n] = mat[e][j];
        for (int c = 0; c < n; c++) {
            int piv = -1;
            for (int r = c; r < VDIM; r++) {
                if (A[r][c]) {
                    piv = r;
                    break;
                }
            }
            if (piv == -1) return cache[e][I] = {};
            swap(A[piv], A[c]);
            for (int r = 0; r < VDIM; r++) {
                if (r != c and A[r][c]) A[r] ^= A[c];
            }
        }
        for (int r = n; r < VDIM; r++) if (A[r][n]) return cache[e][I] = {};
        vector<Element> ret;
        for (size_t i = 0; i < eid.size(); i++) {
            if (A[i][n]) ret.push_back(eid[i]);
        }
        return cache[e][I] = ret;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 181, in main
    subcommand_run(paths=[], jobs=parsed.jobs)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 59, in subcommand_run
    onlinejudge_verify.verify.main(paths, marker=marker, timeout=timeout, jobs=jobs)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 116, in main
    verified = verify_file(path, compilers=compilers, jobs=jobs)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 77, in verify_file
    language.compile(path, basedir=pathlib.Path.cwd(), tempdir=directory)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 48, in compile
    subprocess.check_call(command)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/subprocess.py", line 364, in check_call
    raise CalledProcessError(retcode, cmd)
subprocess.CalledProcessError: Command '['g++', '--std=c++17', '-O2', '-Wall', '-g', '-I', '/home/runner/work/cplib-cpp/cplib-cpp', '-o', '.verify-helper/cache/ca259f8e9cebda54d88036dfaeafd417/a.out', '/home/runner/work/cplib-cpp/cplib-cpp/segmenttree/test/countandsumlessthan.test.cpp']' returned non-zero exit status 1.

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 63, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 115, in update
    raise BundleError(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: matroid/vector_matroid.hpp: line 2: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

