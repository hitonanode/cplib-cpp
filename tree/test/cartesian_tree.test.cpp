#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../cartesian_tree.hpp"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    std::vector<int> A(N);
    for (auto &x : A) cin >> x;
    auto Ainv = A;
    for (auto &x : Ainv) x = -x;
    auto ret = cartesian_tree(A);
    auto ret2 = cartesian_tree<int, std::greater<int>>(Ainv);
    assert(ret == ret2);
    for (int i = 0; i < N; ++i) cout << (ret[i] < 0 ? i : ret[i]) << (i + 1 == N ? '\n' : ' ');
}
