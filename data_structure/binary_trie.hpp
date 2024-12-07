#pragma once
#include <vector>

template <class Int, class Count = int> struct BinaryTrie {
    int maxD;
    std::vector<Count> deg, subtree_sum;
    std::vector<int> ch0, ch1, par;

    int _new_node(int id_par) {
        deg.emplace_back(Count());
        subtree_sum.emplace_back(Count());
        ch0.emplace_back(-1);
        ch1.emplace_back(-1);
        par.emplace_back(id_par);
        return (int)ch0.size() - 1;
    }

    BinaryTrie(int maxD = 0) : maxD(maxD) { _new_node(-1); }

    // Return index of x.
    // Create nodes to locate x if needed.
    int _get_create_index(Int x) {
        int now = 0;
        for (int d = maxD - 1; d >= 0; --d) {
            int nxt = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (nxt == -1) {
                nxt = _new_node(now);
                (((x >> d) & 1) ? ch1[now] : ch0[now]) = nxt;
            }
            now = nxt;
        }
        return now;
    }

    // Return node index of x.
    // Return -1 if x is not in trie.
    int _get_index(Int x) const {
        int now = 0;
        for (int d = maxD - 1; d >= 0; --d) {
            now = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (now == -1) return -1;
        }
        return now;
    }

    // insert x
    void insert(Int x, Count c = Count(1)) {
        int now = _get_create_index(x);
        deg[now] += c;
        while (now >= 0) subtree_sum[now] += c, now = par[now];
    }

    // delete x if exists
    void erase(Int x) {
        int now = _get_index(x);
        if (now >= 0 and deg[now] != 0) {
            Count r = deg[now];
            deg[now] = 0;
            while (now >= 0) subtree_sum[now] -= r, now = par[now];
        }
    }

    Count count(Int x) const {
        int now = _get_index(x);
        return now == -1 ? Count() : deg[now];
    }

    bool contains(Int x) const { return count(x) > Count(); }

    // min(y ^ x) for y in trie
    Int xor_min(Int x) const {
        Int ret = 0;
        int now = 0;
        if (!subtree_sum[now]) return -1;
        for (int d = maxD - 1; d >= 0; d--) {
            int y = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (y != -1 and subtree_sum[y]) {
                now = y;
            } else {
                ret += Int(1) << d, now = ch0[now] ^ ch1[now] ^ y;
            }
        }
        return ret;
    }

    // Count elements y such that x ^ y < thres
    Count count_less_xor(Int x, Int thres) const {
        Count ret = Count();
        int now = 0;

        for (int d = maxD - 1; d >= 0; d--) {
            if (now == -1) break;

            const bool bit_x = (x >> d) & 1;

            if ((thres >> d) & 1) {
                const int child = bit_x ? ch1[now] : ch0[now];
                if (child != -1) ret += subtree_sum[child];

                now = bit_x ? ch0[now] : ch1[now];
            } else {
                now = bit_x ? ch1[now] : ch0[now];
            }
        }

        return ret;
    }
};
