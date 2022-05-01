#define PROBLEM "https://yukicoder.me/problems/no/1660"
#include "../shortest_path.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    shortest_path<int> graph(N + 1);
    vector<int> indeg(N);
    while (K--) {
        int r, c;
        cin >> r >> c;
        r--, c--;
        if (r == c) {
            cout << "-1\n";
            return 0;
        }
        indeg[c]++;
        graph.add_edge(r, c, -1);
    }
    for (int i = 0; i < N; i++) graph.add_edge(N, i, -1);
    if (graph.dag_solver(N)) {
        cout << -(*min_element(graph.dist.begin(), graph.dist.end())) << '\n';
    } else {
        cout << "-1\n";
    }
}
