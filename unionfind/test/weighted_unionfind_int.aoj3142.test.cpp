#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3142"
#include "../weighted_unionfind.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<vector<int>> to;
vector<int> A, B;
WeightedUnionFind<long long> uf;

long long dfs(int now, int prv) {
    long long acc = B[now] - A[now];
    for (auto nxt : to[now]) {
        if (nxt != prv) {
            long long tmp = dfs(nxt, now);
            uf.unite(nxt, now, tmp);
            acc += tmp;
        }
    }
    return acc;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    cin >> N;
    uf = WeightedUnionFind<long long>(N);
    to.resize(N);

    for (int e = 0; e < N - 1; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    A.resize(N);
    B.resize(N);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;
    dfs(0, -1);

    long long sum = 0, lo = 1LL << 60;
    for (int i = 0; i < N; i++) {
        long long tmp = uf.diff(0, i);
        sum += tmp, lo = lo > tmp ? tmp : lo;
    }
    cout << sum - lo * N << '\n';
}
