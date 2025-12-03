#pragma once
#include "../segmenttree/range-add-range-min.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

// Permutation tree
// Complexity: O(N log N)
// https://codeforces.com/blog/entry/78898 https://judge.yosupo.jp/problem/common_interval_decomposition_tree
struct permutation_tree {
    enum NodeType {
        JoinAsc,
        JoinDesc,
        Cut,
        Leaf,
        None,
    };
    struct Node {
        NodeType tp;
        int L, R;       // i in [L, R)
        int mini, maxi; // A[i] in [mini, maxi]
        int par_id = -1;
        std::vector<int> child;
        int sz() const { return R - L; }
        template <class OStream> friend OStream &operator<<(OStream &os, const Node &n) {
            os << "[[" << n.L << ',' << n.R << ")(ch:";
            for (auto i : n.child) os << i << ',';
            return os << ")(tp=" << n.tp << ")]";
        }
    };

    int root;
    std::vector<int> A;
    std::vector<Node> nodes;

    void _add_child(int par_id, int chid) {
        nodes[par_id].child.push_back(chid);
        nodes[par_id].L = std::min(nodes[par_id].L, nodes[chid].L);
        nodes[par_id].R = std::max(nodes[par_id].R, nodes[chid].R);
        nodes[par_id].mini = std::min(nodes[par_id].mini, nodes[chid].mini);
        nodes[par_id].maxi = std::max(nodes[par_id].maxi, nodes[chid].maxi);
    }

    permutation_tree() : root(-1) {}
    permutation_tree(const std::vector<int> &A_) : root(-1), A(A_) { // A: nonempty perm., 0-origin
        assert(!A.empty());
        RangeAddRangeMin<int> seg((std::vector<int>(A.size())));

        std::vector<int> hi{-1}, lo{-1};
        std::vector<int> st;
        for (int i = 0; i < int(A.size()); ++i) {
            while (hi.back() >= 0 and A[i] > A[hi.back()]) {
                seg.add(hi[hi.size() - 2] + 1, hi.back() + 1, A[i] - A[hi.back()]);
                hi.pop_back();
            }
            hi.push_back(i);
            while (lo.back() >= 0 and A[i] < A[lo.back()]) {
                seg.add(lo[lo.size() - 2] + 1, lo.back() + 1, A[lo.back()] - A[i]);
                lo.pop_back();
            }
            lo.push_back(i);

            int h = nodes.size();
            nodes.push_back({NodeType::Leaf, i, i + 1, A[i], A[i], -1, std::vector<int>{}});

            while (true) {
                NodeType join_tp = NodeType::None;
                if (!st.empty() and nodes[st.back()].maxi + 1 == nodes[h].mini) join_tp = JoinAsc;
                if (!st.empty() and nodes[h].maxi + 1 == nodes[st.back()].mini) join_tp = JoinDesc;

                if (!st.empty() and join_tp != NodeType::None) {
                    const Node &vtp = nodes[st.back()];
                    // Insert v as the child of the top node in the stack
                    if (join_tp == vtp.tp) {
                        // Append child to existing Join node
                        _add_child(st.back(), h);
                        h = st.back();
                        st.pop_back();
                    } else {
                        // Make new join node (with exactly two children)
                        int j = st.back();
                        nodes.push_back(
                            {join_tp, nodes[j].L, nodes[j].R, nodes[j].mini, nodes[j].maxi, -1, {j}});
                        st.pop_back();
                        _add_child(nodes.size() - 1, h);
                        h = nodes.size() - 1;
                    }
                } else if (seg.prod(0, i + 1 - nodes[h].sz()) == 0) {
                    // Make Cut node
                    int L = nodes[h].L, R = nodes[h].R, maxi = nodes[h].maxi, mini = nodes[h].mini;
                    nodes.push_back({NodeType::Cut, L, R, mini, maxi, -1, {h}});
                    h = nodes.size() - 1;
                    do {
                        _add_child(h, st.back());
                        st.pop_back();
                    } while (nodes[h].maxi - nodes[h].mini + 1 != nodes[h].sz());
                    std::reverse(nodes[h].child.begin(), nodes[h].child.end());
                } else {
                    break;
                }
            }
            st.push_back(h);
            seg.add(0, i + 1, -1);
        }
        assert(st.size() == 1);

        for (int i = 0; i < int(nodes.size()); i++) {
            for (auto ch : nodes[i].child) nodes[ch].par_id = i;
        }

        root = st[0];
    }

    void to_DOT(std::string filename = "") const {
        if (filename.empty()) filename = "permutation_tree_v=" + std::to_string(A.size()) + ".DOT";

        std::ofstream ss(filename);
        ss << "digraph{\n";
        int nleaf = 0;
        for (int i = 0; i < int(nodes.size()); i++) {
            ss << i << "[\n";
            std::string lbl;
            if (nodes[i].tp == NodeType::Leaf) {
                lbl = "A[" + std::to_string(nleaf) + "] = " + std::to_string(A[nleaf]), nleaf++;
            } else {
                lbl += std::string(nodes[i].tp == NodeType::Cut ? "Cut" : "Join") + "\\n";
                lbl += "[" + std::to_string(nodes[i].L) + ", " + std::to_string(nodes[i].R) + ")";
            }
            ss << "label = \"" << lbl << "\",\n";
            ss << "]\n";
            for (const auto &ch : nodes[i].child) ss << i << " -> " << ch << ";\n";
        }
        ss << "{rank = same;";
        for (int i = 0; i < int(nodes.size()); i++) {
            if (nodes[i].tp == NodeType::Leaf) ss << ' ' << i << ';';
        }
        ss << "}\n";
        ss << "}\n";
        ss.close();
    }
};
