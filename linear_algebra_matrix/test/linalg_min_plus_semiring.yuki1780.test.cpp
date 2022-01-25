#define PROBLEM "https://yukicoder.me/problems/no/1780"

#include "../../number/min_plus_semiring.hpp"
#include "../matrix.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

int main() {

    constexpr int W = 26;
    vector<int> C(W), K(W);
    for (auto &x : C) cin >> x, --x;
    for (auto &x : K) cin >> x;
    int N;
    cin >> N;

    vector<tuple<string, int, int, int>> SABE;
    for (int i = 0; i < N; ++i) {
        string s;
        int a, b, e;
        cin >> s >> a >> b >> e;
        --a, --b;
        SABE.emplace_back(s, a, b, e);
    }

    constexpr int dim = 16;

    using R = min_plus_semiring<long long>;

    auto solve = [&](int init, int c, long long k) -> vector<R> {
        auto mat = matrix<R>::Identity(dim);
        for (const auto &sabe : SABE) {
            string s;
            int a, b, e;
            std::tie(s, a, b, e) = sabe;
            if (count(s.begin(), s.end(), (char)('A' + init)) and R(-e) < mat[a][b]) {
                mat[a][b] = -e;
                mat[b][a] = -e;
            }
        }
        vector<R> initvec(dim);
        initvec[c] = R::id();
        return mat.pow_vec(k, initvec);
    };

    vector<R> rets(dim, R::id());
    for (int w = 0; w < W; ++w) {
        auto f = solve(w, C[w], K[w]);
        for (int i = 0; i < dim; ++i) rets[i] *= f[i];
    }
    auto ret = *min_element(rets.begin(), rets.end());
    cout << (ret != R() ? to_string(-ret.val) : "Impossible") << '\n';
}
