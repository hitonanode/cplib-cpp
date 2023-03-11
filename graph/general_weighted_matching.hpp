#pragma once
#include <cassert>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/maximum_weighted_matching.hpp>

template <class Weight = int> struct MaxWeightedMatching {
    typedef boost::property<boost::edge_weight_t, Weight, boost::property<boost::edge_index_t, int>>
        EdgeProperty;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeProperty>
        my_graph;

    int n;
    my_graph g;

    MaxWeightedMatching(int n_vertices) : n(n_vertices), g(n_vertices) {}

    void add_edge(int u, int v, Weight w) {
        assert(0 <= u and u < n);
        assert(0 <= v and v < n);
        assert(u != v);
        boost::add_edge(u, v, EdgeProperty(w), g);
    }

    struct Solution {
        int sz;
        Weight solution;
        std::vector<int> mate;
    };

    Solution solve() {
        std::vector<typename boost::graph_traits<my_graph>::vertex_descriptor> mate(n);
        boost::maximum_weighted_matching(g, &mate[0]);
        Solution ret;
        ret.sz = boost::matching_size(g, &mate[0]);
        ret.solution = boost::matching_weight_sum(g, &mate[0]);
        for (int i = 0; i < n; ++i) {
            if (0 <= mate.at(i) and mate.at(i) < n) {
                ret.mate.push_back(mate.at(i));
            } else {
                ret.mate.push_back(-1);
            }
        }
        return ret;
    }
};
