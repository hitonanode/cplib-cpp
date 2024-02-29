#pragma once
#include <unordered_set>
#include <vector>

#include "../data_structure/fast_set.hpp"
#include "../sparse_table/rmq_sparse_table.hpp"

// Data structure maintaining "compressed graph" of subsets of the vertices of a tree
// Known as "auxiliary tree" and "virtual tree"
// https://noshi91.github.io/algorithm-encyclopedia/auxiliary-tree
class auxiliary_tree {

    int n_ = 0;
    int root_ = -1;

    // Each node is labeled by both v (given as input) and t (DFS preorder)
    std::vector<int> v2t; // v2t[v] = t
    std::vector<int> t2v; // t2v[t] = v

    // To get LCA of two vertices in O(1) per query
    std::vector<int> _rmq_pos;
    StaticRMQ<std::pair<int, int>> _rmq;

    // Auxiliary tree info
    // Variables starting with '_' are labeled by t, not v
    int _auxiliary_root = -1; // LCA of all currently activated vertices
    fast_set _is_active;      // "t in _is_active" iff t is activated
    fast_set _is_semiactive;  // "t in _is_semiactive" iff t is used in the current tree
    std::vector<int> _parent; // _parent[t] = parent of t in the current tree
    std::vector<std::unordered_set<int>> _child; // _child[t] = children of t in the current tree

    int _get_lca(int t1, int t2) const {
        if (t1 > t2) std::swap(t1, t2);
        return _rmq.get(_rmq_pos.at(t1), _rmq_pos.at(t2) + 1).second;
    }

    void _add_edge(int tpar, int tchild) {
        assert(tpar != tchild);
        assert(_parent.at(tchild) == -1);

        _parent.at(tchild) = tpar;
        _child.at(tpar).insert(tchild);
    }

    void _erase_edge(int tpar, int tchild) {
        assert(tpar != tchild);
        assert(_parent.at(tchild) == tpar);

        _parent.at(tchild) = -1;
        _child.at(tpar).erase(tchild);
    }

public:
    int n() const { return n_; }

    int original_root() const { return root_; }

    int auxiliary_root() const { return _auxiliary_root == -1 ? -1 : t2v.at(_auxiliary_root); }

    bool is_active(int v) const { return _is_active.contains(v2t.at(v)); }

    bool is_semiactive(int v) const { return _is_semiactive.contains(v2t.at(v)); }

    int get_parent(int v) const {
        const int t = v2t.at(v);
        return _parent.at(t) == -1 ? -1 : t2v.at(_parent.at(t));
    }

    std::vector<int> get_children(int v) const {
        const int t = v2t.at(v);
        std::vector<int> ret;
        ret.reserve(_child.at(t).size());
        for (int c : _child.at(t)) ret.push_back(t2v.at(c));
        return ret;
    }

    auxiliary_tree() = default;

    auxiliary_tree(const std::vector<std::vector<int>> &to, int root)
        : n_(to.size()), root_(root), v2t(n_, -1), _rmq_pos(n_, -1), _is_active(n_),
          _is_semiactive(n_), _parent(n_, -1), _child(n_) {
        std::vector<std::pair<int, int>> dfspath; // (depth, t[v])
        t2v.reserve(n_);

        auto rec = [&](auto &&self, int now, int prv, int depth) -> void {
            const int t = t2v.size();
            v2t.at(now) = t;
            t2v.push_back(now);

            _rmq_pos.at(t) = dfspath.size();
            dfspath.emplace_back(depth, t);

            for (int nxt : to.at(now)) {
                if (nxt == prv) continue;
                self(self, nxt, now, depth + 1);
                dfspath.emplace_back(depth, t);
            }
        };
        rec(rec, root, -1, 0);

        _rmq = {dfspath, std::make_pair(n_, -1)};
    }

    void activate(int v_) {
        const int t = v2t.at(v_);

        if (_is_semiactive.contains(t)) {

            // Already semiactive. Nothing to do.

        } else if (_auxiliary_root == -1) {

            // Add one vertex to empty set.
            _auxiliary_root = t;

        } else if (const int next_root = _get_lca(_auxiliary_root, t); next_root != _auxiliary_root) {

            // New node is outside the current tree. Update root.
            if (next_root != t) {
                _is_semiactive.insert(next_root);
                _add_edge(next_root, t);
            }
            _add_edge(next_root, _auxiliary_root);
            _auxiliary_root = next_root;

        } else if (const int tnxt = _is_semiactive.next(t, n_);
                   tnxt < n_ and _get_lca(t, tnxt) == t) {

            // New node lies on the path of the current tree. Insert new node.
            const int tpar = _parent.at(tnxt);
            assert(tpar >= 0);

            // tpar->tnxt => tpar->t->tnxt
            _erase_edge(tpar, tnxt);
            _add_edge(tpar, t);
            _add_edge(t, tnxt);

        } else {

            // New node is "under" the current tree.
            const int tprv = _is_semiactive.prev(t, -1);
            assert(tprv >= 0);
            const int tprvlca = _get_lca(t, tprv), tnxtlca = tnxt < n_ ? _get_lca(t, tnxt) : n_;

            const int t2 = (tnxt == n_ or _get_lca(tprvlca, tnxtlca) == tnxtlca) ? tprv : tnxt;
            const int tlca = _get_lca(t, t2);

            if (!_is_semiactive.contains(tlca)) {
                const int tc = _is_semiactive.next(tlca, n_);
                const int tpar = _parent.at(tc);
                assert(tpar >= 0);
                // tpar->tc => tpar->tlca->tc
                _is_semiactive.insert(tlca);
                _erase_edge(tpar, tc);
                _add_edge(tpar, tlca);
                _add_edge(tlca, tc);
            }

            _add_edge(tlca, t);
        }

        _is_semiactive.insert(t);
        _is_active.insert(t);
    }

    void deactivate(int v_) {
        const int t = v2t.at(v_);

        if (!_is_active.contains(t)) return;

        const int num_children = _child.at(t).size();

        if (num_children > 1) { // (1)

            // Nothing to do (just deactivate it). Still semiactivated.

        } else if (num_children == 1) {

            // Delete this vertex from the current tree.
            const int tchild = *_child.at(t).begin();

            if (_parent.at(t) == -1) {

                // Root changes.
                // t->tchild => tchild
                _auxiliary_root = tchild;
                _erase_edge(t, tchild);

            } else {

                // tpar->t->tchild => tpar->tchild
                const int tpar = _parent.at(t);
                _erase_edge(tpar, t);
                _erase_edge(t, tchild);
                _add_edge(tpar, tchild);
            }

            _is_semiactive.erase(t);

        } else if (num_children == 0 and _parent.at(t) == -1) {

            // Erase the only vertex in the current tree.
            _auxiliary_root = -1;
            _is_semiactive.erase(t);

        } else {

            assert(num_children == 0 and _parent.at(t) != -1);

            const int tpar = _parent.at(t);
            const int tparpar = _parent.at(tpar);

            if (!_is_active.contains(tpar) and _child.at(tpar).size() == 2) {

                // In only this case, parent of t is also erased.
                const int t2 =
                    t ^ (*_child.at(tpar).begin()) ^ (*std::next(_child.at(tpar).begin()));
                if (tparpar == -1) {
                    // t<-tpar->t2 => t2
                    _auxiliary_root = t2;
                    _is_semiactive.erase(tpar);
                    _erase_edge(tpar, t2);
                } else {
                    // tparpar->tpar->t2 => tparpar->t2
                    _is_semiactive.erase(tpar);
                    _erase_edge(tparpar, tpar);
                    _erase_edge(tpar, t2);
                    _add_edge(tparpar, t2);
                }
            }
            _erase_edge(tpar, t);
            _is_semiactive.erase(t);
        }

        _is_active.erase(t);
    }
};
