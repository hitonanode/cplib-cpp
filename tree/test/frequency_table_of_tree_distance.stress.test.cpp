#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../frequency_table_of_tree_distance.hpp"
#include "../../convolution/ntt.hpp"
#include "../../graph/shortest_path.hpp"
#include "../../modint.hpp"
#include "../../random/xorshift.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

using mint = ModInt<998244353>;

int main() {
    for (int t = 0; t < 10000; t++) {
        int n = rand_int() % 100 + 1;
        int w = rand_int() % n + 1;
        vector<vector<int>> to(n);
        shortest_path<int> graph(n);
        for (int i = 1; i < n; i++) {
            int j = max<int>(0, i - 1 - rand_int() % w);
            to[i].push_back(j);
            to[j].push_back(i);
            graph.add_bi_edge(i, j, 1);
        }
        vector<mint> weight(n);
        for (auto &x : weight) x = rand_int() % mint::mod();

        auto ret1 = frequency_table_of_tree_distance(to).solve<mint, nttconv<mint>>(weight);
        vector<mint> ret2(n);
        for (int i = 0; i < n; i++) {
            graph.solve(i);
            for (int j = i + 1; j < n; j++) ret2[graph.dist[j]] += weight[i] * weight[j];
        }
        assert(ret1 == ret2);
    }
    cout << "Hello World\n";
}
