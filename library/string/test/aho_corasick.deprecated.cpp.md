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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: string/test/aho_corasick.deprecated.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a7427d145086499c399a0f95224a581">string/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/test/aho_corasick.deprecated.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D</a>


## Depends on

* :warning: <a href="../aho_corasick.hpp.html">string/aho_corasick.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bitset>
#include <iostream>
#include "string/aho_corasick.hpp"
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

void operator+=(bitset<10000> &l, const bitset<10000> &r) { l |= r; }

int main()
{
    Trie<bitset<10000>> trie;
    string T;
    cin >> T;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string P;
        cin >> P;
        bitset<10000> bs;
        bs.set(i);
        trie.add_keyword(P, bs);
    }
    trie.build_aho_corasick();

    int now = 0;
    bitset<10000> ans;
    for (auto c : T)
    {
        while (now and trie.child[now][c] == 0) now = trie.fail[now];
        now = trie.child[now][c];
        ans |= trie.node_info[now];
    }
    for (int i = 0; i < N; i++) cout << ans[i] << endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/test/aho_corasick.deprecated.cpp"
#include <bitset>
#include <iostream>
#line 2 "string/aho_corasick.hpp"
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// CUT begin
template<typename T>
struct Trie
{
    vector<map<char, int>> child;
    vector<int> fail;
    vector<T> node_info;
    int root;
    Trie() : child(1), fail(1), node_info(1), root(0) {}
    void add_keyword(string str, T info)
    {
        int now = 0;
        for (auto c : str)
        {
            if (child[now].count(c) == 0)
            {
                child[now][c] = fail.size();
                child.emplace_back(map<char, int>());
                fail.emplace_back(root);
                node_info.emplace_back(0);
            }
            now = child[now][c];
        }
        node_info[now] += info;
    }

    void build_aho_corasick()
    {
        queue<int> q;
        for (auto pa : child[root]) q.push(pa.second);
        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            for (auto pa : child[s])
            {
                int t = fail[s];
                while (t and child[t].count(pa.first) == 0) t = fail[t];
                int u = (child[t].count(pa.first) ? child[t][pa.first] : root);
                fail[pa.second] = u;
                node_info[pa.second] += node_info[u];
                q.push(pa.second);
            }
        }
    }
};
#line 4 "string/test/aho_corasick.deprecated.cpp"
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

void operator+=(bitset<10000> &l, const bitset<10000> &r) { l |= r; }

int main()
{
    Trie<bitset<10000>> trie;
    string T;
    cin >> T;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string P;
        cin >> P;
        bitset<10000> bs;
        bs.set(i);
        trie.add_keyword(P, bs);
    }
    trie.build_aho_corasick();

    int now = 0;
    bitset<10000> ans;
    for (auto c : T)
    {
        while (now and trie.child[now][c] == 0) now = trie.fail[now];
        now = trie.child[now][c];
        ans |= trie.node_info[now];
    }
    for (int i = 0; i < N; i++) cout << ans[i] << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

