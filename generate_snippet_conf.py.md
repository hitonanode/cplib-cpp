---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://blank-note.sakura.ne.jp/topics/clipboard_history.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/env python3\n# \"Config.txt\" generator for \"Clipboard History\"\
    , snippet manager\n# https://blank-note.sakura.ne.jp/topics/clipboard_history.html\n\
    \nimport os\nimport re\n\nrootdir = './'\nconfig_header = [\n    '@NoteHotkey=Shift,400'\n\
    ]\n\n\ndef read_hpp(filepath):\n    ret = [os.path.basename(filepath) + '|']\n\
    \    with open(filepath, 'r') as file:\n        for line in file.read().splitlines():\n\
    \            if line[:12] == '// CUT begin':\n                ret = ret[:1]\n\
    \            else:\n                line = re.sub('([|`])', '`\\\\1', line)\n\
    \                if len(line) and line[0] in ['+', '*', '.', ';', ' ']:\n    \
    \                line = '`' + line\n                ret.append(line)\n    ret.append('/E')\n\
    \    return ret\n\n\ndef dfs(current_dir):\n    ret = list()\n    for ch in os.listdir(current_dir):\n\
    \        filepath = os.path.join(current_dir, ch)\n        if os.path.isdir(filepath)\
    \ and filepath[2] != '.':\n            ch_info = dfs(filepath)\n            if\
    \ ch_info:\n                ret += ['+' + ch]\n                ret += ch_info\n\
    \                ret += ['..']\n        if os.path.isfile(filepath) and len(filepath)\
    \ > 4 and filepath[-4:] == '.hpp':\n            ret += read_hpp(filepath)\n  \
    \  return ret\n\n\nif __name__ == '__main__':\n    ret = config_header + dfs(rootdir)\n\
    \    with open('ClipBoardHistoryConfig.txt', 'w') as f:\n        for line in ret:\n\
    \            f.write(line + '\\r\\n')\n"
  dependsOn: []
  isVerificationFile: false
  path: generate_snippet_conf.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: generate_snippet_conf.py
layout: document
redirect_from:
- /library/generate_snippet_conf.py
- /library/generate_snippet_conf.py.html
title: generate_snippet_conf.py
---
