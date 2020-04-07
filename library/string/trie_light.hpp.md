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


# :warning: string/trie_light.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/trie_light.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-07 23:45:19+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <string>
#include <vector>

// CUT begin
struct Trie
{
    char a_init;
    int D;
    int INVALID = -1;
    std::vector<std::vector<int>> child;
    using T_NODE = int;
    std::vector<T_NODE> v_info;
    Trie(char a_init = 'a', int D = 26) : a_init(a_init), D(D), child(1, std::vector<int>(D, INVALID)), v_info(1) {}
    void add_word(const std::string &str, T_NODE info) {
        int now = 0;
        for (auto &c : str) {
            if (child[now][c - a_init] == INVALID) {
                child[now][c - a_init] = child.size();
                child.emplace_back(std::vector<int>(D, INVALID));
                v_info.resize(child.size());
            }
            now = child[now][c - a_init];
        }
        v_info[now] += info;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/trie_light.hpp"
#include <string>
#include <vector>

// CUT begin
struct Trie
{
    char a_init;
    int D;
    int INVALID = -1;
    std::vector<std::vector<int>> child;
    using T_NODE = int;
    std::vector<T_NODE> v_info;
    Trie(char a_init = 'a', int D = 26) : a_init(a_init), D(D), child(1, std::vector<int>(D, INVALID)), v_info(1) {}
    void add_word(const std::string &str, T_NODE info) {
        int now = 0;
        for (auto &c : str) {
            if (child[now][c - a_init] == INVALID) {
                child[now][c - a_init] = child.size();
                child.emplace_back(std::vector<int>(D, INVALID));
                v_info.resize(child.size());
            }
            now = child[now][c - a_init];
        }
        v_info[now] += info;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

