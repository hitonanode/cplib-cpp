#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605"
#include "../matroid_intersection.hpp"
#include "../matroids/graphic_matroid.hpp"
#include "../matroids/partition_matroid.hpp"
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    while (true) {
        int N, M, K;
        cin >> N >> M >> K;
        if (N == 0) break;
        vector<vector<int>> partition(2);
        vector<int> R{K, N - 1 - K};
        vector<pair<int, int>> edges;
        vector<int> weights;
        for (int e = 0; e < M; ++e) {
            int u, v, w;
            char l;
            cin >> u >> v >> w >> l;
            --u, --v;
            partition[l == 'B'].push_back(e);
            edges.emplace_back(u, v);
            weights.push_back(w);
        }
        PartitionMatroid M1(edges.size(), partition, R);
        GraphicMatroid M2(N, edges);
        vector<bool> ret = MatroidIntersection(M1, M2, weights);
        int ne = accumulate(ret.begin(), ret.end(), 0);
        if (ne < N - 1) {
            cout << "-1\n";
        } else {
            int sum = 0;
            for (int e = 0; e < M; ++e) sum += ret[e] * weights[e];
            cout << sum << '\n';
        }
    }
}
