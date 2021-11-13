#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B"
#include "../matroid_intersection.hpp"
#include "../matroids/graphic_matroid.hpp"
#include "../matroids/partition_matroid.hpp"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    vector<vector<int>> partition(V);
    vector<int> R(V, 1);
    R[r] = 0;
    vector<pair<int, int>> edges;
    vector<int> weights;
    for (int e = 0; e < E; ++e) {
        int s, t, w;
        cin >> s >> t >> w;
        partition[t].push_back(e);
        edges.emplace_back(s, t);
        weights.emplace_back(w);
    }

    PartitionMatroid M1(E, partition, R);
    GraphicMatroid M2(V, edges);

    auto sol = MatroidIntersection(M1, M2, weights);
    int ret = 0;
    for (int e = 0; e < E; ++e) ret += sol[e] * weights[e];
    cout << ret << '\n';
}
