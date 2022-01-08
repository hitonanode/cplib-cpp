#pragma once
#include <cassert>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
// Minimum spanning tree for directed graph (spanning arborescence)
//
// Complexity: O(nm) (Chu-Liu/Edmonds' algorithm)
// Verify: https://judge.yosupo.jp/problem/directedmst
// Reference:
// [1] R. E. Tarjan, "Finding optimum branchings," Networks 7.1 (1977): 25-35.
// - https://joisino.hatenablog.com/entry/2017/01/11/230141
template <typename Weight = long long> struct MinimumSpanningArborescence {
    struct noswap_unionfind {
        std::vector<int> par;
        void initialize(int N) {
            par.resize(N);
            std::iota(par.begin(), par.end(), 0);
        }
        int find(int x) { return (par[x] == x) ? x : par[x] = find(par[x]); }
        bool unite(int child, int parent) {
            child = find(child), parent = find(parent);
            if (child == parent) return false;
            par[child] = parent;
            return true;
        }
        bool same(int x, int y) { return find(x) == find(y); }
    } uf;

    struct skew_heap {
        struct node;
        static std::vector<node> data;
        static unsigned len;
        using ptr = int;
        struct node {
        private:
            Weight add, val;
            int id;

        public:
            ptr l, r;
            node(Weight val, int id_) : add(0), val(val), id(id_), l(-1), r(-1) {}
            node() = default;
            Weight weight() const noexcept { return add + val; }
            int getid() const noexcept { return id; }
            void push() {
                if (l != -1) data[l].add += this->add;
                if (r != -1) data[r].add += this->add;
                this->val += this->add;
                this->add = 0;
            }
            void apply(Weight w) { this->add += w; }
        };

        ptr _meld(ptr a, ptr b) {
            if (a == -1) return b;
            if (b == -1) return a;
            if (data[b].weight() < data[a].weight()) std::swap(a, b);
            data[a].push();
            data[a].r = _meld(data[a].r, b);
            std::swap(data[a].l, data[a].r);
            return a;
        }

        ptr root;
        int sz;

        ptr _new_node(Weight value, int id_) {
            if (len >= data.size()) data.resize(std::max<int>(1024, data.size() * 2));
            data[len] = node(value, id_);
            return len++;
        }

    public:
        skew_heap() : root(-1), sz(0) {}
        void push(Weight value, int id_) {
            root = _meld(_new_node(value, id_), root);
            sz++;
        }
        void merge(skew_heap &heap) {
            this->root = _meld(this->root, heap.root);
            if (heap.root != -1) this->sz += heap.sz;
            heap = skew_heap();
        }
        std::pair<Weight, int> top() const { return {data[root].weight(), data[root].getid()}; }
        void add_all(Weight w) {
            if (root != -1) data[root].apply(w);
        }
        void pop() {
            data[root].push();
            root = _meld(data[root].r, data[root].l);
        }
        int size() const { return sz; }
        bool empty() const { return sz == 0; }
    };

    Weight ret;
    MinimumSpanningArborescence(const int N,
                                const std::vector<std::tuple<int, int, Weight>> &edges, int r) {
        assert(r >= 0 and r < N);
        std::vector<short> used(N);
        std::vector<skew_heap> incoming_edges(N);

        ret = 0;
        std::vector<int> from(N, r);
        std::vector<Weight> from_cost(N, 0);
        std::vector<int> used_eids;
        uf.initialize(N);
        used[r] = 2;

        // std::vector<int> par(N, -1);
        int s, t;
        Weight w;
        for (int eid = 0; eid < int(edges.size()); eid++) {
            std::tie(s, t, w) = edges[eid];
            incoming_edges[t].push(w, eid);
        }

        for (int start = 0; start < N; start++) {
            if (used[start] != 0) continue;
            int cur = start;
            std::vector<int> processing;
            while (used[cur] != 2) {
                used[cur] = 1;
                processing.push_back(cur);
                if (incoming_edges[cur].empty()) {
                    // No solution
                    return;
                }

                int eid;
                Weight w;
                std::tie(w, eid) = incoming_edges[cur].top();
                from[cur] = uf.find(std::get<0>(edges[eid]));
                // par[cur] = std::get<0>(edges[eid]);
                // par[std::get<1>(edges[eid])] = std::get<0>(edges[eid]);
                from_cost[cur] = w;
                incoming_edges[cur].pop();
                if (from[cur] == cur) continue;

                ret += from_cost[cur];
                used_eids.push_back(eid);

                if (used[from[cur]] == 1) {
                    int p = cur;
                    do {
                        incoming_edges[p].add_all(-from_cost[p]);
                        if (p != cur) {
                            uf.unite(p, cur);
                            incoming_edges[cur].merge(incoming_edges[p]);
                        }
                        p = uf.find(from[p]);
                    } while (p != cur);
                } else {
                    cur = from[cur];
                }
            }
            for (int v : processing) used[v] = 2;
        }
    }
};
template <>
std::vector<MinimumSpanningArborescence<long long>::skew_heap::node>
    MinimumSpanningArborescence<long long>::skew_heap::data = {};
template <typename T> unsigned MinimumSpanningArborescence<T>::skew_heap::len = 0;
