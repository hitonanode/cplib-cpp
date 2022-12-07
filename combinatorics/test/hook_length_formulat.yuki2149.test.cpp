#define PROBLEM "https://yukicoder.me/problems/no/2149"
#include "../hook_length_formula.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#include <atcoder/modint>
using mint = atcoder::modint998244353;

pair<int, mint> solve(const vector<int> &v) {
    vector<int> hook;
    int n0 = 0;
    int total_move = 0;
    for (auto x : v) {
        if (x == 0) {
            ++n0;
        } else if (n0) {
            total_move += n0;
            hook.push_back(n0);
        }
    }
    mint ret = hook_length_formula<mint>(hook);
    return {total_move, ret};
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;

    vector<int> seq;
    int lasta = 0;
    while (N--) {
        int a;
        cin >> a;
        seq.resize(seq.size() + a - lasta, 0);
        seq.push_back(1);
        lasta = a;
    }

    vector<int> v0, v1;
    for (int i = 0; i < int(seq.size()); ++i) { (i % 2 ? v1 : v0).push_back(seq.at(i)); }
    const int n0 = count(v0.cbegin(), v0.cend(), 1);
    const int n1 = count(v1.cbegin(), v1.cend(), 1);
    if (n0 < n1 or n1 + 1 < n0) {
        puts("0");
        return 0;
    }
    auto [len0, sol0] = solve(v0);
    auto [len1, sol1] = solve(v1);
    mint ret = sol0 * sol1;
    mint den = 1;
    for (int i = 0; i < len0; ++i) ret *= len0 + len1 - i, den *= i + 1;
    cout << (ret / den).val() << endl;
}
