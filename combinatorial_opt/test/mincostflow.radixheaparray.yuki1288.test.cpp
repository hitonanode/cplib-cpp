#define PROBLEM "https://yukicoder.me/problems/no/1288"
#include "../../data_structure/radix_heap_array.hpp"
#include "../mincostflow_nonegativeloop.hpp"
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

int main() {
    int N;
    string S;
    cin >> N >> S;
    vector<long long> V(N);
    for (auto &x : V) cin >> x;

    const int s = N * 5, t = s + 1;
    MinCostFlow<int, long long> graph(t + 1);
    for (int d = 0; d < 5; d++) {
        for (int i = 0; i < N - 1; i++) graph.add_edge(d * N + i, d * N + i + 1, N / 4, 0);
    }
    graph.add_edge(s - 1, 0, N / 4, 0);

    for (int i = 0; i < N; i++) {
        int b = 0;
        if (S[i] == 'u') b = N * 1;
        if (S[i] == 'k') b = N * 2;
        if (S[i] == 'i') b = N * 3;
        int fr = b + i + N, to = b + i;
        graph.add_edge(s, fr, 1, 0);
        graph.add_edge(fr, to, 1, V[i]);
        graph.add_edge(to, t, 1, 0);
    }
    auto cost = graph.flow<radix_heap_array<unsigned long long>>(s, t, N).second;
    cout << accumulate(V.begin(), V.end(), 0LL) - cost << '\n';
}
