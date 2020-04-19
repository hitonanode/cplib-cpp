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
