#pragma once
#include "../other_data_structures/light_forward_list.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// CUT begin
// [1] B. Meyer, "Incremental String Matching," Information Processing Letters, 21(5), 1985.
//
// (Dynamic version of Aho-Corasick algorithm)
// Complexity:
// - add(): O(|keyword_i|)
// - match() : O(\sum_i |keyword_i| + |str|)
template <class T, int (*char2int)(char)> struct IncrementalMatching {
    const int D;
    std::vector<T> node;
    IncrementalMatching(int D_) : D(D_), node(1, D) {}

    void enter_child(int n, int nn, int c) {
        complete_failure(n, nn, c);
        node[n].setch(c, nn);
        int fnn = node[nn].fail;
        node[fnn].inv_fail.insert(nn);
        complete_inverse(n, nn, c);
    }

    void complete_inverse(const int y, const int nn, const int c) {
        for (auto x : node[y].inv_fail) {
            const int xx = node[x].Goto(c);
            if (xx) {
                const int fxx = node[xx].fail;
                node[fxx].inv_fail.erase(xx);
                node[xx].fail = nn, node[nn].inv_fail.insert(xx);
            } else {
                complete_inverse(x, nn, c);
            }
        }
    }

    std::vector<int> endpos;
    int add(const std::string &keyword) { // Enter_in_tree() in [1]
        assert(keyword.length() > 0);
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
    void build_bfs() {         // Build_failure() in [1]
        visorder.clear();
        for (int c = 0; c < D; c++) {
            int u = node[0].Goto(c);
            if (u) visorder.push_back(u);
        }
        for (size_t p = 0; p < visorder.size(); p++) {
            int n = visorder[p];
            for (int c = 0; c < D; c++) {
                const int nn = node[n].Goto(c);
                if (nn) visorder.push_back(nn);
            }
        }
    }

    int step(int now, int d) {
        while (now and !node[now].Goto(d)) now = node[now].fail;
        return node[now].Goto(d);
    }

    // Count occurences of each added keyword in `str`
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
    std::unordered_set<int> inv_fail;
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
