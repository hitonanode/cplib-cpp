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


# :warning: unionfind/undo_unionfind.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05779a67d348d10b6c575a1ac0d9b972">unionfind</a>
* <a href="{{ site.github.repository_url }}/blob/master/unionfind/undo_unionfind.hpp">View this file on GitHub</a>
    - Last commit date: 2019-08-10 13:05:46+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// UnionFind, able to rewind to the previous state by undo()
// Written for Educational Codeforces 62 F, although not verified yet.
#pragma once 
#include <stack>
#include <vector>
#include <numeric>
#include <utility>


struct UndoSizeAwareUnionFind
{
    using pint = std::pair<int, int>;
    std::vector<int> par, cou;
    std::stack<std::pair<int, pint>> history;
    UndoSizeAwareUnionFind(int N) : par(N), cou(N, 1) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) { return (par[x] == x) ? x :find(par[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (cou[x] < cou[y]) std::swap(x, y);
        history.emplace(y, pint(par[y], cou[x]));
        if (x != y) par[y] = x, cou[x] += cou[y];
    }
    void undo()
    {
        cou[par[history.top().first]] = history.top().second.second;
        par[history.top().first] = history.top().second.first;
        history.pop();
    }
    int count(int x) { return cou[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: unionfind/undo_unionfind.hpp: line 3: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

