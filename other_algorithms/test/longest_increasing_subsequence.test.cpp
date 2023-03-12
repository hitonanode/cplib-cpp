#include "../longest_increasing_subsequence.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include <cassert>
#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    std::vector<int> A(N);
    for (auto &x : A) cin >> x;

    auto lis_idxs = longest_increasing_subsequence(A, LisType::StrictlyIncreasing).get_lis_indices();
    assert(lis_idxs.size() == lis_length(A, LisType::StrictlyIncreasing));

    cout << lis_idxs.size() << '\n';
    for (auto i : lis_idxs) cout << i << ' ';
    cout << '\n';
}
