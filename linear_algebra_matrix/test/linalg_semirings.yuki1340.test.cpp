#define PROBLEM "https://yukicoder.me/problems/no/1340"

#include "../../number/min_max_semiring.hpp"
#include "../../number/min_plus_semiring.hpp"
#include "../matrix.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
using namespace std;

template <class Semiring> int solve(int N, const vector<pair<int, int>> &edges, long long T) {
    matrix<Semiring> mat(N, N);
    for (auto edge : edges) mat[edge.second][edge.first] = Semiring::id();
    vector<Semiring> initvec(N, Semiring());
    initvec[0] = Semiring::id();
    vector<Semiring> vec = mat.pow_vec(T, initvec);
    return count(vec.begin(), vec.end(), Semiring::id());
}

int main() {
    int N, M;
    long long T;
    cin >> N >> M >> T;
    vector<pair<int, int>> edges;
    while (M--) {
        int a, b;
        cin >> a >> b;
        edges.emplace_back(a, b);
    }

    auto sol1 = solve<min_max_semiring<int>>(N, edges, T);
    auto sol2 = solve<min_plus_semiring<int>>(N, edges, T);
    assert(sol1 == sol2);
    cout << sol1 << '\n';
}
