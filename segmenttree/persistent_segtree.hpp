#pragma once

#include <bit>
#include <cassert>
#include <functional>
#include <vector>

template <class S, auto op, auto e> struct persistent_segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");

    struct Root {
        int id;
    };

    explicit persistent_segtree(int n) : persistent_segtree(std::vector<S>(n, e())) {}
    explicit persistent_segtree(const std::vector<S> &v) : _n(int(v.size())) {
        size = std::bit_ceil((unsigned int)_n);
        lg = std::countr_zero((unsigned int)size);
        nodes.assign(2 * size, Node{e(), -1, -1});

        for (int i = 0; i < _n; i++) nodes[size + i].val = v[i];
        for (int i = size - 1; i >= 1; i--) {
            nodes[i].left = 2 * i;
            nodes[i].right = 2 * i + 1;
            nodes[i].val = op(nodes[2 * i].val, nodes[2 * i + 1].val);
        }
    }

    Root set(const Root &root, int p, const S &x) {
        assert(0 <= p && p < _n);

        std::vector<int> ids(lg + 1);

        ids[lg] = root.id;
        for (int i = lg - 1; i >= 0; --i) {
            const Node &par = nodes[ids[i + 1]];
            ids[i] = ((p >> i) & 1) ? par.right : par.left;
        }

        int copy_cur = new_node(x, -1, -1);

        for (int i = 1; i <= lg; i++) {
            const int par = ids[i], cur = ids[i - 1];
            const Node &par_node = nodes[par];
            const int left = par_node.left == cur ? copy_cur : par_node.left;
            const int right = par_node.right == cur ? copy_cur : par_node.right;
            copy_cur = new_node(op(nodes[left].val, nodes[right].val), left, right);
        }

        return Root{copy_cur};
    }

    S get(const Root &root, int p) const {
        assert(0 <= p && p < _n);
        int i = root.id;
        for (int bit = lg - 1; bit >= 0; --bit) {
            i = ((p >> bit) & 1) ? nodes[i].right : nodes[i].left;
        }
        return nodes[i].val;
    }

    S prod(const Root &root, int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        auto rec = [&](auto &&self, int i, int lo, int hi) -> S {
            if (r <= lo || hi <= l) return e();
            if (l <= lo && hi <= r) return nodes[i].val;
            const int mid = (lo + hi) >> 1;
            return op(self(self, nodes[i].left, lo, mid), self(self, nodes[i].right, mid, hi));
        };
        return rec(rec, root.id, 0, size);
    }

    S all_prod(const Root &root) const { return nodes[root.id].val; }

    template <bool (*f)(S)> int max_right(const Root &root, int l) const {
        return max_right(root, l, [](S x) { return f(x); });
    }
    template <class F> int max_right(const Root &root, int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        S sm = e();
        auto rec = [&](auto &&self, int i, int lo, int hi) -> int {
            if (hi <= l) return hi;
            if (l <= lo) {
                const S nxt = op(sm, nodes[i].val);
                if (f(nxt)) {
                    sm = nxt;
                    return hi;
                }
                if (hi - lo == 1) return lo;
            }
            const int mid = (lo + hi) >> 1;
            if (l < mid) {
                const int left_res = self(self, nodes[i].left, lo, mid);
                if (left_res < mid) return left_res;
            }
            return self(self, nodes[i].right, mid, hi);
        };
        return std::min(rec(rec, root.id, 0, size), _n);
    }

    template <bool (*f)(S)> int min_left(const Root &root, int r) const {
        return min_left(root, r, [](S x) { return f(x); });
    }
    template <class F> int min_left(const Root &root, int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        S sm = e();
        auto rec = [&](auto &&self, int i, int lo, int hi) -> int {
            if (r <= lo) return lo;
            if (hi <= r) {
                const S nxt = op(nodes[i].val, sm);
                if (f(nxt)) {
                    sm = nxt;
                    return lo;
                }
                if (hi - lo == 1) return hi;
            }
            const int mid = (lo + hi) >> 1;
            if (mid < r) {
                const int right_res = self(self, nodes[i].right, mid, hi);
                if (mid < right_res) return right_res;
            }
            return self(self, nodes[i].left, lo, mid);
        };
        return rec(rec, root.id, 0, size);
    }

    Root get_root() const { return {1}; }

    struct Node {
        S val;
        int left, right;
    };

    int _n, size, lg;
    std::vector<Node> nodes;

    int new_node(const S &val, int left, int right) {
        nodes.push_back(Node{val, left, right});
        return int(nodes.size()) - 1;
    }
};
