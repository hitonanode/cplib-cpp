#pragma once
#include <cassert>
#include <utility>
#include <vector>

// ConvolutionOnTree : 根付き木上で根方向へ畳み込み
// Input:
// - par_ : 各頂点の親の頂点番号 根の par_ は -1
// - f : 各頂点の初期値
// - trans : trans[i] = 各頂点から i 世代目の親頂点への遷移係数
// Verified: https://yukicoder.me/problems/no/2004
struct ConvolutionOnTree {
    int N;
    int root;
    std::vector<int> par;
    std::vector<std::vector<int>> children;

    std::vector<int> depth;
    std::vector<int> farthest_leaf;

    void _rec_build_hld(int now) {
        farthest_leaf[now] = now;
        for (int nxt : children[now]) {
            depth[nxt] = depth[now] + 1;
            _rec_build_hld(nxt);
            if (depth[farthest_leaf[now]] < depth[farthest_leaf[nxt]]) {
                farthest_leaf[now] = farthest_leaf[nxt];
            }
        }
    }

    void _build_hld() {
        depth.assign(N, 0);
        farthest_leaf.assign(N, -1);
        _rec_build_hld(root);
    }

    ConvolutionOnTree(std::vector<int> par_) : N(par_.size()), par(par_), children(par.size()) {
        root = -1;
        for (int i = 0; i < N; ++i) {
            if (par[i] >= 0 and par[i] < N) {
                children[par[i]].push_back(i);
            } else {
                assert(root == -1);
                par[i] = -1;
                root = i;
            }
        }
        assert(root != -1);

        _build_hld();
    }

    template <class T, class F>
    std::vector<T> _run_rec(const int r, int h, std::vector<T> &ret, const std::vector<T> &f,
                            const std::vector<T> &trans, F convolver) {
        const int leaf = farthest_leaf[r], d = depth[leaf] - depth[r] + 1;
        std::vector<T> g;
        std::vector<int> ids;
        g.reserve(d), ids.reserve(d);

        for (int cur = leaf, prv = -1;; prv = cur, cur = par[cur]) {
            ids.push_back(cur);
            g.push_back(f[cur]);

            for (int nxt : children[cur]) {
                if (nxt == prv) continue;
                int nxtlen = depth[farthest_leaf[nxt]] - depth[cur];
                std::vector<T> gchild =
                    _run_rec(nxt, ids.at(int(ids.size()) - nxtlen - 1), ret, f, trans, convolver);
                for (int i = 0; i < int(gchild.size()); ++i) {
                    g.at(int(g.size()) - int(gchild.size()) - 1 + i) += gchild[i];
                }
            }

            if (cur == r) break;
        }

        std::vector<T> trans_sub(trans.begin(), trans.begin() + std::min(trans.size(), g.size()));
        // trans_sub = nttconv(g, trans_sub);
        trans_sub = convolver(g, trans_sub);

        for (int cur = leaf, i = 0;; cur = par[cur], ++i, h = h >= 0 ? par[h] : h) {
            ret.at(cur) += trans_sub.at(i);
            if (h >= 0) ret.at(h) -= trans_sub.at(i);
            if (cur == r) break;
        }
        return g;
    }

    template <class T, class F>
    std::vector<T> run(const std::vector<T> &f, const std::vector<T> &trans, F convolver) {
        std::vector<T> ret(N, T());
        _run_rec<T, F>(root, -1, ret, f, trans, convolver);
        return ret;
    }
};
/* example:
ConvolutionOnTree tree(par);

auto convolve = [&](vector<mint> &l, vector<mint> &r) { return nttconv(l, r); };
auto ret = tree.run(A, trans, convolve);
*/
