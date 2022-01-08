#pragma once
#include "../data_structure/light_forward_list.hpp"
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

// CUT begin
// Aho-Corasick algorithm
// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>
//         <https://yukicoder.me/submissions/598606>
// Complexity:
// - add(): O(|keyword_i|)
// - build_aho_corasick(): O(\sum_i |keyword_i|)
// - match() : O(\sum_i |keyword_i| + |str|)
template <class T, int (*char2int)(char)> struct AhoCorasick {
    bool built;
    const int D;
    std::vector<T> node;
    AhoCorasick(int D_) : built(false), D(D_), node(1, D) {}
    AhoCorasick operator=(const AhoCorasick &rhs) { return AhoCorasick(rhs.D); }

    void enter_child(int n, int nn, int c) { node[n].setch(c, nn); }

    std::vector<int> endpos;
    int add(const std::string &keyword) { // Enter_in_tree() in [1]
        built = false;
        int n = 0;
        for (const auto &cc : keyword) {
            int c = char2int(cc), nn = node[n].Goto(c);
            if (!nn) {
                nn = node.size();
                enter_child(n, nn, c), node.emplace_back(D);
            }
            n = nn;
        }
        return endpos.push_back(n), n;
    }

    void complete_failure(int n, int nn, int c) {
        int m = node[n].fail, mm = node[m].Goto(c);
        while (m and !mm) m = node[m].fail, mm = node[m].Goto(c);
        node[nn].fail = mm;
    }

    std::vector<int> visorder; // BFS order of node ids
    void build() {             // Build_failure() in [1]
        visorder.clear();
        for (auto p : node[0]) {
            if (p.second) visorder.push_back(p.second);
        }
        for (size_t p = 0; p < visorder.size(); p++) {
            int n = visorder[p];
            for (auto p : node[n]) {
                int c = p.first, nn = p.second;
                if (nn) visorder.push_back(nn), complete_failure(n, nn, c);
            }
        }
        built = true;
    }

    int step(int now, int d) {
        while (now and !node[now].Goto(d)) now = node[now].fail;
        return node[now].Goto(d);
    }

    // Count occurences of each added keywords in `str`
    std::vector<int> match(const std::string &str) {
        if (!built) build();
        std::vector<int> freq(node.size());
        int now = 0;
        for (const auto &c : str) freq[now = step(now, char2int(c))]++;

        for (auto i = visorder.rbegin(); i != visorder.rend(); i++)
            freq[node[*i].fail] += freq[*i];
        std::vector<int> ret;
        for (auto x : endpos) ret.push_back(freq[x]);
        return ret;
    }
};

struct TrieNodeFL {
    struct smallpii {
        int first : 8;
        int second : 24;
    };
    light_forward_list<smallpii> chlist;
    int fail;
    TrieNodeFL(int = 0) : fail(0) {}
    int Goto(int c) {
        for (const auto x : chlist) {
            if (x.first == c) return x.second;
        }
        return 0;
    }
    void setch(int c, int i) { chlist.push_front({c, i}); }

    struct iterator {
        light_forward_list<smallpii>::iterator iter;
        iterator operator++() { return {++iter}; }
        smallpii operator*() { return *iter; }
        bool operator!=(const iterator &rhs) { return iter != rhs.iter; }
    };
    iterator begin() { return {chlist.begin()}; }
    iterator end() { return {chlist.end()}; }
};

struct TrieNodeV {
    std::vector<int> ch; // 全 bit が行き先
    int fail;
    TrieNodeV(int D = 0) : ch(D), fail(0) {}
    int Goto(int d) { return ch[d]; }
    void setch(int d, int i) { ch[d] = i; }

    struct iterator {
        int i;
        std::vector<int>::iterator iter;
        iterator operator++() { return {++i, ++iter}; }
        std::pair<int, int> operator*() { return std::make_pair(i, *iter); }
        bool operator!=(const iterator &rhs) { return iter != rhs.iter; }
    };
    iterator begin() { return {0, ch.begin()}; }
    iterator end() { return {int(ch.size()), ch.end()}; }
};

struct TrieNodeUM : std::unordered_map<int, int> {
    int fail;
    TrieNodeUM(int = 0) : fail(0) {}
    int Goto(int d) { return count(d) ? (*this)[d] : 0; }
    void setch(int d, int i) { (*this)[d] = i; }
};

int c2i0aA(char c) { return isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 36; }

/* Usage:
AhoCorasick<TrieNodeFL, c2i0aA> trie(62);
trie.add(P);
trie.build();
vector<int> ret = trie.match();
*/
