#pragma once
#include "../other_data_structures/light_forward_list.hpp"
#include <cassert>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// CUT begin
// Aho-Corasick algorithm
// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>
//         <https://yukicoder.me/submissions/598606>
// Complexity:
// - add(): O(|str_i|)
// - build_aho_corasick(): O(\sum_i |str_i|)
// - match() : O(\sum_i |str_i| + |str|)
template <class T, int (*char2int)(char)> struct AhoCorasick {
    const int D;
    std::vector<T> node;
    AhoCorasick(int D_) : D(D_), node(1, D) {}

    std::vector<int> endpos;
    int add(const std::string &str) { // Enter_in_tree() in [1]
        assert(str.length() > 0);
        int now = 0;
        for (const auto &c : str) {
            const int i = char2int(c), nxt = node[now].Goto(i);
            if (nxt) {
                now = nxt;
            } else {
                node[now].enter_child(i, node.size());
                now = node.size(), node.emplace_back(D);
            }
        }
        return endpos.push_back(now), now;
    }

    std::vector<int> visorder;  // BFS order of node ids
    void build_aho_corasick() { // Build_failure() in [1]
        visorder.clear();
        for (int i = 0; i < D; i++) {
            int u = node[0].Goto(i);
            if (u) visorder.push_back(u);
        }
        for (size_t p = 0; p < visorder.size(); p++) {
            int n = visorder[p];
            for (int c = 0; c < D; c++) {
                const int nn = node[n].Goto(c);
                if (!nn) continue;
                visorder.push_back(nn);
                int m = node[n].fail, cc = node[m].Goto(c); // Complete_failure(n, c) in [1]
                while (m and !cc) m = node[m].fail, cc = node[m].Goto(c);
                node[nn].fail = cc;
            }
        }
    }

    int step(int now, int d) {
        while (now and !node[now].Goto(d)) now = node[now].fail;
        return node[now].Goto(d);
    }

    // Count occurences of each added strings in `str`
    std::vector<int> match(const std::string &str) {
        std::vector<int> freq(node.size());
        int now = 0;
        for (const auto &c : str) freq[now = step(now, char2int(c))]++;

        for (auto i = visorder.rbegin(); i != visorder.rend(); i++) freq[node[*i].fail] += freq[*i];
        std::vector<int> ret;
        for (auto x : endpos) ret.push_back(freq[x]);
        return ret;
    }
};

struct TrieNodeFL {
    static const int B = 8, mask = (1 << B) - 1;
    light_forward_list<unsigned> chlist; // 下位 B bits が文字種，上位 bit が行き先
    unsigned fail;
    TrieNodeFL(int = 0) : fail(0) {}
    int Goto(int d) {
        for (const auto x : chlist)
            if ((x & mask) == d) return x >> B;
        return 0;
    }
    void enter_child(int d, unsigned i) { chlist.push_front(d + (i << B)); }
};

struct TrieNodeV {
    std::vector<unsigned> ch; // 全 bit が行き先
    unsigned fail;
    TrieNodeV(int D = 0) : ch(D), fail(0) {}
    int Goto(int d) { return ch[d]; }
    void enter_child(int d, unsigned i) { ch[d] = i; }
};

struct TrieNodeUM {
    std::unordered_map<int, unsigned> mp;
    unsigned fail;
    TrieNodeUM(int = 0) : fail(0) {}
    int Goto(int d) { return mp.count(d) ? mp[d] : 0; }
    void enter_child(int d, unsigned i) { mp[d] = i; }
};

int c2i0aA(char c) { return isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 36; }

/* Usage:
AhoCorasick<TrieNodeFL, c2i0aA> trie(62);
trie.add(P);
trie.build_aho_corasick();
vector<int> ret = trie.match();
*/
