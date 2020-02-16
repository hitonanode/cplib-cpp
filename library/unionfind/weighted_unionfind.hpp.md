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


# :heavy_check_mark: unionfind/weighted_unionfind.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05779a67d348d10b6c575a1ac0d9b972">unionfind</a>
* <a href="{{ site.github.repository_url }}/blob/master/unionfind/weighted_unionfind.hpp">View this file on GitHub</a>
    - Last commit date: 2019-08-10 13:05:46+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/unionfind/test/weighted_unionfind.test.cpp.html">unionfind/test/weighted_unionfind.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// Weighted UnionFind
#pragma once
#include <numeric>
#include <utility>
#include <vector>


template<typename T>
struct WeightedUnionFind
{
    std::vector<int> par, sz;
    std::vector<T> pot;
    WeightedUnionFind(int N = 0) : par(N), sz(N, 1), pot(N) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x] != x) {
            int r = find(par[x]);
            pot[x] = pot[x] + pot[par[x]], par[x] = r;
        }
        return par[x];
    }
    bool unite(int s, int t, T rel_diff) {
        // Relate s and t by t = s + rel_diff
        // Return false iff contradiction happens.
        rel_diff = rel_diff + weight(s) + (-weight(t));
        if ((s = find(s)) == (t = find(t))) return rel_diff == 0;
        if (sz[s] < sz[t]) std::swap(s, t), rel_diff = -rel_diff; 
        par[t] = s, sz[s] += sz[t], pot[t] = rel_diff;
        return true;
    }
    T weight(int x) { find(x); return pot[x]; }
    T diff(int s, int t) { return weight(t) + (-weight(s)); }
    int count(int x) { return sz[find(x)]; }
    bool same(int s, int t) { return find(s) == find(t); }
};

// sample data structure T for WeightedUnionFind<T>
/*
struct Monoid {
    int data;
    Monoid() : data(0) {}
    Monoid(int d) : data(d) {}
    Monoid operator+(const Monoid &x) const { return Monoid(this->data + x.data); }
    Monoid operator-() const { return Monoid(-data); }
    bool operator==(const Monoid &x) const { return data == x.data; }
};
WeightedUnionFind<Monoid> wuf(10000);
*/

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
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 70, in verify_file
    exec_command(command)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 28, in exec_command
    subprocess.check_call(command)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/subprocess.py", line 364, in check_call
    raise CalledProcessError(retcode, cmd)
subprocess.CalledProcessError: Command '['oj', 'download', '--system', '-d', '.verify-helper/cache/ca259f8e9cebda54d88036dfaeafd417/test', 'https://yukicoder.me/problems/no/877']' returned non-zero exit status 1.

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 63, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 115, in update
    raise BundleError(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: unionfind/weighted_unionfind.hpp: line 2: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

