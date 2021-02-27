#!/usr/bin/env python3
# Generate configuration files for snippet managers
#
# "ClipBoardHistoryConfig.txt" for "Clipboard History" (Windows)
# https://blank-note.sakura.ne.jp/topics/clipboard_history.html
#
# "SnippetConfig.json" for "snippet-from-file" (VS Code)
# https://marketplace.visualstudio.com/items?itemName=morioprog.snippet-from-file

import json
import os
import re

rootdir = './'
config_header = [
    '@NoteHotkey=Shift,400'
]


def read_hpp(filepath):
    print(filepath)
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
    json_ret = dict()
    for ch in os.listdir(current_dir):
        filepath = os.path.join(current_dir, ch)
        if os.path.isdir(filepath) and filepath[2] != '.':
            ch_info, json_info = dfs(filepath)
            json_ret.update(json_info)
            if ch_info:
                ret += ['+' + ch]
                ret += ch_info
                ret += ['..']
        if os.path.isfile(filepath) and len(filepath) > 4 and (filepath[-4:] == '.hpp' or filepath[-2:] == '.h'):
            ret += read_hpp(filepath)
            json_ret[filepath[2:-4]] = filepath
    return ret, json_ret


if __name__ == '__main__':
    ret, json_ret = dfs(rootdir)
    ret = config_header + ret

    with open('ClipBoardHistoryConfig.txt', 'w') as f:
        for line in ret:
            f.write(line + '\r\n')

    with open('SnippetConfig.json', 'w') as f:
        json.dump(json_ret, f, ensure_ascii=False, sort_keys=True, indent=4)
