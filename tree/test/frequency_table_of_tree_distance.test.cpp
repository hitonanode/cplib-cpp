#include "../frequency_table_of_tree_distance.hpp"
#include "../../convolution/fft_double.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<vector<int>> to(N);
    for (int i = 0; i < N - 1; i++) {
        int s, t;
        cin >> s >> t;
        to[s].emplace_back(t), to[t].emplace_back(s);
    }

    auto ret = frequency_table_of_tree_distance(to).solve<long long, fftconv>(std::vector<long long>(N, 1));
    for (int i = 1; i < N; i++) cout << ret[i] << ' ';
    cout << '\n';
}
