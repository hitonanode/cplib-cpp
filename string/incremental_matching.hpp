#pragma once
#include "../data_structure/light_forward_list.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

// CUT begin
// [1] B. Meyer, "Incremental String Matching," Information Processing Letters, 21(5), 1985.
//
// (Dynamic version of Aho-Corasick algorithm)
// Overall complexity: O(K * (\sum_i |keyword_i|) * (\max_i |keyword_i|))
template <class T, int (*char2int)(char)> struct IncrementalMatching {
    bool built;
    const int D;
    std::vector<T> node;
    IncrementalMatching(int D_) : built(false), D(D_), node(1, D) {}

    void enter_child(int n, int nn, int c) {
        complete_failure(n, nn, c);
        node[n].setch(c, nn);
        int fnn = node[nn].fail;
        node[fnn].inv_fail.push_back(nn);
        complete_inverse(n, nn, c);
    }

    void complete_inverse(const int y, const int nn, const int c) {
        for (auto it = node[y].inv_fail.begin();; it++) {
            while (it != node[y].inv_fail.end() and node[*it].fail != y) it = node[y].inv_fail.erase(it);
            if (it == node[y].inv_fail.end()) return;
            const int x = *it, xx = node[x].Goto(c);
            if (xx) {
                node[xx].fail = nn, node[nn].inv_fail.push_back(xx);
            } else {
                complete_inverse(x, nn, c);
            }
        }
    }

    std::vector<int> endpos;
    int add(const std::string &keyword) { // Enter_in_tree() in [1]
        built = false;
        int n = 0;
        for (const auto &cc : keyword) {
            int c = char2int(cc), nn = node[n].Goto(c);
            if (!nn) {
                nn = node.size();
                node.emplace_back(D), enter_child(n, nn, c);
            }
            n = nn;
        }
        return endpos.push_back(n), n;
    }

    void complete_failure(int n, int nn, int c) {
        int m = n, Tmc = node[m].Goto(c);
        while (m and !Tmc) m = node[m].fail, Tmc = node[m].Goto(c);
        node[nn].fail = Tmc;
    }

    std::vector<int> visorder; // BFS order of node ids
    void build() {             // Build_failure() in [1]
        built = true;
        visorder = {0};
        for (size_t p = 0; p < visorder.size(); p++) {
            for (auto p : node[visorder[p]]) {
                if (p.second) visorder.push_back(p.second);
            }
        }
    }

    int step(int now, int d) {
        while (now and !node[now].Goto(d)) now = node[now].fail;
        return node[now].Goto(d);
    }

    // Count occurences of each added keyword in `str`
    std::vector<int> match(const std::string &str) {
        if (!built) build();
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
    std::list<int> inv_fail;
    int fail;
    TrieNodeFL(int = 0) : fail(0) {}
    int Goto(int c) {
        for (const auto x : chlist) {
            if ((x & mask) == c) return x >> B;
        }
        return 0;
    }
    void setch(int c, int i) { chlist.push_front(c + (i << B)); }
    friend std::ostream &operator<<(std::ostream &os, TrieNodeFL &x) {
        os << '[' << x.fail << '/';
        for (const auto c : x.chlist) os << '(' << (c & mask) << ',' << (c >> B) << "),";
        return os << ']';
    }

    struct iterator {
        light_forward_list<unsigned>::iterator iter;
        iterator operator++() { return {++iter}; }
        std::pair<int, int> operator*() {
            unsigned val = *iter;
            return std::make_pair(val & mask, val >> B); // (char, next_pos)
        }
        bool operator!=(const iterator &rhs) { return iter != rhs.iter; }
    };
    iterator begin() { return {chlist.begin()}; }
    iterator end() { return {chlist.end()}; }
};

int c2i_0aA(char c) { return isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 36; }
