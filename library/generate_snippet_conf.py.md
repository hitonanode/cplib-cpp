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
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: generate_snippet_conf.py

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/generate_snippet_conf.py">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#!/usr/bin/env python3
# "Config.txt" generator for "Clipboard History", snippet manager
# <https://blank-note.sakura.ne.jp/topics/clipboard_history.html>

import os
import re

rootdir = './'
config_header = [
    '@NoteHotkey=Shift,400'
]

def read_hpp(filepath):
    ret = [os.path.basename(filepath) + '|']
    with open(filepath, 'r') as file:
        for line in file.read().splitlines():
            if line[:12] == '// CUT begin':
                ret = ret[:1]
            else:
                line = re.sub('([|`])', '`\\1', line)
                if len(line) and line[0] in ['+', '*', '.', ';', ' ']:
                    line = '`' + line
                ret.append(line)
    ret.append('/E')
    return ret

def dfs(current_dir):
    ret = list()
    for ch in os.listdir(current_dir):
        filepath = os.path.join(current_dir, ch)
        if os.path.isdir(filepath):
            ch_info = dfs(filepath)
            if ch_info:
                ret += ['+' + ch]
                ret += ch_info
                ret += ['..']
        if os.path.isfile(filepath) and len(filepath) > 4 and filepath[-4:] == '.hpp':
            ret += read_hpp(filepath)
    return ret


if __name__ == '__main__':
    ret = config_header + dfs(rootdir)
    with open('Config.txt', 'w') as f:
        for line in ret:
            f.write(line + '\r\n')

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py", line 84, in bundle
    raise NotImplementedError
NotImplementedError

```
{% endraw %}

<a href="../index.html">Back to top page</a>

