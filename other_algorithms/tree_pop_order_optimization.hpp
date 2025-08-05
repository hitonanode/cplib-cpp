#pragma once
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

// "01 on Tree"
// https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions
// https://yukicoder.me/problems/no/3148
template <class S> struct TreePopOrderOptimization {
    std::vector<std::vector<int>> to;
    std::vector<S> labels;
    int root = -1;
    std::vector<S> first_slope;
    std::vector<int> par;

    TreePopOrderOptimization(const std::vector<std::vector<int>> &to, const std::vector<S> &labels,
                             int root)
        : to(to), labels(labels), root(root), first_slope(to.size()), par(to.size(), -1) {

        using Pque = std::priority_queue<S, std::vector<S>, std::greater<S>>;
        auto rec = [&](auto &&self, int now, int prv) -> Pque {
            std::vector<Pque> chs;

            for (int nxt : to[now]) {
                if (nxt == prv) continue;
                assert(par[nxt] == -1);
                par[nxt] = now;
                chs.emplace_back(self(self, nxt, now));
            }

            const S &v = labels.at(now);
            if (chs.empty()) {
                first_slope[now] = v;
                Pque pq;
                pq.emplace(v);
                return pq;
            } else {
                S first = v;

                const int idx = std::max_element(chs.begin(), chs.end(),
                                                 [](const auto &a, const auto &b) {
                                                     return a.size() < b.size();
                                                 }) -
                                chs.begin();
                std::swap(chs[idx], chs.front());

                for (int i = 1; i < (int)chs.size(); ++i) {
                    while (!chs[i].empty()) {
                        chs.front().emplace(chs[i].top());
                        chs[i].pop();
                    }
                }

                while (!chs.front().empty() and chs.front().top() < first) {
                    first += chs.front().top();
                    chs.front().pop();
                }
                chs.front().emplace(first_slope[now] = first);
                return std::move(chs.front());
            }
        };

        rec(rec, root, -1);
    }

    std::pair<std::vector<int>, S> Solve() const { return SolveSubtree(root); }

    // Generate optimal pop order of the subproblem rooted at `r`.
    std::pair<std::vector<int>, S> SolveSubtree(int r) const {
        using P = std::pair<S, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.emplace(first_slope.at(r), r);

        std::vector<int> order;
        S ret = labels.at(r);
        while (!pq.empty()) {
            const int idx = pq.top().second;
            order.emplace_back(idx);
            pq.pop();
            if (idx != r) ret += labels.at(idx);

            for (int nxt : to.at(idx)) {
                if (nxt == par.at(idx)) continue;
                pq.emplace(first_slope.at(nxt), nxt);
            }
        }

        return {order, ret};
    }
};

template <class T> struct Vector01onTree {
    T x, y;
    T res;
    Vector01onTree(T x, T y) : x(x), y(y), res(0) {}
    Vector01onTree() : x(0), y(0), res(0) {}
    bool operator<(const Vector01onTree &r) const {
        if (x == 0 and y == 0) return false;
        if (r.x == 0 and r.y == 0) return true;
        if (x == 0 and r.x == 0) return y < r.y;
        if (x == 0) return false;
        if (r.x == 0) return true;
        return y * r.x < x * r.y; // be careful of overflow
    }
    bool operator>(const Vector01onTree &r) const { return r < *this; }

    void operator+=(const Vector01onTree &r) {
        res += r.res + y * r.x;
        x += r.x;
        y += r.y;
    }
};

template <class T>
std::pair<std::vector<int>, T>
Solve01OnTree(const std::vector<std::vector<int>> &to, const std::vector<T> &xs,
              const std::vector<T> &ys, int root) {

    const int n = to.size();
    std::vector<Vector01onTree<T>> labels;
    for (int i = 0; i < n; ++i) labels.emplace_back(xs.at(i), ys.at(i));

    const TreePopOrderOptimization<Vector01onTree<T>> tpo(to, labels, root);
    auto [order, all_prod] = tpo.Solve();
    return {order, all_prod.res};
}
