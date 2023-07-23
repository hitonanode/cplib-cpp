#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B"
#include "../matroid_intersection_dijkstra.hpp"
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
    R.at(r) = 0;
    vector<pair<int, int>> edges;
    vector<int> weight;
    for (int e = 0; e < E; ++e) {
        int s, t, w;
        cin >> s >> t >> w;
        partition.at(t).push_back(e);
        edges.emplace_back(s, t);
        weight.emplace_back(-w);
    }
    PartitionMatroid M1(E, partition, R);
    GraphicMatroid M2(V, edges);

    vector<int> potential(weight.size());
    vector<bool> sol(weight.size());
    while (augment_matroid_intersection_dijkstra(M1, M2, sol, weight, potential)) continue;

    int ret = 0;
    for (int e = 0; e < E; ++e) ret -= sol.at(e) * weight.at(e);
    cout << ret << '\n';
}
