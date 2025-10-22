#define PROBLEM "https://yukicoder.me/problems/no/3306"

#include "../linear_sum_assignment.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector A(N, vector<int>(M));
    for (auto &v : A) {
        for (auto &x : v) cin >> x;
    }

    const int K = N / 2;
    vector mat(K, vector<long long>(K));
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            int best = 0;
            for (int k = 0; k < M; ++k) best = max(best, A.at(N - 1 - j).at(k) - A.at(i).at(k));
            mat.at(i).at(j) = -best;
        }
    }

    auto res = linear_sum_assignment::solve(K, K, mat);
    cout << -res.opt << '\n';
}
